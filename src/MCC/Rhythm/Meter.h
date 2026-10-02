#ifndef MCC_RHYTHM_METER_H
#define MCC_RHYTHM_METER_H

#include <stdint.h>

#include <MCC_BuildSettings.h>
#include <MCC/Rhythm/NoteValue.h>

namespace MCC {

/** @brief Rhythmic interpretation of a written meter. @ingroup MCC_Rhythm */
enum class MeterKind : uint8_t {
    Simple = 0,
    Compound,
    Irregular,
    Invalid
};

/**
 * @brief Exact written time signature and its simple/compound interpretation.
 * @ingroup MCC_Rhythm
 *
 * The numerator counts denominator units in one measure. The denominator is
 * an undotted power-of-two NoteValue from whole through 256th. Simple meters
 * have one denominator unit per beat; compound meters have three and expose
 * the corresponding dotted beat. Other numerators are valid irregular meters,
 * but their beat grouping is deliberately unspecified.
 *
 * `Meter` contains no tempo, wall-clock duration, MIDI clock or PPQN state.
 */
class Meter {
    uint8_t _numerator;
    MCC::NoteValue _pulseValue;

    static constexpr bool IsUndotted(MCC::NoteValue value) noexcept {
        return value.IsValid() && value.DotCount() == 0u;
    }

    static constexpr bool LooksCompound(int32_t numerator) noexcept {
        return numerator >= 6 && numerator % 3 == 0;
    }

    static constexpr bool IsUsable(
        int32_t numerator, MCC::NoteValue pulseValue) noexcept {
        return numerator >= 1 && numerator <= 255 && IsUndotted(pulseValue) &&
            (!LooksCompound(numerator) || pulseValue.BaseDenominator() >= 2u);
    }

    static MCC_CONSTEXPR14 uint16_t GreatestCommonDivisor(
        uint16_t a, uint16_t b) noexcept {
        while (b != 0u) {
            const uint16_t remainder = static_cast<uint16_t>(a % b);
            a = b;
            b = remainder;
        }
        return a;
    }

public:
    /** @brief Creates the invalid meter (SPEC-ERR-2). */
    constexpr Meter() noexcept : _numerator(0u), _pulseValue() {}

    /**
     * @brief Creates the written signature `numerator / denominator`.
     *
     * The numerator must be in `[1, 255]`; the denominator must be one of
     * `1, 2, 4, ..., 256`. Compound meters require denominator 2 or greater
     * because NoteValue does not represent a dotted value longer than a whole.
     */
    MCC_CONSTEXPR14 Meter(int32_t numerator, int32_t denominator) noexcept
        : Meter(numerator, MCC::NoteValue::FromDenominator(denominator)) {}

    /**
     * @brief Creates a meter from its numerator and undotted denominator unit.
     */
    constexpr Meter(int32_t numerator, MCC::NoteValue pulseValue) noexcept
        : _numerator(IsUsable(numerator, pulseValue)
              ? static_cast<uint8_t>(numerator)
              : uint8_t(0u)),
          _pulseValue(IsUsable(numerator, pulseValue)
              ? pulseValue
              : MCC::NoteValue::Invalid()) {}

    /** @brief Returns the invalid meter. */
    static constexpr Meter Invalid() noexcept { return Meter(); }

    /** @brief Returns common time (`4/4`). */
    static MCC_CONSTEXPR14 Meter CommonTime() noexcept { return Meter(4, 4); }

    /** @brief Returns cut time (`2/2`). */
    static MCC_CONSTEXPR14 Meter CutTime() noexcept { return Meter(2, 2); }

    /**
     * @brief Creates a simple meter from one to four undotted beats.
     *
     * `Simple(3, NoteValue::Quarter())` is `3/4`.
     */
    static constexpr Meter Simple(
        int32_t beatCount,
        MCC::NoteValue beatValue = MCC::NoteValue::Quarter()) noexcept {
        return beatCount >= 1 && beatCount <= 4 && IsUndotted(beatValue)
            ? Meter(beatCount, beatValue)
            : Invalid();
    }

    /**
     * @brief Creates a compound meter from dotted beats.
     *
     * `Compound(2, NoteValue::Quarter(1))` is `6/8`. The beat count must be
     * in `[2, 85]`; `beatValue` must have exactly one dot and a base from
     * whole through 128th.
     */
    static MCC_CONSTEXPR14 Meter Compound(
        int32_t beatCount,
        MCC::NoteValue beatValue = MCC::NoteValue::Quarter(1)) noexcept {
        if (beatCount < 2 || beatCount > 85 || !beatValue.IsValid() ||
            beatValue.DotCount() != 1u || beatValue.BaseDenominator() > 128u) {
            return Invalid();
        }
        return Meter(
            beatCount * 3,
            static_cast<int32_t>(beatValue.BaseDenominator()) * 2);
    }

