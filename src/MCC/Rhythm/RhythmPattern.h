#ifndef MCC_RHYTHM_RHYTHM_PATTERN_H
#define MCC_RHYTHM_RHYTHM_PATTERN_H

#include <stddef.h>
#include <stdint.h>

#include <MCC_BuildSettings.h>

#include <Foundation/Containers/BitVector.h>

namespace MCC {

/**
 * @brief Cyclic onset/rest pattern on a grid of equal steps.
 * @ingroup MCC_Rhythm
 *
 * The step count is chosen and changed at runtime, from one to MaximumSteps
 * (SPEC-RHY-11). The steps are a `Foundation::Containers::BitVector`, one
 * bit per step, and follow its storage rules:
 *
 * - **Owned:** heap storage that grows on demand. Like a vector, the
 *   pattern keeps a step count and a larger or equal Capacity(); changing
 *   the step count within the capacity never reallocates, and growing past
 *   it lets the underlying `cpstd::vector` choose the new capacity. Capacity counts whole bytes, so it is a
 *   multiple of eight steps (capped at MaximumSteps).
 * - **Attached:** a non-null buffer passed to Attach() (or the buffer
 *   constructor) is caller-owned storage. The pattern never allocates,
 *   reallocates nor frees it; anything that would need more than the buffer
 *   returns `false` and changes nothing. The caller keeps the buffer alive
 *   while attached. A null buffer selects owned storage.
 *
 * Copy assignment, and move assignment into an attached pattern, copy the
 * steps into the existing storage, so an attached pattern stays attached. The
 * operations that return a new pattern (FromString(), Rotated(), ...) own
 * heap storage; their in-place counterparts (Parse(), Rotate(), Invert(),
 * Append()) work inside an attached buffer without allocating.
 *
 * A pattern may contain no onsets; the invalid pattern has no steps.
 * Allocation failure yields the invalid pattern or a `false` result that
 * leaves the pattern unchanged (SPEC-ERR-1..4). The pattern is a cycle: step
 * queries are reduced modulo the step count and Rotated() starts the cycle
 * later (SPEC-RHY-12..13).
 *
 * Like ScalePattern, a rhythm pattern is structure only. It records neither
 * the written value of a step, a meter, a tempo, a clock nor PPQN: the
 * catalog supplies written context and MIDILAR decides when each step plays
 * (SPEC-RHY-14).
 *
 * Text uses Toussaint's box notation, `x` for an onset and `.` for a rest
 * (`"x..x..x...x.x..."` is the son clave), or his interonset-interval
 * notation (`"3-3-4-2-4"`).
 */
class RhythmPattern {
public:
    /** @brief Largest step count. */
    static constexpr uint16_t MaximumSteps = 0xFFFFu;

    /** @brief Bytes needed to store `steps` steps; use it to size buffers. */
    static constexpr size_t BytesFor(uint32_t steps) noexcept {
        return Foundation::Containers::BitVector::BytesFor(steps);
    }

    /** @brief Creates the invalid pattern without storage (SPEC-ERR-2). */
    RhythmPattern() noexcept : _steps() {}

    /**
     * @brief Creates `steps` rests in owned storage.
     *
     * Invalid when `steps` is outside `[1, MaximumSteps]` or storage cannot
     * be allocated.
     */
    explicit RhythmPattern(int32_t steps) noexcept;

    /**
     * @brief Creates an empty (invalid) pattern attached to `buffer`, or with
     * owned storage when `buffer` is null; see Attach().
     */
    RhythmPattern(uint8_t* buffer, size_t bytes) noexcept : _steps(buffer, bytes) {}

    // Copy, move and destruction follow Foundation::Containers::BitVector:
    // a copy owns exactly its steps; copy assignment, and move assignment
    // into an attached pattern, copy into the existing storage; a move
    // otherwise takes the storage; owned storage is freed on destruction.

    /** @brief Returns the invalid pattern. */
    static RhythmPattern Invalid() noexcept { return RhythmPattern(); }

    /**
     * @brief Creates up to 32 steps from a mask: bit `i` marks step `i`.
     *
     * Invalid when `steps` is outside `[1, 32]` or `onsets` sets a bit at or
     * beyond `steps`.
     */
    static RhythmPattern FromMask(uint32_t onsets, int32_t steps) noexcept;

    /** @brief Returns a new owned pattern parsed by Parse(), or invalid. */
    static RhythmPattern FromString(const char* text) noexcept;

    /** @brief Returns a new owned pattern parsed by ParseIntervals(), or invalid. */
    static RhythmPattern FromIntervals(const char* text) noexcept;

    /**
     * @brief Uses `buffer` (`bytes` long) as storage, without owning it.
     *
     * Releases any owned storage and leaves an empty (invalid) pattern with a
     * capacity of `bytes * 8` steps (reported up to MaximumSteps); use
     * Resize(), Append() or Parse() to fill it. The buffer's bytes are
     * written as steps are added. A null `buffer` returns to empty owned
     * storage instead. Returns `false` and changes nothing only for this
     * pattern's own owned storage.
     */
    bool Attach(uint8_t* buffer, size_t bytes) noexcept { return _steps.Attach(buffer, bytes); }

    /**
     * @brief Releases owned storage or detaches from the attached buffer,
     * leaving the invalid pattern without storage.
     */
    void Release() noexcept { _steps.Release(); }

    /** @brief Returns `true` when the storage is owned (heap) rather than attached. */
    bool OwnsStorage() const noexcept { return _steps.OwnsStorage(); }

