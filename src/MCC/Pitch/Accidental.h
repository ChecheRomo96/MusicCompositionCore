#ifndef MCC_PITCH_ACCIDENTAL_H
#define MCC_PITCH_ACCIDENTAL_H

#include <MCC_BuildSettings.h>

#include <stdint.h>

namespace MCC {

/**
 * @brief Chromatic alteration of a letter, from -4 (quadruple flat) to +4
 * (quadruple sharp).
 * @ingroup MCC_Pitch
 *
 * Natural (0) is a distinct written accidental (SPEC-ACC-1, SPEC-ACC-2).
 * Default construction and out-of-range input produce the single invalid
 * value (SPEC-ERR-1..3). Written order is by semitone value; the invalid
 * value sorts after every valid accidental.
 */
class Accidental {
public:
    /** @brief Lowest supported alteration (quadruple flat). */
    static constexpr int8_t Minimum = -4;

    /** @brief Highest supported alteration (quadruple sharp). */
    static constexpr int8_t Maximum = 4;

    /**
     * @brief Sentinel returned by `Semitones()` for the invalid value
     * (SPEC-ERR-7). Do not rely on it; check `IsValid()`.
     */
    static constexpr int8_t InvalidValue = 127;

private:
    int8_t _semitones;

public:
    /** @brief Creates the invalid accidental (SPEC-ERR-2). */
    constexpr Accidental() noexcept : _semitones(InvalidValue) {}

    /**
     * @brief Creates the accidental `semitones`; values outside
     * `[Minimum, Maximum]` produce the invalid value (SPEC-ERR-3).
     */
    constexpr explicit Accidental(int32_t semitones) noexcept
        : _semitones(IsInRange(semitones)
              ? static_cast<int8_t>(semitones)
              : InvalidValue) {}

    /** @brief Returns the invalid accidental. */
    static constexpr Accidental Invalid() noexcept { return Accidental(); }

    /** @brief Returns the quadruple flat (-4). */
    static constexpr Accidental QuadrupleFlat() noexcept { return Accidental(-4); }

    /** @brief Returns the triple flat (-3). */
    static constexpr Accidental TripleFlat() noexcept { return Accidental(-3); }

    /** @brief Returns the double flat (-2). */
    static constexpr Accidental DoubleFlat() noexcept { return Accidental(-2); }

    /** @brief Returns the flat (-1). */
    static constexpr Accidental Flat() noexcept { return Accidental(-1); }

    /** @brief Returns the natural (0). */
    static constexpr Accidental Natural() noexcept { return Accidental(0); }

    /** @brief Returns the sharp (+1). */
    static constexpr Accidental Sharp() noexcept { return Accidental(1); }

    /** @brief Returns the double sharp (+2). */
    static constexpr Accidental DoubleSharp() noexcept { return Accidental(2); }

    /** @brief Returns the triple sharp (+3). */
    static constexpr Accidental TripleSharp() noexcept { return Accidental(3); }

    /** @brief Returns the quadruple sharp (+4). */
    static constexpr Accidental QuadrupleSharp() noexcept { return Accidental(4); }

    /** @brief Returns `true` unless this is the invalid accidental. */
    constexpr bool IsValid() const noexcept {
        return _semitones != InvalidValue;
    }

    /**
     * @brief Returns the alteration in semitones, or `InvalidValue` for the
     * invalid accidental (SPEC-ERR-7).
     */
    constexpr int8_t Semitones() const noexcept { return _semitones; }

    /**
     * @brief Returns this accidental altered by `semitones`.
     *
     * The result is invalid when this accidental is invalid (SPEC-ERR-4) or
     * when it would leave `[Minimum, Maximum]` (SPEC-ACC-3, SPEC-ERR-5).
     */
    MCC_CONSTEXPR14 Accidental Altered(int32_t semitones) const noexcept {
        if (!IsValid() ||
            semitones < Minimum - Maximum ||
            semitones > Maximum - Minimum) {
            return Invalid();
        }
        return Accidental(_semitones + semitones);
    }

    /** @brief Equality; all invalid accidentals are equal (SPEC-ERR-6). */
    friend constexpr bool operator==(Accidental a, Accidental b) noexcept {
        return a._semitones == b._semitones;
    }

    friend constexpr bool operator!=(Accidental a, Accidental b) noexcept {
        return !(a == b);
    }

    /** @brief Orders by semitones; invalid sorts last. */
    friend constexpr bool operator<(Accidental a, Accidental b) noexcept {
        return a._semitones < b._semitones;
    }

    friend constexpr bool operator>(Accidental a, Accidental b) noexcept {
        return b < a;
    }

    friend constexpr bool operator<=(Accidental a, Accidental b) noexcept {
        return !(b < a);
    }

    friend constexpr bool operator>=(Accidental a, Accidental b) noexcept {
        return !(a < b);
    }

private:
    static constexpr bool IsInRange(int32_t semitones) noexcept {
        return semitones >= Minimum && semitones <= Maximum;
    }
};

} // namespace MCC

#endif // MCC_PITCH_ACCIDENTAL_H
