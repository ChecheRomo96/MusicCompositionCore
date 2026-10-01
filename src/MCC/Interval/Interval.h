#ifndef MCC_INTERVAL_INTERVAL_H
#define MCC_INTERVAL_INTERVAL_H

#include <stdint.h>

#include <MCC/Interval/IntervalDirection.h>
#include <MCC/Interval/IntervalNumber.h>
#include <MCC/Interval/IntervalQuality.h>

namespace MCC {

/**
 * @brief Directed interval: a diatonic step count and a chromatic semitone
 * count (SPEC-INT-1).
 * @ingroup MCC_Interval
 *
 * Both counts are signed. The direction follows the diatonic steps, or the
 * semitones for a unison, so `Cb` from `C` is a descending augmented unison
 * and no diminished unison exists (SPEC-INT-2, SPEC-INT-5). Number and
 * quality are derived from the magnitudes: an ascending major third is
 * `+2` steps and `+4` semitones; a descending one is `-2` and `-4`.
 *
 * An interval is valid when its counts lie within the span of writable
 * pitches and its quality is perfect, major, minor, or augmented/diminished
 * at most four times (SPEC-INT-4). Default construction and every other
 * input produce the single invalid value (SPEC-ERR-1..3).
 */
class Interval {
public:
    /** @brief Largest step magnitude: `IntervalNumber::Maximum - 1`. */
    static constexpr int16_t MaximumSteps = IntervalNumber::Maximum - 1;

    /** @brief Largest semitone magnitude between two writable pitches. */
    static constexpr int16_t MaximumSemitones = 3079;

    /**
     * @brief Sentinel returned by `DiatonicSteps()` for the invalid interval
     * (SPEC-ERR-7). Do not rely on it; check `IsValid()`.
     */
    static constexpr int16_t InvalidSteps = 32767;

private:
    int16_t _steps;
    int16_t _semitones;

    // Semitones of the perfect or major simple interval for 0-6 steps
    // (0 2 4 5 7 9 11). Computed rather than tabled so AVR keeps no lookup
    // table in RAM.
    static constexpr int32_t ReferenceSemitones(int32_t simpleSteps) noexcept {
        return simpleSteps * 2 - (simpleSteps >= 3 ? 1 : 0);
    }

    static constexpr bool IsPerfectSteps(int32_t simpleSteps) noexcept {
        return simpleSteps == 0 || simpleSteps == 3 || simpleSteps == 4;
    }

    static constexpr int32_t Magnitude(int32_t value) noexcept {
        return value < 0 ? -value : value;
    }

    // Deviation of the semitones from the perfect/major reference of the
    // same number, measured in the interval's direction.
    constexpr int32_t Deviation() const noexcept {
        const int32_t sign = Sign();
        const int32_t steps = sign * _steps;
        const int32_t semitones = sign * _semitones;
        return semitones - (steps / 7) * 12 - ReferenceSemitones(steps % 7);
    }

    constexpr int32_t Sign() const noexcept {
        return (_steps != 0)
            ? (_steps > 0 ? 1 : -1)
            : (_semitones < 0 ? -1 : 1);
    }

    static constexpr IntervalQuality QualityFor(int32_t steps,
                                                int32_t deviation) noexcept {
        if (IsPerfectSteps(steps % 7)) {
            if (deviation == 0) {
                return IntervalQuality::Perfect();
            }
            return deviation > 0
                ? IntervalQuality::Augmented(deviation)
                : IntervalQuality::Diminished(-deviation);
        }
        if (deviation == 0) {
            return IntervalQuality::Major();
        }
        if (deviation == -1) {
            return IntervalQuality::Minor();
        }
        return deviation > 0
            ? IntervalQuality::Augmented(deviation)
            : IntervalQuality::Diminished(-deviation - 1);
    }

public:
    /** @brief Creates the invalid interval (SPEC-ERR-2). */
    constexpr Interval() noexcept : _steps(InvalidSteps), _semitones(0) {}