    /**
     * @brief Replaces the steps with box notation such as
     * `"x..x..x...x.x..."`.
     *
     * `x` or `X` is an onset and `.` a rest. Spaces and `|` are ignored so
     * `"x . . x"` and `"x..x..x.|..x.x..."` read as written in the sources.
     * Returns `false` and changes nothing for any other character, no steps,
     * more than MaximumSteps steps, or too little storage.
     */
    bool Parse(const char* text) noexcept;

    /**
     * @brief Replaces the steps with interonset intervals such as
     * `"3-3-4-2-4"`.
     *
     * Each interval is a positive decimal count of steps from one onset to
     * the next; the first onset falls on step 0 and the intervals sum to the
     * step count. Returns `false` and changes nothing for malformed text, a
     * zero interval, a sum above MaximumSteps, or too little storage.
     */
    bool ParseIntervals(const char* text) noexcept;

    /** @brief Returns `true` unless this is the invalid pattern. */
    bool IsValid() const noexcept { return !_steps.IsEmpty(); }

    /** @brief Returns the number of steps, or `0` for the invalid pattern. */
    uint16_t StepCount() const noexcept { return static_cast<uint16_t>(_steps.GetCount()); }

    /** @brief Returns how many steps fit without reallocating. */
    uint16_t Capacity() const noexcept;

    /** @brief Returns the number of onsets, or `0` for the invalid pattern. */
    uint16_t OnsetCount() const noexcept;

    /**
     * @brief Returns `true` when `step`, reduced modulo StepCount(), is an
     * onset; always `false` for the invalid pattern.
     */
    bool IsOnset(int32_t step) const noexcept;

    /**
     * @brief Returns the step of the `index`-th onset (0-based), or `-1` when
     * `index` is outside `[0, OnsetCount())`.
     */
    int32_t OnsetStep(int32_t index) const noexcept;

    /**
     * @brief Returns the steps from the `index`-th onset to the next one,
     * wrapping around the cycle, or `0` when `index` is out of range.
     *
     * A pattern with a single onset has one interval equal to StepCount().
     */
    int32_t InteronsetInterval(int32_t index) const noexcept;

    /**
     * @brief Makes step `step` an onset or a rest.
     *
     * Returns `false` and changes nothing when the pattern is invalid or
     * `step` is outside `[0, StepCount())`.
     */
    bool SetOnset(int32_t step, bool onset = true) noexcept;

    /**
     * @brief Changes the step count, keeping existing steps and adding rests.
     *
     * Reallocates owned storage only when `steps` exceeds Capacity() (to at
     * least the bytes `steps` needs); shrinking never reallocates. Returns
     * `false` and changes nothing when `steps` is outside `[1, MaximumSteps]`
     * or the storage cannot hold it.
     */
    bool Resize(int32_t steps) noexcept;

    /**
     * @brief Ensures Capacity() is at least `steps` without changing the
     * pattern; `false` when `steps` is outside `[0, MaximumSteps]` or the
     * storage cannot hold it.
     */
    bool Reserve(int32_t steps) noexcept;

    /**
     * @brief Adds one step at the end. Owned storage grows geometrically when
     * full; `false` and unchanged at MaximumSteps or when the storage cannot
     * grow.
     */
    bool Append(bool onset = false) noexcept;

    /**
     * @brief Adds `other`'s steps at the end (`other` may be this pattern);
     * `false` and unchanged when `other` is invalid, the result exceeds
     * MaximumSteps, or the storage cannot grow.
     */
    bool Append(const RhythmPattern& other) noexcept;

    /**
     * @brief Asks owned storage to shrink to the bytes the steps need, as
     * `cpstd::vector::shrink_to_fit()` does. Attached storage is left as is.
     * Returns `true`.
     */
    bool ShrinkToFit() noexcept;

    /**
     * @brief Starts the cycle `steps` steps later, in place and without
     * allocating (SPEC-RHY-12). `false` for the invalid pattern.
     */
    bool Rotate(int32_t steps) noexcept;

    /** @brief Swaps onsets and rests in place; `false` for the invalid pattern. */
    bool Invert() noexcept;

    /**
     * @brief Returns the pattern started `steps` steps later (SPEC-RHY-12).
     *
     * Step `i` of the result is step `i + steps` of this pattern, modulo the
     * step count; negative values start earlier. `Rotated(8)` turns the
     * 3-2 son clave into the 2-3 clave. Invalid stays invalid.
     */
    RhythmPattern Rotated(int32_t steps) const noexcept;

    /**
     * @brief Returns `true` when both patterns are the same necklace: equal
     * step counts and some rotation of `other` equals this pattern
     * (SPEC-RHY-13). Invalid patterns are never rotations.
     */
    bool IsRotationOf(const RhythmPattern& other) const noexcept;

    /** @brief Returns a copy with onsets and rests swapped. Invalid stays invalid. */
    RhythmPattern Complement() const noexcept;

    /**
     * @brief Returns this pattern followed by `other`; invalid when either is
     * invalid or the result exceeds MaximumSteps.
     */
    RhythmPattern Concatenated(const RhythmPattern& other) const noexcept;

    /** @brief Exact equality: same step count and onsets; storage is ignored. */
    friend bool operator==(const RhythmPattern& a, const RhythmPattern& b) noexcept {
        return a._steps == b._steps;
    }

    /** @brief Negation of `operator==`. */
    friend bool operator!=(const RhythmPattern& a, const RhythmPattern& b) noexcept {
        return a._steps != b._steps;
    }

private:
    // Bit i is step i; bits past the step count are always zero.
    Foundation::Containers::BitVector _steps;

    bool Bit(uint16_t step) const noexcept { return _steps.Get(step); }
    void ReverseSteps(uint16_t first, uint16_t last) noexcept;
};

} // namespace MCC

#endif // MCC_RHYTHM_RHYTHM_PATTERN_H
