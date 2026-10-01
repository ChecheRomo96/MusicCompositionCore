#ifndef MCC_CHORD_CHORD_H
#define MCC_CHORD_CHORD_H

#include <stddef.h>
#include <stdint.h>

#include <MCC/Chord/ChordPattern.h>
#include <MCC/Interval/Transposition.h>
#include <MCC/Pitch/NoteName.h>
#include <MCC/Pitch/Pitch.h>
#include <MCC/Pitch/PitchClass.h>

namespace MCC {

/**
 * @brief A chord pattern spelled from a root note name.
 * @ingroup MCC_Chord
 *
 * Tones are 1-based in root-position order. Each tone is the root transposed
 * by the pattern's interval, so `E` major contains `G#` and the ninth of `C9`
 * is `D` (SPEC-CHD-2). A tone whose spelling would need an accidental outside
 * `[-4, +4]` is the invalid note name (SPEC-ACC-3).
 *
 * Membership is written by default (`Contains`) and enharmonic only on
 * request (`ContainsPitchClass`), following SPEC-EQ-1..2.
 */
class Chord {
    NoteName _root;
    ChordPattern _pattern;

public:
    /** @brief Creates the invalid chord (SPEC-ERR-2). */
    constexpr Chord() noexcept : _root(), _pattern() {}

    /** @brief Spells `pattern` from `root`; invalid when either is invalid. */
    constexpr Chord(NoteName root, ChordPattern pattern) noexcept
        : _root(root.IsValid() && pattern.IsValid() ? root : NoteName::Invalid()),
          _pattern(root.IsValid() && pattern.IsValid() ? pattern : ChordPattern::Invalid()) {}

    /** @brief Returns the invalid chord. */
    static constexpr Chord Invalid() noexcept { return Chord(); }

    /** @brief Returns `true` unless this is the invalid chord. */
    constexpr bool IsValid() const noexcept { return _pattern.IsValid(); }

    /** @brief Returns the root note name. */
    constexpr NoteName Root() const noexcept { return _root; }

    /** @brief Returns the root-independent pattern. */
    constexpr ChordPattern Pattern() const noexcept { return _pattern; }

    /** @brief Returns the number of tones, or 0 for the invalid chord. */
    constexpr uint8_t ToneCount() const noexcept { return _pattern.ToneCount(); }

    /**
     * @brief Returns the note name of `tone` (1-based), or the invalid note
     * name outside the chord or when it cannot be spelled.
     */
    constexpr NoteName ToneAt(int32_t tone) const noexcept {
        return _root + _pattern.ToneInterval(tone);
    }

    /**
     * @brief Returns the root-position pitch of `tone` when the root is placed
     * in `rootOctave`; extensions keep their compound distance.
     */
    constexpr MCC::Pitch PitchAt(int32_t tone, int32_t rootOctave) const noexcept {
        return MCC::Pitch(_root, rootOctave) + _pattern.ToneInterval(tone);
    }

    /** @brief Returns `true` when a tone is written exactly as `noteName`. */
    constexpr bool Contains(NoteName noteName) const noexcept {
        if (!noteName.IsValid()) {
            return false;
        }
        const uint8_t count = ToneCount();
        for (uint8_t tone = 1; tone <= count; ++tone) {
            if (ToneAt(tone) == noteName) {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Returns `true` when any tone sounds as `pitchClass`, regardless
     * of spelling (explicit enharmonic membership, SPEC-EQ-2).
     */
    constexpr bool ContainsPitchClass(MCC::PitchClass pitchClass) const noexcept {
        if (!IsValid() || !pitchClass.IsValid()) {
            return false;
        }
        const int32_t offset =
            ((static_cast<int32_t>(pitchClass.Value()) - _root.PitchClass().Value()) % 12 + 12) % 12;
        return ((static_cast<uint32_t>(_pattern.PitchClassMask()) >> offset) & 1u) != 0;
    }

    /**
     * @brief Writes a close-position voicing of `inversion` into `pitches`.
     *
     * Inversion 0 is root position; inversion `k` places tone `k + 1` in the
     * bass with the root in `rootOctave`, and raises each earlier tone by
     * whole octaves until it lies above the previous pitch (SPEC-CHD-3).
     * Writes at most `capacity` pitches and returns the number the voicing
     * needs, or 0 for an invalid chord or an inversion outside
     * `[0, ToneCount() - 1]`.
     */
    size_t Voicing(int32_t inversion, int32_t rootOctave,
                   MCC::Pitch* pitches, size_t capacity) const noexcept {
        const uint8_t count = ToneCount();
        if (count == 0 || inversion < 0 || inversion >= count) {
            return 0;
        }
        MCC::Pitch previous;
        for (uint8_t i = 0; i < count; ++i) {
            const int32_t tone = (inversion + i) % count + 1;
            MCC::Pitch pitch = PitchAt(tone, rootOctave);
            while (previous.IsValid() && pitch.IsValid() && !IsLowerThan(previous, pitch)) {
                pitch = pitch.MovedByOctaves(1);
            }
            if (i < capacity) {
                pitches[i] = pitch;
            }
            previous = pitch;
        }
        return count;
    }

    /** @brief Compares roots by spelling and patterns by tones. */
    friend constexpr bool operator==(const Chord& a, const Chord& b) noexcept {
        return a._root == b._root && a._pattern == b._pattern;
    }

    /** @brief Negation of `operator==`. */
    friend constexpr bool operator!=(const Chord& a, const Chord& b) noexcept {
        return !(a == b);
    }
};

} // namespace MCC

#endif // MCC_CHORD_CHORD_H
