#ifndef MCC_KEY_KEY_SIGNATURE_H
#define MCC_KEY_KEY_SIGNATURE_H

#include <stdint.h>

#include <MCC/Pitch/Accidental.h>
#include <MCC/Pitch/Letter.h>

namespace MCC {

/**
 * @brief Key signature: zero to seven sharps or flats (SPEC-KEY-1).
 * @ingroup MCC_Key
 *
 * Stored as a signed position on the circle of fifths: positive values count
 * sharps (F C G D A E B), negative values count flats (B E A D G C F).
 * Values outside `[-7, 7]` produce the single invalid signature.
 */
class KeySignature {
    static constexpr int8_t InvalidValue = -128;

    int8_t _fifths;

    // Position of a letter in the order of sharps: F C G D A E B.
    static constexpr int32_t SharpOrder(Letter letter) noexcept {
        return (DiatonicIndex(letter) * 2 + 1) % 7;
    }

public:
    /** @brief Creates the invalid signature (SPEC-ERR-2). */
    constexpr KeySignature() noexcept : _fifths(InvalidValue) {}

    /** @brief Creates a signature of `fifths` sharps (positive) or flats (negative). */
    constexpr explicit KeySignature(int32_t fifths) noexcept
        : _fifths(fifths >= -7 && fifths <= 7 ? static_cast<int8_t>(fifths) : InvalidValue) {}

    /** @brief Returns the invalid signature. */
    static constexpr KeySignature Invalid() noexcept { return KeySignature(); }

    /** @brief Returns `true` unless this is the invalid signature. */
    constexpr bool IsValid() const noexcept { return _fifths != InvalidValue; }

    /** @brief Returns sharps as positive and flats as negative; 0 when invalid. */
    constexpr int8_t Fifths() const noexcept { return IsValid() ? _fifths : 0; }

    /** @brief Returns the number of sharps. */
    constexpr uint8_t Sharps() const noexcept {
        return static_cast<uint8_t>(Fifths() > 0 ? Fifths() : 0);
    }

    /** @brief Returns the number of flats. */
    constexpr uint8_t Flats() const noexcept {
        return static_cast<uint8_t>(Fifths() < 0 ? -Fifths() : 0);
    }

    /**
     * @brief Returns the accidental the signature applies to `letter`:
     * sharp, flat or natural; invalid for the invalid signature.
     */
    constexpr MCC::Accidental AccidentalOf(Letter letter) const noexcept {
        if (!IsValid()) {
            return MCC::Accidental::Invalid();
        }
        const int32_t order = SharpOrder(letter);
        if (order < Sharps()) {
            return MCC::Accidental::Sharp();
        }
        if (6 - order < Flats()) {
            return MCC::Accidental::Flat();
        }
        return MCC::Accidental::Natural();
    }

    /** @brief Compares signatures. */
    friend constexpr bool operator==(KeySignature a, KeySignature b) noexcept {
        return a._fifths == b._fifths;
    }

    /** @brief Negation of `operator==`. */
    friend constexpr bool operator!=(KeySignature a, KeySignature b) noexcept {
        return !(a == b);
    }
};

} // namespace MCC

#endif // MCC_KEY_KEY_SIGNATURE_H