    /**
     * @brief Creates the interval spanning `diatonicSteps` letters and
     * `semitones` semitones, both signed (SPEC-INT-1).
     *
     * The result is invalid when either count exceeds the writable span or
     * the quality would need more than four augmentations or diminutions
     * (SPEC-ERR-3, SPEC-ERR-5).
     */
    static constexpr Interval FromSteps(int32_t diatonicSteps,
                                        int32_t semitones) noexcept {
        // Compare against both bounds: negating INT32_MIN would overflow.
        if (diatonicSteps < -MaximumSteps || diatonicSteps > MaximumSteps ||
            semitones < -MaximumSemitones || semitones > MaximumSemitones) {
            return Interval();
        }
        Interval candidate;
        candidate._steps = static_cast<int16_t>(diatonicSteps);
        candidate._semitones = static_cast<int16_t>(semitones);
        return candidate.Quality().IsValid() ? candidate : Interval();
    }

    /**
     * @brief Creates the interval of `quality` and `number` in `direction`,
     * for example `Interval(IntervalQuality::Major(), IntervalNumber(3))`.
     *
     * The result is invalid when the quality does not apply to the number
     * (a perfect third, a major fifth), for a diminished unison
     * (SPEC-INT-5), for direction `Unison` with anything but a perfect
     * unison, or when either argument is invalid. A perfect unison ignores
     * `direction`.
     */
    constexpr Interval(IntervalQuality quality, IntervalNumber number,
                       IntervalDirection direction = IntervalDirection::Ascending) noexcept
        : Interval(Build(quality, number, direction)) {}

    /** @brief Returns the invalid interval. */
    static constexpr Interval Invalid() noexcept { return Interval(); }

    /** @brief Returns the perfect unison. */
    static constexpr Interval Unison() noexcept { return FromSteps(0, 0); }

    /** @brief Returns `true` unless this is the invalid interval. */
    constexpr bool IsValid() const noexcept { return _steps != InvalidSteps; }

    /**
     * @brief Returns the signed diatonic step count, or `InvalidSteps` for
     * the invalid interval (SPEC-ERR-7).
     */
    constexpr int16_t DiatonicSteps() const noexcept { return _steps; }

    /**
     * @brief Returns the signed semitone count, or `0` for the invalid
     * interval (SPEC-ERR-7).
     */
    constexpr int16_t Semitones() const noexcept { return _semitones; }

    /**
     * @brief Returns the direction (SPEC-INT-2); `Unison` for the perfect
     * unison and for the invalid interval (SPEC-ERR-7).
     */
    constexpr IntervalDirection Direction() const noexcept {
        if (!IsValid() || (_steps == 0 && _semitones == 0)) {
            return IntervalDirection::Unison;
        }
        return Sign() > 0 ? IntervalDirection::Ascending
                          : IntervalDirection::Descending;
    }

    /** @brief Returns the 1-based number (SPEC-INT-2); invalid if invalid. */
    constexpr IntervalNumber Number() const noexcept {
        if (!IsValid()) {
            return IntervalNumber::Invalid();
        }
        return IntervalNumber(Magnitude(_steps) + 1);
    }

    /** @brief Returns the quality (SPEC-INT-4); invalid if invalid. */
    constexpr IntervalQuality Quality() const noexcept {
        if (!IsValid()) {
            return IntervalQuality::Invalid();
        }
        return QualityFor(Magnitude(_steps), Deviation());
    }

    /** @brief Returns `true` for numbers 1-8 (SPEC-INT-3). */
    constexpr bool IsSimple() const noexcept { return Number().IsSimple(); }

    /** @brief Returns `true` for numbers above 8 (SPEC-INT-3). */
    constexpr bool IsCompound() const noexcept { return Number().IsCompound(); }

    /**
     * @brief Removes whole octaves while keeping direction and quality
     * (SPEC-INT-3): a major tenth becomes a major third; an octave stays an
     * octave.
     */
    constexpr Interval Simple() const noexcept {
        if (!IsValid() || Magnitude(_steps) <= 7) {
            return *this;
        }
        const int32_t sign = Sign();
        const int32_t octaves = (Magnitude(_steps) - 1) / 7;
        return FromSteps(_steps - sign * octaves * 7,
                         _semitones - sign * octaves * 12);
    }

