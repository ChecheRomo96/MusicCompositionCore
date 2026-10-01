#ifndef MCC_SCALE_SCALE_PATTERN_H
#define MCC_SCALE_SCALE_PATTERN_H

#include <stdint.h>

#include <MCC/Interval/Interval.h>

namespace MCC {

/**
 * @brief Root-independent scale structure: up to twelve ascending degrees.
 * @ingroup MCC_Scale
 *
 * Each degree stores its diatonic steps (0-6) and semitones (0-11) above the
 * root, so a scale spelled from any root keeps its written letters: the third
 * degree of a major pattern is always a third (SPEC-SCL-2). Semitones are
 * strictly ascending and the first degree is the perfect unison (SPEC-SCL-1).
 *
 * A pattern is eight bytes, trivially copyable and allocation-free, so the
 * same representation is stored in the flash catalog (SPEC-EMB-5).
 * Default construction and every malformed input produce the single invalid
 * pattern (SPEC-ERR-1..3).
 */
class ScalePattern {
public:
    /** @brief Largest number of degrees: every chromatic semitone. */
    static constexpr uint8_t MaximumDegrees = 12;

private:
    uint16_t _semitones;   // bit k set: a degree lies k semitones above the root
    uint8_t _steps[6];     // diatonic steps of degree i in nibble i

    // Semitones of the major-scale degree `steps` above the root: 0 2 4 5 7 9 11.
    // Computed rather than tabled so AVR keeps no lookup table in RAM.
    static constexpr int32_t NaturalSemitones(int32_t steps) noexcept {
        return steps * 2 - (steps >= 3 ? 1 : 0);
    }

    constexpr uint8_t StepsAt(uint8_t index) const noexcept {
        return static_cast<uint8_t>((_steps[index / 2] >> ((index % 2) * 4)) & 0x0F);
    }

    constexpr int32_t SemitonesAt(uint8_t index) const noexcept {
        uint8_t seen = 0;
        for (int32_t k = 0; k < 12; ++k) {
            if ((static_cast<uint32_t>(_semitones) >> k) & 1u) {
                if (seen == index) {
                    return k;
                }
                ++seen;
            }
        }
        return -1;
    }

public:
    /** @brief Creates the invalid pattern (SPEC-ERR-2). */
    constexpr ScalePattern() noexcept : _semitones(0), _steps{0, 0, 0, 0, 0, 0} {}

    /** @brief Returns the invalid pattern. */
    static constexpr ScalePattern Invalid() noexcept { return ScalePattern(); }

    /**
     * @brief Builds a pattern from a degree formula such as `"1 2 b3 4 5 b6 b7"`.
     *
     * Each space-separated token is an optional run of `b` or `#` followed by
     * a degree number from 1 to 7, read against the major scale. The formula
     * must start with `1` and its semitones must be strictly ascending inside
     * one octave; otherwise the invalid pattern is returned.
     */
    static constexpr ScalePattern FromFormula(const char* formula) noexcept {
        ScalePattern pattern;
        if (formula == nullptr) {
            return Invalid();
        }
        uint8_t count = 0;
        int32_t previous = -1;
        // Index-based scanning without `continue`: GCC 7 (the Arduino AVR
        // toolchain) miscounts constexpr loops that `continue` past an
        // advancing pointer.
        int32_t i = 0;
        while (formula[i] != '\0') {
            if (formula[i] == ' ') {
                ++i;
            } else {
                int32_t accidental = 0;
                while (formula[i] == 'b' || formula[i] == '#') {
                    accidental += (formula[i] == '#') ? 1 : -1;
                    ++i;
                }
                if (formula[i] < '1' || formula[i] > '7') {
                    return Invalid();
                }
                const int32_t steps = formula[i] - '1';
                ++i;
                if (formula[i] != ' ' && formula[i] != '\0') {
                    return Invalid();
                }
                const int32_t semitones = NaturalSemitones(steps) + accidental;
                if (count == MaximumDegrees || semitones <= previous || semitones > 11 ||
                    (count == 0 && (steps != 0 || semitones != 0)) ||
                    !Interval::FromSteps(steps, semitones).IsValid()) {
                    return Invalid();
                }
                pattern._semitones = static_cast<uint16_t>(pattern._semitones | (1u << semitones));
                pattern._steps[count / 2] = static_cast<uint8_t>(
                    pattern._steps[count / 2] | (steps << ((count % 2) * 4)));
                previous = semitones;
                ++count;
            }
        }
        return count == 0 ? Invalid() : pattern;
    }

    /** @brief Returns `true` unless this is the invalid pattern. */
    constexpr bool IsValid() const noexcept { return _semitones != 0; }

    /** @brief Returns the number of degrees, or 0 for the invalid pattern. */
    constexpr uint8_t DegreeCount() const noexcept {
        uint8_t count = 0;
        for (int32_t k = 0; k < 12; ++k) {
            count = static_cast<uint8_t>(count + ((static_cast<uint32_t>(_semitones) >> k) & 1u));
        }
        return count;
    }

    /**
     * @brief Returns the ascending interval from the root to `degree`
     * (1-based), or the invalid interval outside `[1, DegreeCount()]`.
     */
    constexpr Interval DegreeInterval(int32_t degree) const noexcept {
        if (degree < 1 || degree > DegreeCount()) {
            return Interval::Invalid();
        }
        const uint8_t index = static_cast<uint8_t>(degree - 1);
        return Interval::FromSteps(StepsAt(index), SemitonesAt(index));
    }

    /**
     * @brief Returns `true` when a degree lies `semitones` (reduced modulo 12)
     * above the root.
     */
    constexpr bool ContainsSemitone(int32_t semitones) const noexcept {
        const int32_t reduced = ((semitones % 12) + 12) % 12;
        return IsValid() && ((static_cast<uint32_t>(_semitones) >> reduced) & 1u) != 0;
    }

    /** @brief Compares degrees, including their written steps. */
    friend constexpr bool operator==(const ScalePattern& a, const ScalePattern& b) noexcept {
        if (a._semitones != b._semitones) {
            return false;
        }
        for (uint8_t i = 0; i < 6; ++i) {
            if (a._steps[i] != b._steps[i]) {
                return false;
            }
        }
        return true;
    }

    /** @brief Negation of `operator==`. */
    friend constexpr bool operator!=(const ScalePattern& a, const ScalePattern& b) noexcept {
        return !(a == b);
    }
};

} // namespace MCC

#endif // MCC_SCALE_SCALE_PATTERN_H
