#ifndef MCC_SCALE_SCALE_H
#define MCC_SCALE_SCALE_H

#include <MCC_BuildSettings.h>

#include <stdint.h>

#include <MCC/Interval/Transposition.h>
#include <MCC/Pitch/NoteName.h>
#include <MCC/Pitch/Pitch.h>
#include <MCC/Pitch/PitchClass.h>
#include <MCC/Scale/ScalePattern.h>

namespace MCC {

/**
 * @brief A scale pattern spelled from a root note name.
 * @ingroup MCC_Scale
 *
 * Degrees are 1-based. Each degree is the root transposed by the pattern's
 * interval, so spelling follows the pattern (SPEC-SCL-2): `E` major contains
 * `G#`, never `Ab`. A degree whose spelling would need an accidental outside
 * `[-4, +4]` is the invalid note name (SPEC-ACC-3, SPEC-SCL-3).
 *
 * Membership is written by default (`Contains`) and enharmonic only on
 * request (`ContainsPitchClass`), following SPEC-EQ-1..2.
 */
class Scale {
    NoteName _root;
    ScalePattern _pattern;

public:
    /** @brief Creates the invalid scale (SPEC-ERR-2). */
    constexpr Scale() noexcept : _root(), _pattern() {}

    /**
     * @brief Spells `pattern` from `root`; invalid when either is invalid.
     */
    constexpr Scale(NoteName root, ScalePattern pattern) noexcept
        : _root(root.IsValid() && pattern.IsValid() ? root : NoteName::Invalid()),
          _pattern(root.IsValid() && pattern.IsValid() ? pattern : ScalePattern::Invalid()) {}

    /** @brief Returns the invalid scale. */
    static constexpr Scale Invalid() noexcept { return Scale(); }

    /** @brief Returns `true` unless this is the invalid scale. */
    constexpr bool IsValid() const noexcept { return _pattern.IsValid(); }

    /** @brief Returns the root note name. */
    constexpr NoteName Root() const noexcept { return _root; }

    /** @brief Returns the root-independent pattern. */
    constexpr ScalePattern Pattern() const noexcept { return _pattern; }

    /** @brief Returns the number of degrees, or 0 for the invalid scale. */
    MCC_CONSTEXPR14 uint8_t DegreeCount() const noexcept { return _pattern.DegreeCount(); }

    /**
     * @brief Returns the note name of `degree` (1-based), or the invalid note
     * name outside the scale or when it cannot be spelled.
     */
    MCC_CONSTEXPR14 NoteName NoteAt(int32_t degree) const noexcept {
        return _root + _pattern.DegreeInterval(degree);
    }

    /**
     * @brief Returns the pitch of `degree` when the root is placed in
     * `rootOctave`; degrees above the root may fall in the next octave.
     */
    MCC_CONSTEXPR14 MCC::Pitch PitchAt(int32_t degree, int32_t rootOctave) const noexcept {
        return MCC::Pitch(_root, rootOctave) + _pattern.DegreeInterval(degree);
    }

    /**
     * @brief Returns the 1-based degree written exactly as `noteName`, or 0
     * when no degree has that spelling.
     */
    MCC_CONSTEXPR14 uint8_t DegreeOf(NoteName noteName) const noexcept {
        if (!noteName.IsValid()) {
            return 0;
        }
        const uint8_t count = DegreeCount();
        for (uint8_t degree = 1; degree <= count; ++degree) {
            if (NoteAt(degree) == noteName) {
                return degree;
            }
        }
        return 0;
    }

    /** @brief Returns `true` when a degree is written exactly as `noteName`. */
    MCC_CONSTEXPR14 bool Contains(NoteName noteName) const noexcept {
        return DegreeOf(noteName) != 0;
    }

    /**
     * @brief Returns `true` when any degree sounds as `pitchClass`, regardless
     * of spelling (explicit enharmonic membership, SPEC-EQ-2).
     */
    constexpr bool ContainsPitchClass(MCC::PitchClass pitchClass) const noexcept {
        return IsValid() && pitchClass.IsValid() &&
            _pattern.ContainsSemitone(
                static_cast<int32_t>(pitchClass.Value()) - _root.PitchClass().Value());
    }

    /** @brief Compares roots by spelling and patterns by degrees. */
    friend constexpr bool operator==(const Scale& a, const Scale& b) noexcept {
        return a._root == b._root && a._pattern == b._pattern;
    }

    /** @brief Negation of `operator==`. */
    friend constexpr bool operator!=(const Scale& a, const Scale& b) noexcept {
        return !(a == b);
    }
};

} // namespace MCC

#endif // MCC_SCALE_SCALE_H
