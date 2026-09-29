#ifndef MCC_TUNING_EQUAL_TEMPERAMENT_H
#define MCC_TUNING_EQUAL_TEMPERAMENT_H

#include <float.h>
#include <stdint.h>

#include <Foundation/Math/Arithmetic.h>

#include <MCC/Pitch/PitchClass.h>
#include <MCC/Pitch/Pitch.h>
#include <MCC/Tuning/Tuning.h>

namespace MCC {

/**
 * @brief Twelve-tone equal temperament relative to a `Tuning`.
 * @ingroup MCC_Tuning
 *
 * A pitch `n` semitones above the reference sounds at
 * `referenceFrequency * 2^(n / 12)`. Enharmonic pitches share a frequency.
 * The frequency is computed from a table of the twelve semitone ratios and
 * exact octave doublings, without `pow()` or the math library.
 *
 * Default construction produces the invalid temperament (invalid tuning).
 */
class EqualTemperament {
    MCC::Tuning _tuning;

public:
    /** @brief Creates the invalid temperament (SPEC-ERR-2). */
    constexpr EqualTemperament() noexcept : _tuning() {}

    /** @brief Creates the temperament for `tuning`. */
    constexpr explicit EqualTemperament(MCC::Tuning tuning) noexcept
        : _tuning(tuning) {}

    /** @brief Returns equal temperament with `A4 = 440 Hz` (SPEC-OCT-2). */
    static constexpr EqualTemperament Standard() noexcept {
        return EqualTemperament(MCC::Tuning::Standard());
    }

    /** @brief Returns `true` when the tuning is valid. */
    constexpr bool IsValid() const noexcept { return _tuning.IsValid(); }

    /** @brief Returns the tuning reference. */
    constexpr MCC::Tuning Tuning() const noexcept { return _tuning; }

    /**
     * @brief Returns the frequency of `pitch` in hertz.
     *
     * Returns `0` when the temperament or the pitch is invalid, or when the
     * frequency exceeds the largest finite `float` (SPEC-ERR-5, SPEC-ERR-7).
     * Under `A4 = 440 Hz` that happens above `B123`; every lower pitch down
     * to octave -128 has a finite positive frequency.
     */
    constexpr float Frequency(MCC::Pitch pitch) const noexcept {
        if (!IsValid() || !pitch.IsValid()) {
            return 0.0f;
        }

        // 2^(k / 12) for k = 0..11.
        constexpr float ratios[MCC::PitchClass::Count] = {
            1.0f,
            1.0594630943592953f,
            1.1224620483093730f,
            1.1892071150027210f,
            1.2599210498948732f,
            1.3348398541700344f,
            1.4142135623730951f,
            1.4983070768766815f,
            1.5874010519681994f,
            1.6817928305074290f,
            1.7817974362806785f,
            1.8877486253633870f};

        const int32_t distance =
            static_cast<int32_t>(pitch.ChromaticIndex().Value()) -
            _tuning.Reference().ChromaticIndex().Value();
        int32_t octaves = Foundation::Math::FloorDiv(
            distance, MCC::PitchClass::Count);
        const int32_t semitones = Foundation::Math::FloorMod(
            distance, MCC::PitchClass::Count);

        float frequency = _tuning.ReferenceFrequency() * ratios[semitones];
        for (; octaves > 0; --octaves) {
            if (frequency > FLT_MAX / 2.0f) {
                return 0.0f;
            }
            frequency *= 2.0f;
        }
        for (; octaves < 0; ++octaves) {
            frequency *= 0.5f;
        }
        return frequency;
    }

    /** @brief Equality of tunings. */
    friend constexpr bool operator==(EqualTemperament a, EqualTemperament b) noexcept {
        return a._tuning == b._tuning;
    }

    friend constexpr bool operator!=(EqualTemperament a, EqualTemperament b) noexcept {
        return !(a == b);
    }
};

} // namespace MCC

#endif // MCC_TUNING_EQUAL_TEMPERAMENT_H
