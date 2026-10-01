#ifndef MCC_PITCH_NOTE_NAME_H
#define MCC_PITCH_NOTE_NAME_H

#include <MCC_BuildSettings.h>

#include <stdint.h>

#include <Foundation/Math/Arithmetic.h>

#include <MCC/Pitch/Accidental.h>
#include <MCC/Pitch/PitchClass.h>
#include <MCC/Pitch/Letter.h>

namespace MCC {

/**
 * @brief Written note name: a letter plus an accidental, without octave.
 * @ingroup MCC_Pitch
 *
 * The spelling is preserved: `C#` and `Db` are different note names that
 * share a pitch class (SPEC-EQ-1). Enharmonic equivalence is tested only
 * through `MCC::IsEnharmonic()` (SPEC-EQ-2), and no implicit conversion to
 * `PitchClass` exists (SPEC-EQ-3).
 *
 * Default construction, a non-enumerator `Letter` or an invalid accidental
 * produce the single invalid value (SPEC-ERR-1..3). Operations on the
 * invalid value return the invalid value (SPEC-ERR-4).
 */
class NoteName {
    static constexpr uint8_t InvalidLetter = 0xFF;

    uint8_t _letter;
    MCC::Accidental _accidental;

public:
    /** @brief Creates the invalid note name (SPEC-ERR-2). */
    constexpr NoteName() noexcept
        : _letter(InvalidLetter), _accidental(MCC::Accidental::Invalid()) {}

    /**
     * @brief Creates the note name spelled `letter` + `accidental`.
     *
     * An invalid accidental or a `Letter` outside the enumerators produces
     * the invalid note name (SPEC-ERR-3).
     */
    constexpr NoteName(MCC::Letter letter, MCC::Accidental accidental) noexcept
        : _letter(IsSpellable(letter, accidental)
              ? static_cast<uint8_t>(letter)
              : InvalidLetter),
          _accidental(IsSpellable(letter, accidental)
              ? accidental
              : MCC::Accidental::Invalid()) {}

    /** @brief Creates the natural note name of `letter`. */
    constexpr explicit NoteName(MCC::Letter letter) noexcept
        : NoteName(letter, MCC::Accidental::Natural()) {}

    /** @brief Returns the invalid note name. */
    static constexpr NoteName Invalid() noexcept { return NoteName(); }

    /** @brief Returns `true` unless this is the invalid note name. */
    constexpr bool IsValid() const noexcept { return _letter != InvalidLetter; }

    /**
     * @brief Returns the written letter, or `Letter::C` for the invalid
     * note name (SPEC-ERR-7).
     */
    constexpr MCC::Letter Letter() const noexcept {
        return IsValid() ? static_cast<MCC::Letter>(_letter) : MCC::Letter::C;
    }

    /**
     * @brief Returns the written accidental; invalid for the invalid note
     * name.
     */
    constexpr MCC::Accidental Accidental() const noexcept { return _accidental; }

    /**
     * @brief Returns `(NaturalSemitone(letter) + accidental) mod 12`, always
     * in `[0, 11]` (SPEC-ORD-4). The invalid note name yields the invalid
     * pitch class (SPEC-ERR-4).
     */
    MCC_CONSTEXPR14 MCC::PitchClass PitchClass() const noexcept {
        if (!IsValid()) {
            return MCC::PitchClass::Invalid();
        }
        return MCC::PitchClass(Foundation::Math::FloorMod(
            NaturalSemitone(Letter()) + _accidental.Semitones(),
            MCC::PitchClass::Count));
    }

    /**
     * @brief Moves the letter by `steps` diatonic letters and keeps the
     * written accidental: `C#` moved by 2 is `E#`, `B` moved by 1 is `C`.
     *
     * The spelling is never rewritten, so the accidental of a valid note
     * name always remains within `[-4, +4]` (SPEC-ACC-3).
     */
    MCC_CONSTEXPR14 NoteName MovedDiatonically(int32_t steps) const noexcept {
        if (!IsValid()) {
            return Invalid();
        }
        return NoteName(MoveLetter(Letter(), steps), _accidental);
    }

    /**
     * @brief Keeps the letter and alters the accidental by `semitones`:
     * `C#` altered by +1 is `C##`, never `D`.
     *
     * A result outside `[-4, +4]` is the invalid note name; the note is
     * never respelled with another letter (SPEC-ACC-3, SPEC-ERR-5).
     */
    MCC_CONSTEXPR14 NoteName Altered(int32_t semitones) const noexcept {
        if (!IsValid()) {
            return Invalid();
        }
        return NoteName(Letter(), _accidental.Altered(semitones));
    }

    /**
     * @brief Written equality: letter and accidental (SPEC-EQ-1).
     * All invalid note names are equal (SPEC-ERR-6).
     */
    friend constexpr bool operator==(NoteName a, NoteName b) noexcept {
        return a._letter == b._letter && a._accidental == b._accidental;
    }

    friend constexpr bool operator!=(NoteName a, NoteName b) noexcept {
        return !(a == b);
    }

    /**
     * @brief Written order: letter, then accidental (SPEC-ORD-5).
     * The invalid note name sorts last.
     */
    friend constexpr bool operator<(NoteName a, NoteName b) noexcept {
        return (a._letter != b._letter)
            ? a._letter < b._letter
            : a._accidental < b._accidental;
    }

    friend constexpr bool operator>(NoteName a, NoteName b) noexcept {
        return b < a;
    }

    friend constexpr bool operator<=(NoteName a, NoteName b) noexcept {
        return !(b < a);
    }

    friend constexpr bool operator>=(NoteName a, NoteName b) noexcept {
        return !(a < b);
    }

private:
    static constexpr bool IsSpellable(
        MCC::Letter letter,
        MCC::Accidental accidental
    ) noexcept {
        return Detail::IsLetter(letter) && accidental.IsValid();
    }
};

/**
 * @brief Returns `true` when `a` and `b` are valid and share a pitch
 * class (SPEC-EQ-2). `IsEnharmonic(C#, Db)` is `true`; any invalid operand
 * yields `false` (SPEC-ERR-6).
 * @ingroup MCC_Pitch
 */
constexpr bool IsEnharmonic(NoteName a, NoteName b) noexcept {
    return a.IsValid() && b.IsValid() && a.PitchClass() == b.PitchClass();
}

} // namespace MCC

#endif // MCC_PITCH_NOTE_NAME_H
