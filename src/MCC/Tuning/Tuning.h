#ifndef MCC_TUNING_TUNING_H
#define MCC_TUNING_TUNING_H

#include <float.h>

#include <MCC/Pitch/Pitch.h>

namespace MCC {

/**
 * @brief Tuning reference: a written pitch and its frequency in hertz.
 * @ingroup MCC_Tuning
 *
 * `Tuning::Standard()` is `A4 = 440 Hz` (SPEC-OCT-2). Default construction,
 * an invalid reference pitch or a frequency that is not a finite positive
 * number produce the single invalid value (SPEC-ERR-2, SPEC-ERR-3).
 */
class Tuning {
    MCC::Pitch _reference;
    float _frequency;

public:
    /** @brief Creates the invalid tuning (SPEC-ERR-2). */
    constexpr Tuning() noexcept : _reference(), _frequency(0.0f) {}

    /**
     * @brief Creates a tuning where `reference` sounds at `frequency` Hz.
     * An invalid pitch, or a frequency that is zero, negative, infinite or
     * NaN, produces the invalid tuning (SPEC-ERR-3).
     */
    constexpr Tuning(MCC::Pitch reference, float frequency) noexcept
        : _reference(IsUsable(reference, frequency)
              ? reference
              : MCC::Pitch::Invalid()),
          _frequency(IsUsable(reference, frequency) ? frequency : 0.0f) {}

    /** @brief Returns the standard tuning, `A4 = 440 Hz` (SPEC-OCT-2). */
    static constexpr Tuning Standard() noexcept {
        return Tuning(MCC::Pitch(MCC::Letter::A, 4), 440.0f);
    }

    /** @brief Returns the invalid tuning. */
    static constexpr Tuning Invalid() noexcept { return Tuning(); }

    /** @brief Returns `true` unless this is the invalid tuning. */
    constexpr bool IsValid() const noexcept { return _reference.IsValid(); }

    /** @brief Returns the reference pitch; invalid for the invalid tuning. */
    constexpr MCC::Pitch Reference() const noexcept { return _reference; }

    /**
     * @brief Returns the reference frequency in hertz, or `0` for the invalid
     * tuning (SPEC-ERR-7).
     */
    constexpr float ReferenceFrequency() const noexcept { return _frequency; }

    /**
     * @brief Equality of reference pitch and frequency. All invalid tunings
     * are equal (SPEC-ERR-6).
     */
    friend constexpr bool operator==(Tuning a, Tuning b) noexcept {
        return a._reference == b._reference && a._frequency == b._frequency;
    }

    friend constexpr bool operator!=(Tuning a, Tuning b) noexcept {
        return !(a == b);
    }

private:
    static constexpr bool IsUsable(MCC::Pitch reference, float frequency) noexcept {
        // NaN fails both comparisons; infinity fails the upper bound.
        return reference.IsValid() && frequency > 0.0f && frequency <= FLT_MAX;
    }
};

} // namespace MCC

#endif // MCC_TUNING_TUNING_H
