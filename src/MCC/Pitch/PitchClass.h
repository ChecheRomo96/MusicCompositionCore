#ifndef MCC_PITCH_PITCH_CLASS_H
#define MCC_PITCH_PITCH_CLASS_H

#include <stdint.h>

#include <Foundation/Math/Arithmetic.h>

#include <MCC/Pitch/Accidental.h>
#include <MCC/Pitch/ChromaticClass.h>
#include <MCC/Pitch/Letter.h>

namespace MCC {

/**
 * @brief Written pitch class: a letter plus an accidental, without octave.
 * @ingroup MCC_Pitch
 *
 * The spelling is preserved: `C#` and `Db` are different pitch classes that
 * share a chromatic class (SPEC-EQ-1). Enharmonic equivalence is tested only
 * through `MCC::IsEnharmonic()` (SPEC-EQ-2), and no implicit conversion to
 * `ChromaticClass` exists (SPEC-EQ-3).
 *
 * Default construction, a non-enumerator `Letter` or an invalid accidental
 * produce the single invalid value (SPEC-ERR-1..3). Operations on the
 * invalid value return the invalid value (SPEC-ERR-4).
 */
class PitchClass {
    static constexpr uint8_t InvalidLetter = 0xFF;

    uint8_t _letter;
    MCC::Accidental _accidental;

public:
    /** @brief Creates the invalid pitch class (SPEC-ERR-2). */
    constexpr PitchClass() noexcept
        : _letter(InvalidLetter), _accidental(MCC::Accidental::Invalid()) {}

    /**
     * @brief Creates the pitch class spelled `letter` + `accidental`.
     *
     * An invalid accidental or a `Letter` outside the enumerators produces
     * the invalid pitch class (SPEC-ERR-3).
     */
    constexpr PitchClass(MCC::Letter letter, MCC::Accidental accidental) noexcept
        : _letter(IsSpellable(letter, accidental)
              ? static_cast<uint8_t>(letter)
              : InvalidLetter),
          _accidental(IsSpellable(letter, accidental)
              ? accidental
              : MCC::Accidental::Invalid()) {}

    /** @brief Creates the natural pitch class of `letter`. */
    constexpr explicit PitchClass(MCC::Letter letter) noexcept
        : PitchClass(letter, MCC::Accidental::Natural()) {}

    /** @brief Returns the invalid pitch class. */
    static constexpr PitchClass Invalid() noexcept { return PitchClass(); }

    /** @brief Returns `true` unless this is the invalid pitch class. */
    constexpr bool IsValid() const noexcept { return _letter != InvalidLetter; }

    /**
     * @brief Returns the written letter, or `Letter::C` for the invalid
     * pitch class (SPEC-ERR-7).
     */
    constexpr MCC::Letter Letter() const noexcept {
        return IsValid() ? static_cast<MCC::Letter>(_letter) : MCC::Letter::C;
    }

    /**
     * @brief Returns the written accidental; invalid for the invalid pitch
     * class.
     */
    constexpr MCC::Accidental Accidental() const noexcept { return _accidental; }

    /**
     * @brief Returns `(NaturalSemitone(letter) + accidental) mod 12`, always
     * in `[0, 11]` (SPEC-ORD-4). The invalid pitch class yields the invalid
     * chromatic class (SPEC-ERR-4).
     */
    constexpr MCC::ChromaticClass ChromaticClass() const noexcept {
        if (!IsValid()) {
            return MCC::ChromaticClass::Invalid();
        }
        return MCC::ChromaticClass(Foundation::Math::FloorMod(
            NaturalSemitone(Letter()) + _accidental.Semitones(),
            MCC::ChromaticClass::Count));
    }

    /**
     * @brief Moves the letter by `steps` diatonic letters and keeps the
     * written accidental: `C#` moved by 2 is `E#`, `B` moved by 1 is `C`.
     *
     * The spelling is never rewritten, so the accidental of a valid pitch
     * class always remains within `[-4, +4]` (SPEC-ACC-3).
     */
    constexpr PitchClass MovedDiatonically(int steps) const noexcept {
        if (!IsValid()) {
            return Invalid();
        }
        return PitchClass(MoveLetter(Letter(), steps), _accidental);
    }

    /**
     * @brief Keeps the letter and alters the accidental by `semitones`:
     * `C#` altered by +1 is `C##`, never `D`.
     *
     * A result outside `[-4, +4]` is the invalid pitch class; the note is
     * never respelled with another letter (SPEC-ACC-3, SPEC-ERR-5).
     */
    constexpr PitchClass Altered(int semitones) const noexcept {
        if (!IsValid()) {
            return Invalid();
        }
        return PitchClass(Letter(), _accidental.Altered(semitones));
    }

    /**
     * @brief Written equality: letter and accidental (SPEC-EQ-1).
     * All invalid pitch classes are equal (SPEC-ERR-6).
     */
    friend constexpr bool operator==(PitchClass a, PitchClass b) noexcept {
        return a._letter == b._letter && a._accidental == b._accidental;
    }

    friend constexpr bool operator!=(PitchClass a, PitchClass b) noexcept {
        return !(a == b);
    }

    /**
     * @brief Written order: letter, then accidental (SPEC-ORD-5).
     * The invalid pitch class sorts last.
     */
    friend constexpr bool operator<(PitchClass a, PitchClass b) noexcept {
        return (a._letter != b._letter)
            ? a._letter < b._letter
            : a._accidental < b._accidental;
    }

    friend constexpr bool operator>(PitchClass a, PitchClass b) noexcept {
        return b < a;
    }

    friend constexpr bool operator<=(PitchClass a, PitchClass b) noexcept {
        return !(b < a);
    }

    friend constexpr bool operator>=(PitchClass a, PitchClass b) noexcept {
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
 * @brief Returns `true` when `a` and `b` are valid and share a chromatic
 * class (SPEC-EQ-2). `IsEnharmonic(C#, Db)` is `true`; any invalid operand
 * yields `false` (SPEC-ERR-6).
 * @ingroup MCC_Pitch
 */
constexpr bool IsEnharmonic(PitchClass a, PitchClass b) noexcept {
    return a.IsValid() && b.IsValid() && a.ChromaticClass() == b.ChromaticClass();
}

} // namespace MCC

#endif // MCC_PITCH_PITCH_CLASS_H
