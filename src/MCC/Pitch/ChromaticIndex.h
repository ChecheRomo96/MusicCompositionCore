#ifndef MCC_PITCH_CHROMATIC_INDEX_H
#define MCC_PITCH_CHROMATIC_INDEX_H

#include <stdint.h>

#include <Foundation/Math/Arithmetic.h>

#include <MCC/Pitch/ChromaticClass.h>

namespace MCC {

/**
 * @brief Absolute semitone position of a pitch, with origin `C-1 = 0`.
 * @ingroup MCC_Pitch
 *
 * `C0 = 12`, `C4 = 60` and `A4 = 69` (SPEC-CHR-1). Valid values cover every
 * writable pitch, from `Cbbbb-128 = -1528` to `B####127 = 1551`
 * (SPEC-CHR-2); they are not restricted to any protocol range (SPEC-CHR-3).
 *
 * Default construction and out-of-range input produce the single invalid
 * value (SPEC-ERR-2, SPEC-ERR-3). Indices are ordered by value; the invalid
 * value sorts after every valid index.
 */
class ChromaticIndex {
public:
    /** @brief Lowest valid index: `Cbbbb` in octave -128. */
    static constexpr int16_t Minimum = -1528;

    /** @brief Highest valid index: `B####` in octave 127. */
    static constexpr int16_t Maximum = 1551;

    /**
     * @brief Sentinel returned by `Value()` for the invalid index
     * (SPEC-ERR-7). Do not rely on it; check `IsValid()`.
     */
    static constexpr int16_t InvalidValue = 32767;

private:
    int16_t _value;

public:
    /** @brief Creates the invalid index (SPEC-ERR-2). */
    constexpr ChromaticIndex() noexcept : _value(InvalidValue) {}

    /**
     * @brief Creates the index `value`; values outside
     * `[Minimum, Maximum]` produce the invalid index (SPEC-ERR-3).
     */
    constexpr explicit ChromaticIndex(int32_t value) noexcept
        : _value((value >= Minimum && value <= Maximum)
              ? static_cast<int16_t>(value)
              : InvalidValue) {}

    /** @brief Returns the invalid index. */
    static constexpr ChromaticIndex Invalid() noexcept {
        return ChromaticIndex();
    }

    /** @brief Returns `true` unless this is the invalid index. */
    constexpr bool IsValid() const noexcept { return _value != InvalidValue; }

    /**
     * @brief Returns the semitone position, or `InvalidValue` for the
     * invalid index (SPEC-ERR-7).
     */
    constexpr int16_t Value() const noexcept { return _value; }

    /**
     * @brief Returns the chromatic class `Value() mod 12` (SPEC-ORD-4); the
     * invalid index yields the invalid class (SPEC-ERR-4).
     */
    constexpr MCC::ChromaticClass ChromaticClass() const noexcept {
        if (!IsValid()) {
            return MCC::ChromaticClass::Invalid();
        }
        return MCC::ChromaticClass(
            Foundation::Math::FloorMod(_value, MCC::ChromaticClass::Count));
    }

    /**
     * @brief Returns this index moved by `semitones`. The result is invalid
     * when this index is invalid or the result leaves
     * `[Minimum, Maximum]` (SPEC-ERR-4, SPEC-ERR-5).
     */
    constexpr ChromaticIndex Transposed(int32_t semitones) const noexcept {
        if (!IsValid() ||
            semitones < Minimum - Maximum ||
            semitones > Maximum - Minimum) {
            return Invalid();
        }
        return ChromaticIndex(static_cast<int32_t>(_value) + semitones);
    }

    /** @brief Equality; all invalid indices are equal (SPEC-ERR-6). */
    friend constexpr bool operator==(ChromaticIndex a, ChromaticIndex b) noexcept {
        return a._value == b._value;
    }

    friend constexpr bool operator!=(ChromaticIndex a, ChromaticIndex b) noexcept {
        return !(a == b);
    }

    /** @brief Orders by value; invalid sorts last. */
    friend constexpr bool operator<(ChromaticIndex a, ChromaticIndex b) noexcept {
        return a._value < b._value;
    }

    friend constexpr bool operator>(ChromaticIndex a, ChromaticIndex b) noexcept {
        return b < a;
    }

    friend constexpr bool operator<=(ChromaticIndex a, ChromaticIndex b) noexcept {
        return !(b < a);
    }

    friend constexpr bool operator>=(ChromaticIndex a, ChromaticIndex b) noexcept {
        return !(a < b);
    }
};

} // namespace MCC

#endif // MCC_PITCH_CHROMATIC_INDEX_H
