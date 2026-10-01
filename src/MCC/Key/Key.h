#ifndef MCC_KEY_KEY_H
#define MCC_KEY_KEY_H

#include <MCC_BuildSettings.h>

#include <stdint.h>

#include <Foundation/Math/Arithmetic.h>

#include <MCC/Key/KeySignature.h>
#include <MCC/Pitch/ChromaticIndex.h>
#include <MCC/Pitch/NoteName.h>
#include <MCC/Pitch/Pitch.h>
#include <MCC/Pitch/PitchClass.h>
#include <MCC/Scale/Scales.h>

namespace MCC {

/**
 * @brief Diatonic mode of a key, ordered from brightest to darkest.
 * @ingroup MCC_Key
 */
enum class KeyMode : uint8_t {
    Lydian = 0,
    Major,
    Mixolydian,
    Dorian,
    Minor,
    Phrygian,
    Locrian
};

/**
 * @brief A tonic and a diatonic mode, with the key signature they imply.
 * @ingroup MCC_Key
 *
 * The key is modelled separately from its scale (SPEC-KEY-2): `Signature()`
 * follows from the tonic's position on the circle of fifths and the mode, and
 * a tonic whose signature would exceed seven sharps or flats (`G#` major)
 * produces the invalid key. `Spell()` writes any pitch class in the key's
 * context: diatonic pitch classes use the key's own letters; a chromatic one
 * alters a diatonic note by a semitone, preferring the spelling with fewer
 * accidentals and, on a tie, a raised note in sharp keys and a lowered note
 * in flat keys (SPEC-KEY-3).
 */
class Key {
    NoteName _tonic;
    KeyMode _mode;

    // Circle-of-fifths position of a letter relative to C: F -1 ... B 5.
    static constexpr int32_t LetterFifths(Letter letter) noexcept {
        return (DiatonicIndex(letter) * 2 + 1) % 7 - 1;
    }

    // Signature offset of a mode relative to major on the same tonic.
    static constexpr int32_t ModeOffset(KeyMode mode) noexcept {
        return 1 - static_cast<int32_t>(mode);
    }

    static constexpr int32_t SignatureFifths(NoteName tonic, KeyMode mode) noexcept {
        return LetterFifths(tonic.Letter()) + 7 * tonic.Accidental().Semitones() + ModeOffset(mode);
    }

    static constexpr bool IsMode(KeyMode mode) noexcept {
        return static_cast<uint8_t>(mode) <= static_cast<uint8_t>(KeyMode::Locrian);
    }

public:
    /** @brief Creates the invalid key (SPEC-ERR-2). */
    constexpr Key() noexcept : _tonic(), _mode(KeyMode::Major) {}

    /** @brief Creates `tonic` in `mode`; invalid beyond seven sharps or flats. */
    constexpr Key(NoteName tonic, KeyMode mode) noexcept
        : _tonic(tonic.IsValid() && IsMode(mode) &&
                 KeySignature(SignatureFifths(tonic, mode)).IsValid()
              ? tonic : NoteName::Invalid()),
          _mode(IsMode(mode) ? mode : KeyMode::Major) {}

    /** @brief Returns the key with `signature` in `mode` (`2` sharps + Minor = B minor). */
    static MCC_CONSTEXPR14 Key FromSignature(KeySignature signature, KeyMode mode) noexcept {
        if (!signature.IsValid() || !IsMode(mode)) {
            return Key();
        }
        // Tonic position on the circle of fifths, then its letter and accidental.
        const int32_t fifths = signature.Fifths() - ModeOffset(mode);
        const int32_t order = Foundation::Math::FloorMod(fifths + 1, 7);
        const int32_t accidental = Foundation::Math::FloorDiv(fifths + 1, 7);
        const Letter letter = static_cast<Letter>(((order + 6) * 4) % 7);
        return Key(NoteName(letter, Accidental(accidental)), mode);
    }

    /** @brief Returns the invalid key. */
    static constexpr Key Invalid() noexcept { return Key(); }

    /** @brief Returns `true` unless this is the invalid key. */
    constexpr bool IsValid() const noexcept { return _tonic.IsValid(); }

    /** @brief Returns the tonic. */
    constexpr NoteName Tonic() const noexcept { return _tonic; }

    /** @brief Returns the mode. */
    constexpr KeyMode Mode() const noexcept { return _mode; }

    /** @brief Returns the key signature, or the invalid signature. */
    constexpr KeySignature Signature() const noexcept {
        return IsValid() ? KeySignature(SignatureFifths(_tonic, _mode)) : KeySignature();
    }

    /** @brief Returns the catalog scale of the mode, or `Scales::Id::Invalid`. */
    Scales::Id ScaleId() const noexcept;

    /** @brief Returns the key's scale spelled from its tonic. */
    MCC::Scale Scale() const noexcept { return Scales::Make(_tonic, ScaleId()); }

    /** @brief Writes `pitchClass` in this key's context (SPEC-KEY-3). */
    MCC_CONSTEXPR14 NoteName Spell(MCC::PitchClass pitchClass) const noexcept {
        if (!IsValid() || !pitchClass.IsValid()) {
            return NoteName::Invalid();
        }
        const KeySignature signature = Signature();
        const int32_t direction = signature.Fifths() < 0 ? -1 : 1;
        NoteName best;
        int32_t bestScore = 1000;
        for (int32_t index = 0; index < 7; ++index) {
            const Letter letter = static_cast<Letter>(index);
            const int32_t keyAccidental = signature.AccidentalOf(letter).Semitones();
            for (int32_t alteration = -1; alteration <= 1; ++alteration) {
                const NoteName candidate(letter, Accidental(keyAccidental + alteration));
                if (candidate.IsValid() && candidate.PitchClass() == pitchClass) {
                    // Diatonic first, then the fewest accidentals, then the
                    // key's direction: raised in sharp keys, lowered in flat keys.
                    const int32_t accidental = candidate.Accidental().Semitones();
                    const int32_t score = alteration == 0 ? 0
                        : 10 * (accidental < 0 ? -accidental : accidental) +
                          (alteration == direction ? 1 : 2);
                    if (score < bestScore) {
                        best = candidate;
                        bestScore = score;
                    }
                }
            }
        }
        return best;
    }

    /** @brief Writes a sounding chromatic index as a pitch in this key's context. */
    MCC_CONSTEXPR14 MCC::Pitch Spell(MCC::ChromaticIndex index) const noexcept {
        if (!index.IsValid()) {
            return MCC::Pitch::Invalid();
        }
        const NoteName noteName = Spell(index.PitchClass());
        if (!noteName.IsValid()) {
            return MCC::Pitch::Invalid();
        }
        const int32_t offset =
            NaturalSemitone(noteName.Letter()) + noteName.Accidental().Semitones();
        return MCC::Pitch(noteName, Foundation::Math::FloorDiv(index.Value() - offset, 12) - 1);
    }

    /** @brief Compares tonic spelling and mode. */
    friend constexpr bool operator==(const Key& a, const Key& b) noexcept {
        return a._tonic == b._tonic && (!a.IsValid() || a._mode == b._mode);
    }

    /** @brief Negation of `operator==`. */
    friend constexpr bool operator!=(const Key& a, const Key& b) noexcept {
        return !(a == b);
    }
};

} // namespace MCC

#endif // MCC_KEY_KEY_H
