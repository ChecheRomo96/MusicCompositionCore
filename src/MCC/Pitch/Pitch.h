#ifndef MCC_PITCH_PITCH_H
#define MCC_PITCH_PITCH_H

#include <MCC_BuildSettings.h>

#include <stdint.h>

#include <Foundation/Math/Arithmetic.h>

#include <MCC/Pitch/Accidental.h>
#include <MCC/Pitch/PitchClass.h>
#include <MCC/Pitch/ChromaticIndex.h>
#include <MCC/Pitch/Letter.h>
#include <MCC/Pitch/NoteName.h>

namespace MCC {

/**
 * @brief Written absolute pitch: a note name plus an octave.
 * @ingroup MCC_Pitch
 *
 * MCC uses scientific pitch notation: middle C is `C4` (SPEC-OCT-1). The
 * octave belongs to the written letter, so `B#3` is written in octave 3 and
 * sounds as `C4` (SPEC-OCT-3). Octaves range from -128 to 127 (SPEC-OCT-4).
 *
 * `operator==` and `operator<` compare the written pitch (SPEC-EQ-1,
 * SPEC-ORD-5); sounding pitch is compared through `ChromaticIndex()`,
 * `MCC::IsEnharmonic()` and `MCC::IsLowerThan()` (SPEC-EQ-2, SPEC-ORD-6).
 *
 * Default construction, an invalid note name or an out-of-range octave
 * produce the single invalid value (SPEC-ERR-1..3). Operations on the
 * invalid value, and operations whose result leaves the octave or
 * accidental ranges, return the invalid value (SPEC-ERR-4, SPEC-ERR-5).
 */
class Pitch {
public:
    /** @brief Lowest supported octave. */
    static constexpr int8_t MinimumOctave = -128;

    /** @brief Highest supported octave. */
    static constexpr int8_t MaximumOctave = 127;

    /**
     * @brief Sentinel returned by `DiatonicIndex()` for the invalid pitch
     * (SPEC-ERR-7). Do not rely on it; check `IsValid()`.
     */
    static constexpr int16_t InvalidDiatonicIndex = 32767;

private:
    MCC::NoteName _noteName;
    int8_t _octave;

public:
    /** @brief Creates the invalid pitch (SPEC-ERR-2). */
    constexpr Pitch() noexcept : _noteName(), _octave(0) {}

    /**
     * @brief Creates `noteName` written in `octave`. An invalid note
     * name or an octave outside `[-128, 127]` produces the invalid pitch
     * (SPEC-ERR-3).
     */
    constexpr Pitch(MCC::NoteName noteName, int32_t octave) noexcept
        : _noteName(IsWritable(noteName, octave)
              ? noteName
              : MCC::NoteName::Invalid()),
          _octave(IsWritable(noteName, octave)
              ? static_cast<int8_t>(octave)
              : static_cast<int8_t>(0)) {}

    /** @brief Creates `letter` + `accidental` written in `octave`. */
    constexpr Pitch(MCC::Letter letter, MCC::Accidental accidental,
                    int32_t octave) noexcept
        : Pitch(MCC::NoteName(letter, accidental), octave) {}

    /** @brief Creates the natural `letter` written in `octave`. */
    constexpr Pitch(MCC::Letter letter, int32_t octave) noexcept
        : Pitch(MCC::NoteName(letter), octave) {}

    /** @brief Returns the invalid pitch. */
    static constexpr Pitch Invalid() noexcept { return Pitch(); }

    /** @brief Returns `true` unless this is the invalid pitch. */
    constexpr bool IsValid() const noexcept { return _noteName.IsValid(); }

    /** @brief Returns the written note name; invalid for the invalid pitch. */
    constexpr MCC::NoteName NoteName() const noexcept { return _noteName; }

    /**
     * @brief Returns the written letter, or `Letter::C` for the invalid
     * pitch (SPEC-ERR-7).
     */
    constexpr MCC::Letter Letter() const noexcept { return _noteName.Letter(); }

    /** @brief Returns the written accidental; invalid for the invalid pitch. */
    constexpr MCC::Accidental Accidental() const noexcept {
        return _noteName.Accidental();
    }

    /**
     * @brief Returns the written octave, or `0` for the invalid pitch
     * (SPEC-ERR-7).
     */
    constexpr int8_t Octave() const noexcept { return _octave; }

    /**
     * @brief Returns `octave * 7 + letterIndex` (SPEC-ORD-2), or
     * `InvalidDiatonicIndex` for the invalid pitch (SPEC-ERR-7).
     */
    MCC_CONSTEXPR14 int16_t DiatonicIndex() const noexcept {
        if (!IsValid()) {
            return InvalidDiatonicIndex;
        }
        return static_cast<int16_t>(
            _octave * LetterCount + MCC::DiatonicIndex(Letter()));
    }

    /**
     * @brief Returns `(octave + 1) * 12 + letterSemitone + accidental`
     * (SPEC-ORD-3); the invalid pitch yields the invalid index.
     */
    MCC_CONSTEXPR14 MCC::ChromaticIndex ChromaticIndex() const noexcept {
        if (!IsValid()) {
            return MCC::ChromaticIndex::Invalid();
        }
        return MCC::ChromaticIndex(
            (static_cast<int32_t>(_octave) + 1) * MCC::PitchClass::Count +
            NaturalSemitone(Letter()) + Accidental().Semitones());
    }

