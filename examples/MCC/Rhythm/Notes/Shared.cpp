#include "Shared.h"

#include <MCC_Rhythm.h>

namespace MCCExamples {
namespace Rhythm {
namespace Notes {

namespace {

constexpr char LetterNames[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};

void Integer(int32_t value, char* buffer) noexcept {
    char digits[12];
    int count = 0;
    const bool negative = value < 0;
    uint32_t magnitude = negative
        ? uint32_t(0u) - static_cast<uint32_t>(value)
        : static_cast<uint32_t>(value);
    do {
        digits[count++] = static_cast<char>('0' + magnitude % 10u);
        magnitude /= 10u;
    } while (magnitude != 0u);

    int length = 0;
    if (negative) {
        buffer[length++] = '-';
    }
    while (count > 0) {
        buffer[length++] = digits[--count];
    }
    buffer[length] = '\0';
}

void Padded(PrintFunction print, const char* text, int width) noexcept {
    int length = 0;
    while (text[length] != '\0') {
        ++length;
    }
    print(text);
    for (int index = length; index < width; ++index) {
        print(" ");
    }
}

void Spell(MCC::Note note, char* buffer) noexcept {
    if (!note.IsValid()) {
        const char invalid[] = "(invalid)";
        for (int index = 0; index < 10; ++index) {
            buffer[index] = invalid[index];
        }
        return;
    }

    int length = 0;
    buffer[length++] = LetterNames[MCC::DiatonicIndex(note.Letter())];
    const int accidental = note.Accidental().Semitones();
    const int symbols = accidental < 0 ? -accidental : accidental;
    for (int index = 0; index < symbols; ++index) {
        buffer[length++] = accidental < 0 ? 'b' : '#';
    }
    Integer(note.Octave(), buffer + length);
}

void Row(PrintFunction print, const char* expression, MCC::Note note) noexcept {
    char text[16];
    print("   ");
    Padded(print, expression, 54);
    Spell(note, text);
    Padded(print, text, 8);
    Integer(note.Value().Numerator(), text);
    print(text);
    print("/");
    Integer(note.Value().Denominator(), text);
    print(text);
    print("\n");
}

} // namespace

void Run(PrintFunction print) noexcept {
    print("========================================\n");
    print(" MCC :: Rhythm / Notes\n");
    print("========================================\n");
    print("\nPURPOSE\n");
    print("Combine a spelled pitch with an exact written note value.\n");

    print("\n[1] CONSTRUCTION\n\n");
    Row(print, "Note(Pitch(C#, 4), NoteValue::Eighth(1))",
        MCC::Note(
            MCC::Pitch(MCC::Letter::C, MCC::Accidental::Sharp(), 4),
            MCC::NoteValue::Eighth(1)));
    Row(print, "Note(NoteName(Db), 4, NoteValue::Half())",
        MCC::Note(
            MCC::NoteName(MCC::Letter::D, MCC::Accidental::Flat()), 4,
            MCC::NoteValue::Half()));
    Row(print, "Note(Letter::A, 3)",
        MCC::Note(MCC::Letter::A, 3));
    Row(print, "Note(Letter::F, Sharp, 5, Quarter(2))",
        MCC::Note(
            MCC::Letter::F, MCC::Accidental::Sharp(), 5,
            MCC::NoteValue::Quarter(2)));

    print("\n[2] COPY-STYLE CHANGES\n\n");
    const MCC::Note source(
        MCC::Letter::B, MCC::Accidental::Sharp(), 3,
        MCC::NoteValue::Quarter());
    Row(print, "source", source);
    Row(print, "source.MovedDiatonically(1)", source.MovedDiatonically(1));
    Row(print, "source.WithDots(1)", source.WithDots(1));

    print("\nTAKEAWAY\n");
    print("Pitch spelling and rhythmic spelling remain explicit and independent.\n");
    print("========================================\n");
}

} // namespace Notes
} // namespace Rhythm
} // namespace MCCExamples
