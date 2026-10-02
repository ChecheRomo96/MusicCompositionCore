#ifndef MCC_RHYTHM_NOTE_H
#define MCC_RHYTHM_NOTE_H

#include <stdint.h>

#include <MCC_BuildSettings.h>
#include <MCC/Pitch/Pitch.h>
#include <MCC/Rhythm/NoteValue.h>

namespace MCC {

/**
 * @brief A written pitch combined with an exact written note value.
 * @ingroup MCC_Rhythm
 *
 * `Note` preserves the pitch spelling (`C#4` remains distinct from `Db4`)
 * and the rhythmic spelling (base plus augmentation dots). Constructors that
 * omit the note value use a quarter note. Invalid pitch or value input
 * produces the single invalid note.
 *
 * MIDI conversion deliberately does not live here: a MIDI note number has no
 * written spelling. MIDILAR must provide a key or another spelling policy and
 * then construct an MCC note from the resulting MCC::Pitch.
 */
class Note {
    MCC::Pitch _pitch;
    MCC::NoteValue _value;

public:
    /** @brief Creates the invalid note (SPEC-ERR-2). */
    constexpr Note() noexcept : _pitch(), _value() {}

    /**
     * @brief Creates `pitch` with `value`; the default value is a quarter.
     */
    constexpr explicit Note(
        MCC::Pitch pitch,
        MCC::NoteValue value = MCC::NoteValue::Quarter()) noexcept
        : _pitch(pitch.IsValid() && value.IsValid()
              ? pitch
              : MCC::Pitch::Invalid()),
          _value(pitch.IsValid() && value.IsValid()
              ? value
              : MCC::NoteValue::Invalid()) {}

    /** @brief Creates `noteName` in `octave`, with a quarter by default. */
    constexpr Note(
        MCC::NoteName noteName,
        int32_t octave,
        MCC::NoteValue value = MCC::NoteValue::Quarter()) noexcept
        : Note(MCC::Pitch(noteName, octave), value) {}

    /** @brief Creates natural `letter` in `octave`, with a quarter by default. */
    constexpr Note(
        MCC::Letter letter,
        int32_t octave,
        MCC::NoteValue value = MCC::NoteValue::Quarter()) noexcept
        : Note(MCC::Pitch(letter, octave), value) {}

    /**
     * @brief Creates `letter` + `accidental` in `octave`, with a quarter by
     * default.
     */
    constexpr Note(
        MCC::Letter letter,
        MCC::Accidental accidental,
        int32_t octave,
        MCC::NoteValue value = MCC::NoteValue::Quarter()) noexcept
        : Note(MCC::Pitch(letter, accidental, octave), value) {}

    /** @brief Returns the invalid note. */
    static constexpr Note Invalid() noexcept { return Note(); }

    /** @brief Returns `true` unless this is the invalid note. */
    constexpr bool IsValid() const noexcept {
        return _pitch.IsValid() && _value.IsValid();
    }

    /** @brief Returns the written pitch, or the invalid pitch. */
    constexpr MCC::Pitch Pitch() const noexcept { return _pitch; }

    /** @brief Returns the written note value, or the invalid value. */
    constexpr MCC::NoteValue Value() const noexcept { return _value; }

    /** @brief Returns the written note name, or the invalid note name. */
    constexpr MCC::NoteName NoteName() const noexcept {
        return _pitch.NoteName();
    }

    /** @brief Returns the written letter. */
    constexpr MCC::Letter Letter() const noexcept { return _pitch.Letter(); }

    /** @brief Returns the written accidental, or the invalid accidental. */
    constexpr MCC::Accidental Accidental() const noexcept {
        return _pitch.Accidental();
    }

    /** @brief Returns the written octave, or `0` for the invalid note. */
    constexpr int8_t Octave() const noexcept { return _pitch.Octave(); }

    /** @brief Returns the pitch class, or the invalid pitch class. */
    MCC_CONSTEXPR14 MCC::PitchClass PitchClass() const noexcept {
        return _pitch.PitchClass();
    }

    /** @brief Returns the chromatic index, or the invalid chromatic index. */
    MCC_CONSTEXPR14 MCC::ChromaticIndex ChromaticIndex() const noexcept {
        return _pitch.ChromaticIndex();
    }

    /** @brief Returns the same note value with a new written pitch. */
    constexpr Note WithPitch(MCC::Pitch pitch) const noexcept {
        return Note(pitch, _value);
    }

    /** @brief Returns the same written pitch with a new note value. */
    constexpr Note WithValue(MCC::NoteValue value) const noexcept {
        return Note(_pitch, value);
    }

    /** @brief Returns the same written pitch and base with a new dot count. */
    constexpr Note WithDots(int32_t dots) const noexcept {
        return Note(_pitch, _value.WithDots(dots));
    }

    /** @brief Moves the pitch diatonically and preserves the note value. */
    MCC_CONSTEXPR14 Note MovedDiatonically(int32_t steps) const noexcept {
        return Note(_pitch.MovedDiatonically(steps), _value);
    }

    /** @brief Alters the pitch and preserves the note value. */
    MCC_CONSTEXPR14 Note Altered(int32_t semitones) const noexcept {
        return Note(_pitch.Altered(semitones), _value);
    }

    /** @brief Moves the pitch by octaves and preserves the note value. */
    MCC_CONSTEXPR14 Note MovedByOctaves(int32_t octaves) const noexcept {
        return Note(_pitch.MovedByOctaves(octaves), _value);
    }

    /** @brief Written equality of both pitch and note value. */
    friend constexpr bool operator==(Note a, Note b) noexcept {
        return a._pitch == b._pitch && a._value == b._value;
    }

    friend constexpr bool operator!=(Note a, Note b) noexcept {
        return !(a == b);
    }

    /**
     * @brief Written order by pitch, then exact note-value duration; invalid
     * notes sort last.
     */
    friend MCC_CONSTEXPR14 bool operator<(Note a, Note b) noexcept {
        if (!a.IsValid() || !b.IsValid()) {
            return a.IsValid() && !b.IsValid();
        }
        return a._pitch != b._pitch ? a._pitch < b._pitch : a._value < b._value;
    }

    friend MCC_CONSTEXPR14 bool operator>(Note a, Note b) noexcept {
        return b < a;
    }

    friend MCC_CONSTEXPR14 bool operator<=(Note a, Note b) noexcept {
        return !(b < a);
    }

    friend MCC_CONSTEXPR14 bool operator>=(Note a, Note b) noexcept {
        return !(a < b);
    }
};

/**
 * @brief Orders notes by sounding pitch, then by written pitch and value.
 * @ingroup MCC_Rhythm
 */
MCC_CONSTEXPR14 bool IsNoteLowerThan(Note a, Note b) noexcept {
    if (!a.IsValid() || !b.IsValid()) {
        return a.IsValid() && !b.IsValid();
    }
    if (a.ChromaticIndex() != b.ChromaticIndex()) {
        return a.ChromaticIndex() < b.ChromaticIndex();
    }
    return a.Pitch() != b.Pitch() ? a.Pitch() < b.Pitch() : a.Value() < b.Value();
}

} // namespace MCC

#endif // MCC_RHYTHM_NOTE_H
