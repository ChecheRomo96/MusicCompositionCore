#ifndef MCC_RHYTHM_NOTE_VALUE_H
#define MCC_RHYTHM_NOTE_VALUE_H

#include <stdint.h>

#include <MCC_BuildSettings.h>

namespace MCC {

/**
 * @brief Exact written note length: a power-of-two base and zero to four dots.
 * @ingroup MCC_Rhythm
 *
 * A note value is independent of tempo, clocks and PPQN. Its duration is an
 * exact reduced fraction of a whole note: a quarter note is `1/4`, a dotted
 * quarter is `3/8`, and a double-dotted quarter is `7/16`.
 *
 * Default construction and invalid factories produce the single invalid value.
 * Invalid values return `0/0` from Numerator() and Denominator().
 */
class NoteValue {
    static constexpr uint8_t InvalidBaseExponent = 0xFFu;
    static constexpr uint8_t MaximumBaseExponent = 8u;

    uint8_t _baseExponent;
    uint8_t _dots;

    static constexpr bool IsDotCountValid(int32_t dots) noexcept {
        return dots >= 0 && dots <= 4;
    }

    constexpr NoteValue(uint8_t baseExponent, int32_t dots) noexcept
        : _baseExponent(baseExponent <= MaximumBaseExponent && IsDotCountValid(dots)
              ? baseExponent
              : InvalidBaseExponent),
          _dots(baseExponent <= MaximumBaseExponent && IsDotCountValid(dots)
              ? static_cast<uint8_t>(dots)
              : 0u) {}

public:
    /** @brief Largest supported number of augmentation dots. */
    static constexpr uint8_t MaximumDots = 4u;

    /** @brief Sentinel returned by DotCount() for an invalid value. */
    static constexpr uint8_t InvalidDotCount = 0xFFu;

    /** @brief Creates the invalid note value. */
    constexpr NoteValue() noexcept : _baseExponent(InvalidBaseExponent), _dots(0u) {}

    /** @brief Returns the invalid note value. */
    static constexpr NoteValue Invalid() noexcept { return NoteValue(); }

    /** @brief Creates a whole note, optionally augmented by `dots`. */
    static constexpr NoteValue Whole(int32_t dots = 0) noexcept {
        return NoteValue(0u, dots);
    }

    /** @brief Creates a half note, optionally augmented by `dots`. */
    static constexpr NoteValue Half(int32_t dots = 0) noexcept {
        return NoteValue(1u, dots);
    }

    /** @brief Creates a quarter note, optionally augmented by `dots`. */
    static constexpr NoteValue Quarter(int32_t dots = 0) noexcept {
        return NoteValue(2u, dots);
    }

    /** @brief Creates an eighth note, optionally augmented by `dots`. */
    static constexpr NoteValue Eighth(int32_t dots = 0) noexcept {
        return NoteValue(3u, dots);
    }

    /** @brief Creates a sixteenth note, optionally augmented by `dots`. */
    static constexpr NoteValue Sixteenth(int32_t dots = 0) noexcept {
        return NoteValue(4u, dots);
    }

    /** @brief Creates a thirty-second note, optionally augmented by `dots`. */
    static constexpr NoteValue ThirtySecond(int32_t dots = 0) noexcept {
        return NoteValue(5u, dots);
    }

    /** @brief Creates a sixty-fourth note, optionally augmented by `dots`. */
    static constexpr NoteValue SixtyFourth(int32_t dots = 0) noexcept {
        return NoteValue(6u, dots);
    }

    /** @brief Creates a 128th note, optionally augmented by `dots`. */
    static constexpr NoteValue OneHundredTwentyEighth(int32_t dots = 0) noexcept {
        return NoteValue(7u, dots);
    }

    /** @brief Creates a 256th note, optionally augmented by `dots`. */
    static constexpr NoteValue TwoHundredFiftySixth(int32_t dots = 0) noexcept {
        return NoteValue(8u, dots);
    }

    /**
     * @brief Creates a value from the undotted base denominator.
     *
     * `baseDenominator` must be one of `1, 2, 4, ..., 256`; `dots` must be
     * between zero and MaximumDots. Otherwise the result is invalid.
     */
    static MCC_CONSTEXPR14 NoteValue FromDenominator(
        int32_t baseDenominator, int32_t dots = 0) noexcept {
        switch (baseDenominator) {
            case 1: return Whole(dots);
            case 2: return Half(dots);
            case 4: return Quarter(dots);
            case 8: return Eighth(dots);
            case 16: return Sixteenth(dots);
            case 32: return ThirtySecond(dots);
            case 64: return SixtyFourth(dots);
            case 128: return OneHundredTwentyEighth(dots);
            case 256: return TwoHundredFiftySixth(dots);
            default: return Invalid();
        }
    }

    /** @brief Returns `true` unless this is the invalid note value. */
    constexpr bool IsValid() const noexcept {
        return _baseExponent != InvalidBaseExponent;
    }

    /** @brief Returns `true` when this valid value has augmentation dots. */
    constexpr bool IsDotted() const noexcept { return IsValid() && _dots != 0u; }

    /** @brief Returns the undotted denominator (`1` through `256`), or `0`. */
    constexpr uint16_t BaseDenominator() const noexcept {
        return IsValid()
            ? static_cast<uint16_t>(uint16_t(1u) << _baseExponent)
            : uint16_t(0u);
    }

    /** @brief Returns the number of dots, or InvalidDotCount when invalid. */
    constexpr uint8_t DotCount() const noexcept {
        return IsValid() ? _dots : InvalidDotCount;
    }

    /** @brief Returns the exact reduced numerator relative to a whole note. */
    constexpr uint16_t Numerator() const noexcept {
        return IsValid()
            ? static_cast<uint16_t>((uint16_t(1u) << (_dots + 1u)) - 1u)
            : uint16_t(0u);
    }

    /** @brief Returns the exact reduced denominator relative to a whole note. */
    constexpr uint16_t Denominator() const noexcept {
        return IsValid()
            ? static_cast<uint16_t>(uint16_t(1u) << (_baseExponent + _dots))
            : uint16_t(0u);
    }

    /** @brief Returns the same base with `dots`, or invalid for bad input. */
    constexpr NoteValue WithDots(int32_t dots) const noexcept {
        return IsValid() ? NoteValue(_baseExponent, dots) : Invalid();
    }

    /** @brief Written equality: the base and dot count must both match. */
    friend constexpr bool operator==(NoteValue a, NoteValue b) noexcept {
        return a._baseExponent == b._baseExponent && a._dots == b._dots;
    }

    friend constexpr bool operator!=(NoteValue a, NoteValue b) noexcept {
        return !(a == b);
    }

    /**
     * @brief Orders by exact duration, with invalid values after valid values.
     * Written values with equal duration compare equivalent even when their
     * spelling differs.
     */
    friend constexpr bool operator<(NoteValue a, NoteValue b) noexcept {
        return a.IsValid() != b.IsValid()
            ? a.IsValid()
            : (!a.IsValid()
                ? false
                : static_cast<uint32_t>(a.Numerator()) * b.Denominator()
                    < static_cast<uint32_t>(b.Numerator()) * a.Denominator());
    }

    friend constexpr bool operator>(NoteValue a, NoteValue b) noexcept {
        return b < a;
    }

    friend constexpr bool operator<=(NoteValue a, NoteValue b) noexcept {
        return !(b < a);
    }

    friend constexpr bool operator>=(NoteValue a, NoteValue b) noexcept {
        return !(a < b);
    }
};

} // namespace MCC

#endif // MCC_RHYTHM_NOTE_VALUE_H