    /** @brief Returns `true` unless this is the invalid meter. */
    constexpr bool IsValid() const noexcept { return _numerator != 0u; }

    /** @brief Returns the written numerator, or `0` for the invalid meter. */
    constexpr uint8_t Numerator() const noexcept { return _numerator; }

    /** @brief Returns the written denominator, or `0` for the invalid meter. */
    constexpr uint16_t Denominator() const noexcept {
        return _pulseValue.BaseDenominator();
    }

    /** @brief Returns the denominator unit, or the invalid NoteValue. */
    constexpr MCC::NoteValue PulseValue() const noexcept { return _pulseValue; }

    /** @brief Returns the number of denominator units in the measure. */
    constexpr uint8_t PulseCount() const noexcept { return _numerator; }

    /** @brief Classifies this meter as simple, compound, irregular or invalid. */
    constexpr MeterKind Kind() const noexcept {
        return !IsValid() ? MeterKind::Invalid
            : (_numerator <= 4u ? MeterKind::Simple
                : (LooksCompound(_numerator)
                    ? MeterKind::Compound
                    : MeterKind::Irregular));
    }

    constexpr bool IsSimple() const noexcept { return Kind() == MeterKind::Simple; }
    constexpr bool IsCompound() const noexcept { return Kind() == MeterKind::Compound; }
    constexpr bool IsIrregular() const noexcept { return Kind() == MeterKind::Irregular; }

    /**
     * @brief Returns the interpreted beat count, or `0` for irregular/invalid.
     */
    constexpr uint8_t BeatCount() const noexcept {
        return IsSimple() ? _numerator
            : (IsCompound() ? static_cast<uint8_t>(_numerator / 3u) : 0u);
    }

    /**
     * @brief Returns the beat value, or invalid for irregular/invalid meters.
     *
     * The beat equals one pulse in simple meter and three pulses in compound
     * meter, such as dotted quarter in `6/8`.
     */
    MCC_CONSTEXPR14 MCC::NoteValue BeatValue() const noexcept {
        if (IsSimple()) {
            return _pulseValue;
        }
        if (IsCompound()) {
            return MCC::NoteValue::FromDenominator(
                static_cast<int32_t>(Denominator() / 2u), 1);
        }
        return MCC::NoteValue::Invalid();
    }

    /** @brief Reduced numerator of the measure length in whole notes. */
    MCC_CONSTEXPR14 uint16_t MeasureNumerator() const noexcept {
        if (!IsValid()) {
            return 0u;
        }
        const uint16_t divisor = GreatestCommonDivisor(_numerator, Denominator());
        return static_cast<uint16_t>(_numerator / divisor);
    }

    /** @brief Reduced denominator of the measure length in whole notes. */
    MCC_CONSTEXPR14 uint16_t MeasureDenominator() const noexcept {
        if (!IsValid()) {
            return 0u;
        }
        const uint16_t divisor = GreatestCommonDivisor(_numerator, Denominator());
        return static_cast<uint16_t>(Denominator() / divisor);
    }

    /** @brief Written equality; equivalent durations need not be equal. */
    friend constexpr bool operator==(Meter a, Meter b) noexcept {
        return a._numerator == b._numerator && a._pulseValue == b._pulseValue;
    }

    friend constexpr bool operator!=(Meter a, Meter b) noexcept {
        return !(a == b);
    }

    /** @brief Written order by numerator then denominator; invalid sorts last. */
    friend constexpr bool operator<(Meter a, Meter b) noexcept {
        return a.IsValid() != b.IsValid() ? a.IsValid()
            : (!a.IsValid() ? false
                : (a._numerator != b._numerator
                    ? a._numerator < b._numerator
                    : a.Denominator() < b.Denominator()));
    }

    friend constexpr bool operator>(Meter a, Meter b) noexcept { return b < a; }
    friend constexpr bool operator<=(Meter a, Meter b) noexcept { return !(b < a); }
    friend constexpr bool operator>=(Meter a, Meter b) noexcept { return !(a < b); }
};

/**
 * @brief Returns `true` when two valid meters span the same whole-note length.
 * @ingroup MCC_Rhythm
 *
 * Written identity remains distinct: `3/4 != 6/8`, but both have the same
 * measure duration.
 */
constexpr bool HasSameMeasureDuration(Meter a, Meter b) noexcept {
    return a.IsValid() && b.IsValid() &&
        static_cast<uint32_t>(a.Numerator()) * b.Denominator() ==
        static_cast<uint32_t>(b.Numerator()) * a.Denominator();
}

} // namespace MCC

#endif // MCC_RHYTHM_METER_H
