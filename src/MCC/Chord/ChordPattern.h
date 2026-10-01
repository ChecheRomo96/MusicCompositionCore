#ifndef MCC_CHORD_CHORD_PATTERN_H
#define MCC_CHORD_CHORD_PATTERN_H

#include <stdint.h>

#include <MCC/Interval/Interval.h>

namespace MCC {

/**
 * @brief Root-independent chord structure: up to seven ascending tones within
 * two octaves.
 * @ingroup MCC_Chord
 *
 * Each tone stores its diatonic steps (0-12) and semitones (0-23) above the
 * root, so extensions keep their written numbers: the ninth of a chord is
 * spelled as a ninth, not as a second (SPEC-CHD-2). Semitones are strictly
 * ascending and the first tone is the perfect unison (SPEC-CHD-1).
 *
 * A pattern is eight bytes, trivially copyable and allocation-free, so the
 * same representation is stored in the flash catalog (SPEC-EMB-5).
 * Default construction and every malformed input produce the single invalid
 * pattern (SPEC-ERR-1..3).
 */
class ChordPattern {
public:
    /** @brief Largest number of tones: a full thirteenth chord. */
    static constexpr uint8_t MaximumTones = 7;

private:
    uint32_t _semitones;   // bit k set: a tone lies k semitones above the root
    uint8_t _steps[4];     // diatonic steps of tone i in nibble i

    // Semitones of the major-scale degree `steps` above the root, extended
    // past the octave. Computed rather than tabled so AVR keeps no RAM table.
    static constexpr int32_t NaturalSemitones(int32_t steps) noexcept {
        return (steps / 7) * 12 + (steps % 7) * 2 - ((steps % 7) >= 3 ? 1 : 0);
    }

    constexpr uint8_t StepsAt(uint8_t index) const noexcept {
        return static_cast<uint8_t>((_steps[index / 2] >> ((index % 2) * 4)) & 0x0F);
    }

    constexpr int32_t SemitonesAt(uint8_t index) const noexcept {
        uint8_t seen = 0;
        for (int32_t k = 0; k < 24; ++k) {
            if ((_semitones >> k) & 1u) {
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
    constexpr ChordPattern() noexcept : _semitones(0), _steps{0, 0, 0, 0} {}

    /** @brief Returns the invalid pattern. */
    static constexpr ChordPattern Invalid() noexcept { return ChordPattern(); }

    /**
     * @brief Builds a pattern from a chord formula such as `"1 3 5 b7 9"`.
     *
     * Each space-separated token is an optional run of `b` or `#` followed by
     * a tone number from 1 to 13, read against the major scale. The formula
     * must start with `1`, contain at most seven tones and have strictly
     * ascending semitones below two octaves; otherwise the invalid pattern is
     * returned.
     */
    static constexpr ChordPattern FromFormula(const char* formula) noexcept {
        ChordPattern pattern;
        if (formula == nullptr) {
            return Invalid();
        }
        uint8_t count = 0;
        int32_t previous = -1;
        // Index-based scanning without `continue` keeps GCC 7 (the Arduino
        // AVR toolchain) able to evaluate the loop at compile time.
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
                int32_t number = 0;
                while (formula[i] >= '0' && formula[i] <= '9' && number < 100) {
                    number = number * 10 + (formula[i] - '0');
                    ++i;
                }
                if (number < 1 || number > 13 ||
                    (formula[i] != ' ' && formula[i] != '\0')) {
                    return Invalid();
                }
                const int32_t steps = number - 1;
                const int32_t semitones = NaturalSemitones(steps) + accidental;
                if (count == MaximumTones || semitones <= previous || semitones > 23 ||
                    (count == 0 && (steps != 0 || semitones != 0)) ||
                    !Interval::FromSteps(steps, semitones).IsValid()) {
                    return Invalid();
                }
                pattern._semitones |= (static_cast<uint32_t>(1) << semitones);
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

    /** @brief Returns the number of tones, or 0 for the invalid pattern. */
    constexpr uint8_t ToneCount() const noexcept {
        uint8_t count = 0;
        for (int32_t k = 0; k < 24; ++k) {
            count = static_cast<uint8_t>(count + ((_semitones >> k) & 1u));
        }
        return count;
    }

    /**
     * @brief Returns the ascending interval from the root to `tone`
     * (1-based, in root-position order), or the invalid interval outside
     * `[1, ToneCount()]`.
     */
    constexpr Interval ToneInterval(int32_t tone) const noexcept {
        if (tone < 1 || tone > ToneCount()) {
            return Interval::Invalid();
        }
        const uint8_t index = static_cast<uint8_t>(tone - 1);
        return Interval::FromSteps(StepsAt(index), SemitonesAt(index));
    }

    /**
     * @brief Returns the twelve-bit set of semitones above the root reduced
     * modulo 12; bit k is set when a tone sounds k semitones above the root.
     */
    constexpr uint16_t PitchClassMask() const noexcept {
        return static_cast<uint16_t>((_semitones | (_semitones >> 12)) & 0x0FFFu);
    }

    /** @brief Compares tones, including their written steps. */
    friend constexpr bool operator==(const ChordPattern& a, const ChordPattern& b) noexcept {
        if (a._semitones != b._semitones) {
            return false;
        }
        for (uint8_t i = 0; i < 4; ++i) {
            if (a._steps[i] != b._steps[i]) {
                return false;
            }
        }
        return true;
    }

    /** @brief Negation of `operator==`. */
    friend constexpr bool operator!=(const ChordPattern& a, const ChordPattern& b) noexcept {
        return !(a == b);
    }
};

} // namespace MCC

#endif // MCC_CHORD_CHORD_PATTERN_H
