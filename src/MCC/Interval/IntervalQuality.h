#ifndef MCC_INTERVAL_INTERVAL_QUALITY_H
#define MCC_INTERVAL_INTERVAL_QUALITY_H

#include <stdint.h>

namespace MCC {

/**
 * @brief Kind of an interval quality.
 * @ingroup MCC_Interval
 */
enum class IntervalQualityKind : uint8_t {
    Diminished = 0,
    Minor = 1,
    Perfect = 2,
    Major = 3,
    Augmented = 4
};

/**
 * @brief Interval quality: perfect, major, minor, or augmented/diminished
 * repeated one to four times (SPEC-INT-4).
 * @ingroup MCC_Interval
 *
 * Default construction and a repetition count outside `[1, 4]` produce the
 * single invalid value (SPEC-ERR-2, SPEC-ERR-3).
 */
class IntervalQuality {
public:
    /** @brief Largest augmented or diminished repetition count. */
    static constexpr uint8_t MaximumCount = 4;

private:
    static constexpr uint8_t InvalidValue = 0xFF;

    // Kind in the high bits, repetition count (1 for P/M/m) in the low bits.
    uint8_t _value;

    constexpr IntervalQuality(IntervalQualityKind kind, int32_t count) noexcept
        : _value((count >= 1 && count <= MaximumCount)
              ? static_cast<uint8_t>(
                    (static_cast<uint8_t>(kind) << 3) | static_cast<uint8_t>(count))
              : InvalidValue) {}

public:
    /** @brief Creates the invalid quality (SPEC-ERR-2). */
    constexpr IntervalQuality() noexcept : _value(InvalidValue) {}

    /** @brief Returns the invalid quality. */
    static constexpr IntervalQuality Invalid() noexcept { return IntervalQuality(); }

    /** @brief Returns the perfect quality. */
    static constexpr IntervalQuality Perfect() noexcept {
        return IntervalQuality(IntervalQualityKind::Perfect, 1);
    }

    /** @brief Returns the major quality. */
    static constexpr IntervalQuality Major() noexcept {
        return IntervalQuality(IntervalQualityKind::Major, 1);
    }

    /** @brief Returns the minor quality. */
    static constexpr IntervalQuality Minor() noexcept {
        return IntervalQuality(IntervalQualityKind::Minor, 1);
    }

    /**
     * @brief Returns the quality augmented `count` times; a count outside
     * `[1, 4]` is invalid (SPEC-INT-4).
     */
    static constexpr IntervalQuality Augmented(int32_t count = 1) noexcept {
        return IntervalQuality(IntervalQualityKind::Augmented, count);
    }

    /**
     * @brief Returns the quality diminished `count` times; a count outside
     * `[1, 4]` is invalid (SPEC-INT-4).
     */
    static constexpr IntervalQuality Diminished(int32_t count = 1) noexcept {
        return IntervalQuality(IntervalQualityKind::Diminished, count);
    }

    /** @brief Returns `true` unless this is the invalid quality. */
    constexpr bool IsValid() const noexcept { return _value != InvalidValue; }

    /**
     * @brief Returns the kind, or `Perfect` for the invalid quality
     * (SPEC-ERR-7).
     */
    constexpr IntervalQualityKind Kind() const noexcept {
        return IsValid()
            ? static_cast<IntervalQualityKind>(_value >> 3)
            : IntervalQualityKind::Perfect;
    }

    /**
     * @brief Returns how many times the quality is augmented or diminished,
     * `1` for perfect, major and minor, and `0` for the invalid quality.
     */
    constexpr uint8_t Count() const noexcept {
        return IsValid() ? static_cast<uint8_t>(_value & 0x07) : 0;
    }

    /**
     * @brief Returns the quality of the inverted interval: major and minor,
     * and augmented and diminished, swap; perfect stays (SPEC-INT-6).
     */
    constexpr IntervalQuality Inverted() const noexcept {
        if (!IsValid()) {
            return Invalid();
        }
        switch (Kind()) {
            case IntervalQualityKind::Major:
                return Minor();
            case IntervalQualityKind::Minor:
                return Major();
            case IntervalQualityKind::Augmented:
                return Diminished(Count());
            case IntervalQualityKind::Diminished:
                return Augmented(Count());
            case IntervalQualityKind::Perfect:
                break;
        }
        return Perfect();
    }

    /** @brief Equality; all invalid qualities are equal (SPEC-ERR-6). */
    friend constexpr bool operator==(IntervalQuality a, IntervalQuality b) noexcept {
        return a._value == b._value;
    }

    friend constexpr bool operator!=(IntervalQuality a, IntervalQuality b) noexcept {
        return !(a == b);
    }
};

} // namespace MCC

#endif // MCC_INTERVAL_INTERVAL_QUALITY_H
