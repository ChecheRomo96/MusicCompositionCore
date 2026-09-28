#ifndef MCC_PITCH_PITCH_H
#define MCC_PITCH_PITCH_H

#include <stdint.h>

#include <Foundation/Math/Arithmetic.h>

#include <MCC/Pitch/Accidental.h>
#include <MCC/Pitch/ChromaticClass.h>
#include <MCC/Pitch/ChromaticIndex.h>
#include <MCC/Pitch/Letter.h>
#include <MCC/Pitch/PitchClass.h>

namespace MCC {

/**
 * @brief Written absolute pitch: a pitch class plus an octave.
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
 * Default construction, an invalid pitch class or an out-of-range octave
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
    MCC::PitchClass _pitchClass;
    int8_t _octave;

public:
    /** @brief Creates the invalid pitch (SPEC-ERR-2). */
    constexpr Pitch() noexcept : _pitchClass(), _octave(0) {}

    /**
     * @brief Creates `pitchClass` written in `octave`. An invalid pitch
     * class or an octave outside `[-128, 127]` produces the invalid pitch
     * (SPEC-ERR-3).
     */
    constexpr Pitch(MCC::PitchClass pitchClass, int32_t octave) noexcept
        : _pitchClass(IsWritable(pitchClass, octave)
              ? pitchClass
              : MCC::PitchClass::Invalid()),
          _octave(IsWritable(pitchClass, octave)
              ? static_cast<int8_t>(octave)
              : 0) {}

    /** @brief Creates `letter` + `accidental` written in `octave`. */
    constexpr Pitch(MCC::Letter letter, MCC::Accidental accidental,
                    int32_t octave) noexcept
        : Pitch(MCC::PitchClass(letter, accidental), octave) {}

    /** @brief Creates the natural `letter` written in `octave`. */
    constexpr Pitch(MCC::Letter letter, int32_t octave) noexcept
        : Pitch(MCC::PitchClass(letter), octave) {}

    /** @brief Returns the invalid pitch. */
    static constexpr Pitch Invalid() noexcept { return Pitch(); }

    /** @brief Returns `true` unless this is the invalid pitch. */
    constexpr bool IsValid() const noexcept { return _pitchClass.IsValid(); }

    /** @brief Returns the written pitch class; invalid for the invalid pitch. */
    constexpr MCC::PitchClass PitchClass() const noexcept { return _pitchClass; }

    /**
     * @brief Returns the written letter, or `Letter::C` for the invalid
     * pitch (SPEC-ERR-7).
     */
    constexpr MCC::Letter Letter() const noexcept { return _pitchClass.Letter(); }

    /** @brief Returns the written accidental; invalid for the invalid pitch. */
    constexpr MCC::Accidental Accidental() const noexcept {
        return _pitchClass.Accidental();
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
    constexpr int16_t DiatonicIndex() const noexcept {
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
    constexpr MCC::ChromaticIndex ChromaticIndex() const noexcept {
        if (!IsValid()) {
            return MCC::ChromaticIndex::Invalid();
        }
        return MCC::ChromaticIndex(
            (static_cast<int32_t>(_octave) + 1) * MCC::ChromaticClass::Count +
            NaturalSemitone(Letter()) + Accidental().Semitones());
    }

    /**
     * @brief Returns the chromatic class of the written pitch class
     * (SPEC-ORD-4); the invalid pitch yields the invalid class.
     */
    constexpr MCC::ChromaticClass ChromaticClass() const noexcept {
        return _pitchClass.ChromaticClass();
    }

    /**
     * @brief Moves the letter by `steps` diatonic letters, changing octave
     * between `B` and `C`, and keeps the written accidental: `B#3` moved
     * by 1 is `C#4`.
     *
     * The result is invalid when the octave leaves `[-128, 127]`
     * (SPEC-OCT-4, SPEC-ERR-5).
     */
    constexpr Pitch MovedDiatonically(int32_t steps) const noexcept {
        if (!IsValid() || steps < -2 * DiatonicSpan || steps > 2 * DiatonicSpan) {
            return Invalid();
        }
        const int32_t index = DiatonicIndex() + steps;
        return Pitch(
            MCC::PitchClass(
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
    constexpr Pitch Altered(int32_t semitones) const noexcept {
        if (!IsValid()) {
            return Invalid();
        }
        return Pitch(_pitchClass.Altered(semitones), _octave);
    }

    /**
     * @brief Moves the pitch by `octaves` octaves, keeping its spelling. The
     * result is invalid outside `[-128, 127]` (SPEC-OCT-4).
     */
    constexpr Pitch MovedByOctaves(int32_t octaves) const noexcept {
        if (!IsValid() ||
            octaves < MinimumOctave - MaximumOctave ||
            octaves > MaximumOctave - MinimumOctave) {
            return Invalid();
        }
        return Pitch(_pitchClass, _octave + octaves);
    }

    /**
     * @brief Written equality: letter, accidental and octave (SPEC-EQ-1).
     * All invalid pitches are equal (SPEC-ERR-6).
     */
    friend constexpr bool operator==(Pitch a, Pitch b) noexcept {
        return a._pitchClass == b._pitchClass && a._octave == b._octave;
    }

    friend constexpr bool operator!=(Pitch a, Pitch b) noexcept {
        return !(a == b);
    }

    /**
     * @brief Written order: octave, then letter, then accidental
     * (SPEC-ORD-5). `B#3 < Cb4` although `B#3` sounds higher. The invalid
     * pitch sorts last.
     */
    friend constexpr bool operator<(Pitch a, Pitch b) noexcept {
        if (!a.IsValid() || !b.IsValid()) {
            return a.IsValid() && !b.IsValid();
        }
        return (a._octave != b._octave)
            ? a._octave < b._octave
            : a._pitchClass < b._pitchClass;
    }

    friend constexpr bool operator>(Pitch a, Pitch b) noexcept {
        return b < a;
    }

    friend constexpr bool operator<=(Pitch a, Pitch b) noexcept {
        return !(b < a);
    }

    friend constexpr bool operator>=(Pitch a, Pitch b) noexcept {
        return !(a < b);
    }

private:
    // Number of diatonic positions between the lowest and highest pitch.
    static constexpr int32_t DiatonicSpan =
        (static_cast<int32_t>(MaximumOctave) - MinimumOctave + 1) * LetterCount;

    static constexpr bool IsWritable(MCC::PitchClass pitchClass,
                                     int32_t octave) noexcept {
        return pitchClass.IsValid() &&
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
constexpr bool IsLowerThan(Pitch a, Pitch b) noexcept {
    if (!a.IsValid() || !b.IsValid()) {
        return a.IsValid() && !b.IsValid();
    }
    return (a.ChromaticIndex() != b.ChromaticIndex())
        ? a.ChromaticIndex() < b.ChromaticIndex()
        : a < b;
}

} // namespace MCC

#endif // MCC_PITCH_PITCH_H
