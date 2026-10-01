#ifndef MCC_INTERVAL_TRANSPOSITION_H
#define MCC_INTERVAL_TRANSPOSITION_H

#include <MCC_BuildSettings.h>

#include <stdint.h>

#include <Foundation/Math/Arithmetic.h>

#include <MCC/Interval/Interval.h>
#include <MCC/Pitch/Accidental.h>
#include <MCC/Pitch/Letter.h>
#include <MCC/Pitch/NoteName.h>
#include <MCC/Pitch/Pitch.h>

namespace MCC {

/**
 * @brief Returns the directed interval from `from` to `to` (SPEC-INT-1):
 * the difference of their diatonic and chromatic indices. `B#3` to `C4` is
 * an ascending diminished second; `C4` to `Cb4` is a descending augmented
 * unison (SPEC-INT-5).
 *
 * The result is invalid when either pitch is invalid or the quality would
 * need more than four augmentations or diminutions (for example `Cbbbb4` to
 * `C####4`).
 * @ingroup MCC_Interval
 */
MCC_CONSTEXPR14 Interval IntervalBetween(Pitch from, Pitch to) noexcept {
    if (!from.IsValid() || !to.IsValid()) {
        return Interval::Invalid();
    }
    return Interval::FromSteps(
        static_cast<int32_t>(to.DiatonicIndex()) - from.DiatonicIndex(),
        static_cast<int32_t>(to.ChromaticIndex().Value()) -
            from.ChromaticIndex().Value());
}

/**
 * @brief Returns the interval from `from` up to the next `to`, which is a
 * simple ascending interval of 0-6 steps: `B` to `C` is a minor second and
 * `E` to `C` is a minor sixth. Between two spellings of the same letter the
 * result is a unison, descending when `to` is lower (`C` to `Cb`,
 * SPEC-INT-5).
 * @ingroup MCC_Interval
 */
MCC_CONSTEXPR14 Interval IntervalBetween(NoteName from, NoteName to) noexcept {
    if (!from.IsValid() || !to.IsValid()) {
        return Interval::Invalid();
    }
    const int32_t fromIndex = DiatonicIndex(from.Letter());
    const int32_t toIndex = DiatonicIndex(to.Letter());
    const int32_t steps = Foundation::Math::FloorMod(toIndex - fromIndex, LetterCount);
    const int32_t wrap = (toIndex < fromIndex) ? 12 : 0;
    const int32_t semitones =
        NaturalSemitone(to.Letter()) + to.Accidental().Semitones() + wrap -
        NaturalSemitone(from.Letter()) - from.Accidental().Semitones();
    return Interval::FromSteps(steps, semitones);
}

/**
 * @brief Transposes `pitch` by `interval` preserving spelling (SPEC-INT-7):
 * the letter moves by the diatonic steps and the accidental is whatever the
 * semitones require. `E4 + major third = G#4`; `B3 + minor second = C4`.
 *
 * The result is invalid when an operand is invalid, the accidental would
 * leave `[-4, +4]` (SPEC-ACC-3) or the octave would leave `[-128, 127]`
 * (SPEC-OCT-4).
 * @ingroup MCC_Interval
 */
MCC_CONSTEXPR14 Pitch operator+(Pitch pitch, Interval interval) noexcept {
    if (!pitch.IsValid() || !interval.IsValid()) {
        return Pitch::Invalid();
    }
    const int32_t diatonic =
        static_cast<int32_t>(pitch.DiatonicIndex()) + interval.DiatonicSteps();
    const int32_t chromatic =
        static_cast<int32_t>(pitch.ChromaticIndex().Value()) + interval.Semitones();
    const Letter letter =
        static_cast<Letter>(Foundation::Math::FloorMod(diatonic, LetterCount));
    const int32_t octave = Foundation::Math::FloorDiv(diatonic, LetterCount);
    const int32_t natural = (octave + 1) * 12 + NaturalSemitone(letter);
    return Pitch(letter, Accidental(chromatic - natural), octave);
}

/**
 * @brief Transposes `pitch` down by `interval`: `pitch + interval.Reversed()`.
 * @ingroup MCC_Interval
 */
MCC_CONSTEXPR14 Pitch operator-(Pitch pitch, Interval interval) noexcept {
    return pitch + interval.Reversed();
}

/**
 * @brief Transposes a note name by `interval` preserving spelling
 * (SPEC-INT-7): `E + major third = G#`, `B + minor second = C`. Octaves in
 * the interval do not change a note name.
 *
 * The result is invalid when an operand is invalid or the accidental would
 * leave `[-4, +4]` (SPEC-ACC-3).
 * @ingroup MCC_Interval
 */
MCC_CONSTEXPR14 NoteName operator+(NoteName noteName, Interval interval) noexcept {
    if (!noteName.IsValid() || !interval.IsValid()) {
        return NoteName::Invalid();
    }
    // Write the note name in octave 0, transpose it by the simple interval
    // (at most one octave, so the octave stays in range) and drop the
    // octave. An accidental overflow yields the invalid pitch, whose note
    // name is invalid.
    return (Pitch(noteName, 0) + interval.Simple()).NoteName();
}

/**
 * @brief Transposes a note name down by `interval`.
 * @ingroup MCC_Interval
 */
MCC_CONSTEXPR14 NoteName operator-(NoteName noteName, Interval interval) noexcept {
    return noteName + interval.Reversed();
}

} // namespace MCC

#endif // MCC_INTERVAL_TRANSPOSITION_H
