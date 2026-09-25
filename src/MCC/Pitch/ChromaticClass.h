#ifndef MCC_PITCH_CHROMATIC_CLASS_H
#define MCC_PITCH_CHROMATIC_CLASS_H

#include <stdint.h>

#include <Foundation/Math/Arithmetic.h>

namespace MCC {

/**
 * @brief Chromatic class 0-11 with spelling discarded (`C = 0`).
 * @ingroup MCC_Pitch
 *
 * Default construction and out-of-range input produce the single invalid
 * value (SPEC-ERR-2, SPEC-ERR-3): the constructor checks its input and does
 * not reduce it. Use `Transposed()` for modular arithmetic. Classes are
 * ordered by value; the invalid value sorts after every valid class.
 */
class ChromaticClass {
public:
    /** @brief Number of chromatic classes in an octave. */
    static constexpr uint8_t Count = 12;

    /**
     * @brief Sentinel returned by `Value()` for the invalid class
     * (SPEC-ERR-7). Do not rely on it; check `IsValid()`.
     */
    static constexpr uint8_t InvalidValue = 0xFF;

private:
    uint8_t _value;

public:
    /** @brief Creates the invalid chromatic class (SPEC-ERR-2). */
    constexpr ChromaticClass() noexcept : _value(InvalidValue) {}

    /**
     * @brief Creates the chromatic class `value`; values outside `[0, 11]`
     * produce the invalid value (SPEC-ERR-3).
     */
    constexpr explicit ChromaticClass(int value) noexcept
        : _value((value >= 0 && value < Count)
              ? static_cast<uint8_t>(value)
              : InvalidValue) {}

    /** @brief Returns the invalid chromatic class. */
    static constexpr ChromaticClass Invalid() noexcept {
        return ChromaticClass();
    }

    /** @brief Returns `true` unless this is the invalid class. */
    constexpr bool IsValid() const noexcept { return _value != InvalidValue; }

    /**
     * @brief Returns the class in `[0, 11]`, or `InvalidValue` for the
     * invalid class (SPEC-ERR-7).
     */
    constexpr uint8_t Value() const noexcept { return _value; }

    /**
     * @brief Returns this class moved by `semitones`, reduced modulo 12.
     * An invalid class stays invalid (SPEC-ERR-4).
     */
    constexpr ChromaticClass Transposed(int semitones) const noexcept {
        if (!IsValid()) {
            return Invalid();
        }
        return ChromaticClass(Foundation::Math::FloorMod(
            _value + Foundation::Math::FloorMod(semitones, Count), Count));
    }

    /** @brief Equality; all invalid classes are equal (SPEC-ERR-6). */
    friend constexpr bool operator==(ChromaticClass a, ChromaticClass b) noexcept {
        return a._value == b._value;
    }

    friend constexpr bool operator!=(ChromaticClass a, ChromaticClass b) noexcept {
        return !(a == b);
    }

    /** @brief Orders by value; invalid sorts last. */
    friend constexpr bool operator<(ChromaticClass a, ChromaticClass b) noexcept {
        return a._value < b._value;
    }

    friend constexpr bool operator>(ChromaticClass a, ChromaticClass b) noexcept {
        return b < a;
    }

    friend constexpr bool operator<=(ChromaticClass a, ChromaticClass b) noexcept {
        return !(b < a);
    }

    friend constexpr bool operator>=(ChromaticClass a, ChromaticClass b) noexcept {
        return !(a < b);
    }
};

} // namespace MCC

#endif // MCC_PITCH_CHROMATIC_CLASS_H