    /**
     * @brief Returns the pitch class of the written note name
     * (SPEC-ORD-4); the invalid pitch yields the invalid class.
     */
    MCC_CONSTEXPR14 MCC::PitchClass PitchClass() const noexcept {
        return _noteName.PitchClass();
    }

    /**
     * @brief Moves the letter by `steps` diatonic letters, changing octave
     * between `B` and `C`, and keeps the written accidental: `B#3` moved
     * by 1 is `C#4`.
     *
     * The result is invalid when the octave leaves `[-128, 127]`
     * (SPEC-OCT-4, SPEC-ERR-5).
     */
    MCC_CONSTEXPR14 Pitch MovedDiatonically(int32_t steps) const noexcept {
        if (!IsValid() || steps < -2 * DiatonicSpan || steps > 2 * DiatonicSpan) {
            return Invalid();
        }
        const int32_t index = DiatonicIndex() + steps;
        return Pitch(
            MCC::NoteName(
                static_cast<MCC::Letter>(
                    Foundation::Math::FloorMod(index, LetterCount)),
                Accidental()),
            Foundation::Math::FloorDiv(index, LetterCount));
    }

    /**
     * @brief Keeps the letter and octave and alters the accidental by
     * `semitones`; outside `[-4, +4]` the result is invalid and is never
     * respelled (SPEC-ACC-3).
     */
    MCC_CONSTEXPR14 Pitch Altered(int32_t semitones) const noexcept {
        if (!IsValid()) {
            return Invalid();
        }
        return Pitch(_noteName.Altered(semitones), _octave);
    }

    /**
     * @brief Moves the pitch by `octaves` octaves, keeping its spelling. The
     * result is invalid outside `[-128, 127]` (SPEC-OCT-4).
     */
    MCC_CONSTEXPR14 Pitch MovedByOctaves(int32_t octaves) const noexcept {
        if (!IsValid() ||
            octaves < MinimumOctave - MaximumOctave ||
            octaves > MaximumOctave - MinimumOctave) {
            return Invalid();
        }
        return Pitch(_noteName, _octave + octaves);
    }

    /**
     * @brief Written equality: letter, accidental and octave (SPEC-EQ-1).
     * All invalid pitches are equal (SPEC-ERR-6).
     */
    friend constexpr bool operator==(Pitch a, Pitch b) noexcept {
        return a._noteName == b._noteName && a._octave == b._octave;
    }

    friend constexpr bool operator!=(Pitch a, Pitch b) noexcept {
        return !(a == b);
    }

    /**
     * @brief Written order: octave, then letter, then accidental
     * (SPEC-ORD-5). `B#3 < Cb4` although `B#3` sounds higher. The invalid
     * pitch sorts last.
     */
    friend MCC_CONSTEXPR14 bool operator<(Pitch a, Pitch b) noexcept {
        if (!a.IsValid() || !b.IsValid()) {
            return a.IsValid() && !b.IsValid();
        }
        return (a._octave != b._octave)
            ? a._octave < b._octave
            : a._noteName < b._noteName;
    }

    friend MCC_CONSTEXPR14 bool operator>(Pitch a, Pitch b) noexcept {
        return b < a;
    }

    friend MCC_CONSTEXPR14 bool operator<=(Pitch a, Pitch b) noexcept {
        return !(b < a);
    }

    friend MCC_CONSTEXPR14 bool operator>=(Pitch a, Pitch b) noexcept {
        return !(a < b);
    }

private:
    // Number of diatonic positions between the lowest and highest pitch.
    static constexpr int32_t DiatonicSpan =
        (static_cast<int32_t>(MaximumOctave) - MinimumOctave + 1) * LetterCount;

    static constexpr bool IsWritable(MCC::NoteName noteName,
                                     int32_t octave) noexcept {
        return noteName.IsValid() &&
            octave >= MinimumOctave && octave <= MaximumOctave;
    }
};

/**
 * @brief Returns `true` when `a` and `b` are valid and have the same
 * chromatic index (SPEC-EQ-2): `B#3` and `C4` are enharmonic, `B#3` and
 * `C3` are not. Any invalid operand yields `false` (SPEC-ERR-6).
 * @ingroup MCC_Pitch
 */
constexpr bool IsEnharmonic(Pitch a, Pitch b) noexcept {
    return a.IsValid() && b.IsValid() && a.ChromaticIndex() == b.ChromaticIndex();
}

/**
 * @brief Pitch-height order (SPEC-ORD-6): `true` when `a` sounds lower than
 * `b`, with enharmonic ties broken by written order so that sorting is
 * deterministic. The invalid pitch sorts last.
 * @ingroup MCC_Pitch
 */
MCC_CONSTEXPR14 bool IsLowerThan(Pitch a, Pitch b) noexcept {
    if (!a.IsValid() || !b.IsValid()) {
        return a.IsValid() && !b.IsValid();
    }
    return (a.ChromaticIndex() != b.ChromaticIndex())
        ? a.ChromaticIndex() < b.ChromaticIndex()
        : a < b;
}

} // namespace MCC

#endif // MCC_PITCH_PITCH_H