    /**
     * @brief Returns the inversion of the simple interval, in the same
     * direction (SPEC-INT-6): numbers add up to 9, major and minor swap,
     * augmented and diminished swap. Compound intervals invert their simple
     * part.
     *
     * An augmented octave inverts to a descending augmented unison, because
     * a diminished unison does not exist (SPEC-INT-5).
     */
    constexpr Interval Inverted() const noexcept {
        if (!IsValid()) {
            return Invalid();
        }
        const Interval simple = Simple();
        const int32_t sign = simple.Sign();
        return FromSteps(sign * 7 - simple._steps, sign * 12 - simple._semitones);
    }

    /** @brief Returns the same interval in the opposite direction. */
    constexpr Interval Reversed() const noexcept {
        if (!IsValid()) {
            return Invalid();
        }
        return FromSteps(-static_cast<int32_t>(_steps),
                         -static_cast<int32_t>(_semitones));
    }

    /**
     * @brief Adds two intervals by adding their steps and semitones:
     * major third + minor third = perfect fifth. The result is invalid when
     * either operand is invalid or the sum is unrepresentable.
     */
    friend constexpr Interval operator+(Interval a, Interval b) noexcept {
        if (!a.IsValid() || !b.IsValid()) {
            return Invalid();
        }
        return FromSteps(static_cast<int32_t>(a._steps) + b._steps,
                         static_cast<int32_t>(a._semitones) + b._semitones);
    }

    /**
     * @brief Written equality: same steps and semitones. An augmented
     * fourth and a diminished fifth are different intervals. All invalid
     * intervals are equal (SPEC-ERR-6).
     */
    friend constexpr bool operator==(Interval a, Interval b) noexcept {
        return a._steps == b._steps && a._semitones == b._semitones;
    }

    friend constexpr bool operator!=(Interval a, Interval b) noexcept {
        return !(a == b);
    }

private:
    static constexpr Interval Build(IntervalQuality quality, IntervalNumber number,
                                    IntervalDirection direction) noexcept {
        if (!quality.IsValid() || !number.IsValid()) {
            return Interval();
        }
        const int32_t steps = number.Value() - 1;
        const int32_t simpleSteps = steps % 7;
        const IntervalQualityKind kind = quality.Kind();
        const int32_t count = quality.Count();

        int32_t deviation = 0;
        if (IsPerfectSteps(simpleSteps)) {
            if (kind == IntervalQualityKind::Major ||
                kind == IntervalQualityKind::Minor) {
                return Interval();
            }
            deviation = (kind == IntervalQualityKind::Augmented) ? count
                : (kind == IntervalQualityKind::Diminished) ? -count
                : 0;
        } else {
            if (kind == IntervalQualityKind::Perfect) {
                return Interval();
            }
            deviation = (kind == IntervalQualityKind::Augmented) ? count
                : (kind == IntervalQualityKind::Minor) ? -1
                : (kind == IntervalQualityKind::Diminished) ? -count - 1
                : 0;
        }

        if (steps == 0) {
            if (deviation < 0) {
                return Interval();  // No diminished unison (SPEC-INT-5).
            }
            if (deviation == 0) {
                return Unison();
            }
            if (direction == IntervalDirection::Unison) {
                return Interval();
            }
        } else if (direction == IntervalDirection::Unison) {
            return Interval();
        }

        const int32_t sign = (direction == IntervalDirection::Descending) ? -1 : 1;
        const int32_t semitones =
            (steps / 7) * 12 + ReferenceSemitones(simpleSteps) + deviation;
        return FromSteps(sign * steps, sign * semitones);
    }
};

/**
 * @brief Returns `true` when `a` and `b` are valid and span the same signed
 * number of semitones: an ascending augmented fourth and an ascending
 * diminished fifth are enharmonic. Any invalid operand yields `false`.
 * @ingroup MCC_Interval
 */
constexpr bool IsEnharmonic(Interval a, Interval b) noexcept {
    return a.IsValid() && b.IsValid() && a.Semitones() == b.Semitones();
}

} // namespace MCC

#endif // MCC_INTERVAL_INTERVAL_H
