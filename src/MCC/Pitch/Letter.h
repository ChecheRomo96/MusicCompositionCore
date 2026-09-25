#ifndef MCC_PITCH_LETTER_H
#define MCC_PITCH_LETTER_H

#include <stdint.h>

#include <MCC/Pitch/Detail/Modulo.h>

namespace MCC {

/**
 * @brief Diatonic letter name.
 * @ingroup MCC_Pitch
 *
 * Closed enumeration ordered `C D E F G A B` with diatonic indices 0-6
 * (SPEC-ORD-1). Every enumerator is valid; `Letter` has no invalid state
 * (SPEC-ERR-1). Values produced by casting integers outside 0-6 are not
 * letters: `PitchClass` rejects them and the queries below treat them as
 * `Letter::C`.
 */
enum class Letter : uint8_t {
    C = 0,
    D = 1,
    E = 2,
    F = 3,
    G = 4,
    A = 5,
    B = 6
};

/** @brief Number of diatonic letters. @ingroup MCC_Pitch */
constexpr uint8_t LetterCount = 7;

/** @cond */
namespace Detail {

constexpr bool IsLetter(Letter letter) noexcept {
    return static_cast<uint8_t>(letter) < LetterCount;
}

} // namespace Detail
/** @endcond */

/**
 * @brief Returns the diatonic index of `letter`: `C = 0` ... `B = 6`.
 * @ingroup MCC_Pitch
 */
constexpr uint8_t DiatonicIndex(Letter letter) noexcept {
    return Detail::IsLetter(letter) ? static_cast<uint8_t>(letter) : 0;
}

/**
 * @brief Returns the semitone offset of the natural `letter` above `C`:
 * `0 2 4 5 7 9 11` (SPEC-ORD-1).
 * @ingroup MCC_Pitch
 */
constexpr uint8_t NaturalSemitone(Letter letter) noexcept {
    constexpr uint8_t semitones[LetterCount] = {0, 2, 4, 5, 7, 9, 11};
    return semitones[DiatonicIndex(letter)];
}

/**
 * @brief Moves `letter` by `steps` diatonic letters, wrapping around the
 * octave: `MoveLetter(Letter::B, 1) == Letter::C`.
 * @ingroup MCC_Pitch
 */
constexpr Letter MoveLetter(Letter letter, int steps) noexcept {
    return static_cast<Letter>(Detail::FloorMod(
        DiatonicIndex(letter) + Detail::FloorMod(steps, LetterCount),
        LetterCount));
}

} // namespace MCC

#endif // MCC_PITCH_LETTER_H
