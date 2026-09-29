#ifndef MCC_INTERVAL_INTERVAL_NUMBER_H
#define MCC_INTERVAL_INTERVAL_NUMBER_H

#include <stdint.h>

namespace MCC {

/**
 * @brief 1-based interval number: `1` unison, `3` third, `8` octave,
 * `10` tenth (SPEC-INT-2, SPEC-INT-3).
 * @ingroup MCC_Interval
 *
 * Numbers range from 1 to `Maximum`, the widest span between two writable
 * pitches. Default construction and out-of-range input produce the single
 * invalid value (SPEC-ERR-2, SPEC-ERR-3).
 */
class IntervalNumber {
public:
    /** @brief Widest number: `Cbbbb-128` to `B####127` spans 1791 steps. */
    static constexpr uint16_t Maximum = 1792;

    /**
     * @brief Sentinel returned by `Value()` for the invalid number
     * (SPEC-ERR-7). Do not rely on it; check `IsValid()`.
     */
    static constexpr uint16_t InvalidValue = 0xFFFF;

private:
    uint16_t _value;

public:
    /** @brief Creates the invalid number (SPEC-ERR-2). */
    constexpr IntervalNumber() noexcept : _value(InvalidValue) {}

    /**
     * @brief Creates the number `value`; values outside `[1, Maximum]`
     * produce the invalid number (SPEC-ERR-3).
     */
    constexpr explicit IntervalNumber(int32_t value) noexcept
        : _value((value >= 1 && value <= Maximum)
              ? static_cast<uint16_t>(value)
              : InvalidValue) {}

    /** @brief Returns the invalid number. */
    static constexpr IntervalNumber Invalid() noexcept { return IntervalNumber(); }

    /** @brief Returns `true` unless this is the invalid number. */
    constexpr bool IsValid() const noexcept { return _value != InvalidValue; }

    /** @brief Returns the number, or `InvalidValue` (SPEC-ERR-7). */
    constexpr uint16_t Value() const noexcept { return _value; }

    /** @brief Returns `true` for numbers 1-8 (SPEC-INT-3). */
    constexpr bool IsSimple() const noexcept { return IsValid() && _value <= 8; }

    /** @brief Returns `true` for numbers above 8 (SPEC-INT-3). */
    constexpr bool IsCompound() const noexcept { return IsValid() && _value > 8; }

    /**
     * @brief Returns the simple number obtained by removing octaves
     * (SPEC-INT-3): `9 -> 2`, `10 -> 3`, `15 -> 8`. Simple numbers are
     * returned unchanged.
     */
    constexpr IntervalNumber Simple() const noexcept {
        if (!IsValid() || _value <= 8) {
            return *this;
        }
        return IntervalNumber((_value - 2) % 7 + 2);
    }

    /**
     * @brief Returns `true` when the simple number is a unison, fourth,
     * fifth or octave, which take perfect qualities (SPEC-INT-4).
     */
    constexpr bool IsPerfectType() const noexcept {
        const uint16_t simple = Simple().Value();
        return simple == 1 || simple == 4 || simple == 5 || simple == 8;
    }

    /**
     * @brief Returns the inverted simple number, `9 - Simple()`
     * (SPEC-INT-6).
     */
    constexpr IntervalNumber Inverted() const noexcept {
        if (!IsValid()) {
            return Invalid();
        }
        return IntervalNumber(9 - Simple().Value());
    }

    /** @brief Equality; all invalid numbers are equal (SPEC-ERR-6). */
    friend constexpr bool operator==(IntervalNumber a, IntervalNumber b) noexcept {
        return a._value == b._value;
    }

    friend constexpr bool operator!=(IntervalNumber a, IntervalNumber b) noexcept {
        return !(a == b);
    }

    /** @brief Orders by value; the invalid number sorts last. */
    friend constexpr bool operator<(IntervalNumber a, IntervalNumber b) noexcept {
        return a._value < b._value;
    }
};

} // namespace MCC

#endif // MCC_INTERVAL_INTERVAL_NUMBER_H
