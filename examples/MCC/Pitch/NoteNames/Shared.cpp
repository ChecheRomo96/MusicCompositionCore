#include "Shared.h"

#include <MCC_Pitch.h>

namespace MCCExamples {
namespace Pitch {
namespace NoteNames {

namespace {

// MCC has no text formatting yet (Phase 8), so the example spells note
// names itself with the ASCII convention: '#' sharp, 'b' flat.
constexpr char LetterNames[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};

// Writes the spelling of `noteName` into `buffer` (at least 6 chars).
void Spell(MCC::NoteName noteName, char* buffer) noexcept {
    if (!noteName.IsValid()) {
        const char invalid[] = "(inv)";
        for (int i = 0; i < 6; ++i) {
            buffer[i] = invalid[i];
        }
        return;
    }

    int length = 0;
    buffer[length++] = LetterNames[MCC::DiatonicIndex(noteName.Letter())];
    const int semitones = noteName.Accidental().Semitones();
    const char symbol = semitones > 0 ? '#' : 'b';
    for (int i = 0; i < (semitones > 0 ? semitones : -semitones); ++i) {
        buffer[length++] = symbol;
    }
    buffer[length] = '\0';
}

// Writes `value` (0-99) into `buffer`.
void Number(int value, char* buffer) noexcept {
    int length = 0;
    if (value >= 10) {
        buffer[length++] = static_cast<char>('0' + value / 10);
    }
    buffer[length++] = static_cast<char>('0' + value % 10);
    buffer[length] = '\0';
}

// Prints `text` padded with spaces to `width` characters.
void Padded(PrintFunction print, const char* text, int width) noexcept {
    int length = 0;
    while (text[length] != '\0') {
        ++length;
    }
    print(text);
    for (int i = length; i < width; ++i) {
        print(" ");
    }
}

void PrintNoteName(PrintFunction print, MCC::NoteName noteName,
                     int width) noexcept {
    char spelling[6];
    Spell(noteName, spelling);
    Padded(print, spelling, width);
}

void PrintBool(PrintFunction print, bool value) noexcept {
    print(value ? "true" : "false");
}

void PitchClassTable(PrintFunction print) noexcept {
    print("\n1) Pitch class of the 7 x 9 spellings\n");
    print("   (letter semitone + accidental) mod 12\n\n");
    print("        bbbb  bbb   bb    b     nat   #     ##    ###   ####\n");

    for (int letter = 0; letter < MCC::LetterCount; ++letter) {
        const char name[] = {' ', ' ', ' ', LetterNames[letter], '\0'};
        Padded(print, name, 8);
        for (int accidental = -4; accidental <= 4; ++accidental) {
            const MCC::NoteName noteName(
                static_cast<MCC::Letter>(letter), MCC::Accidental(accidental));
            char value[3];
            Number(noteName.PitchClass().Value(), value);
            Padded(print, value, 6);
        }
        print("\n");
    }
}

void EqualityVersusEnharmonic(PrintFunction print) noexcept {
    print("\n2) Written equality versus enharmonic equivalence\n\n");

    const MCC::NoteName pairs[][2] = {
        {MCC::NoteName(MCC::Letter::C, MCC::Accidental::Sharp()),
         MCC::NoteName(MCC::Letter::D, MCC::Accidental::Flat())},
        {MCC::NoteName(MCC::Letter::B, MCC::Accidental::Sharp()),
         MCC::NoteName(MCC::Letter::C)},
        {MCC::NoteName(MCC::Letter::E), MCC::NoteName(MCC::Letter::F)},
        {MCC::NoteName(MCC::Letter::G, MCC::Accidental::Sharp()),
         MCC::NoteName(MCC::Letter::G, MCC::Accidental::Sharp())},
    };

    print("   a      b      a == b   IsEnharmonic(a, b)\n");
    for (const auto& pair : pairs) {
        print("   ");
        PrintNoteName(print, pair[0], 7);
        PrintNoteName(print, pair[1], 7);
        Padded(print, pair[0] == pair[1] ? "true" : "false", 9);
        PrintBool(print, MCC::IsEnharmonic(pair[0], pair[1]));
        print("\n");
    }
}

void DiatonicMovement(PrintFunction print) noexcept {
    print("\n3) Diatonic movement keeps the written accidental\n\n");

    const MCC::NoteName starts[] = {
        MCC::NoteName(MCC::Letter::C, MCC::Accidental::Sharp()),
        MCC::NoteName(MCC::Letter::B, MCC::Accidental::Flat()),
        MCC::NoteName(MCC::Letter::F, MCC::Accidental::QuadrupleSharp()),
    };

    for (const MCC::NoteName start : starts) {
        print("   ");
        for (int steps = 0; steps <= 7; ++steps) {
            PrintNoteName(print, start.MovedDiatonically(steps), 7);
        }
        print("\n");
    }
}

void BoundaryAccidentals(PrintFunction print) noexcept {
    print("\n4) Altering the accidental never respells\n\n");

    const MCC::NoteName start(MCC::Letter::C, MCC::Accidental::DoubleSharp());
    for (int delta = -7; delta <= 3; ++delta) {
        const MCC::NoteName altered = start.Altered(delta);
        print("   C## altered by ");
        if (delta >= 0) {
            print("+");
        } else {
            print("-");
        }
        char value[3];
        Number(delta >= 0 ? delta : -delta, value);
        Padded(print, value, 3);
        print("-> ");
        PrintNoteName(print, altered, 7);
        if (altered.IsValid()) {
            char chromatic[3];
            Number(altered.PitchClass().Value(), chromatic);
            print("class ");
            print(chromatic);
        } else {
            print("outside [-4, +4]");
        }
        print("\n");
    }
}

void WrittenOrder(PrintFunction print) noexcept {
    print("\n5) Written order is letter, then accidental (not pitch height)\n\n");

    MCC::NoteName values[] = {
        MCC::NoteName(MCC::Letter::D, MCC::Accidental::Flat()),
        MCC::NoteName(MCC::Letter::C, MCC::Accidental::DoubleSharp()),
        MCC::NoteName(MCC::Letter::B, MCC::Accidental::Sharp()),
        MCC::NoteName(MCC::Letter::C),
        MCC::NoteName(MCC::Letter::C, MCC::Accidental::Flat()),
        MCC::NoteName(),
    };
    constexpr int count = sizeof(values) / sizeof(values[0]);

    // Insertion sort with operator<: no standard library on AVR.
    for (int i = 1; i < count; ++i) {
        const MCC::NoteName current = values[i];
        int j = i - 1;
        while (j >= 0 && current < values[j]) {
            values[j + 1] = values[j];
            --j;
        }
        values[j + 1] = current;
    }

    print("   sorted: ");
    for (const MCC::NoteName value : values) {
        PrintNoteName(print, value, 7);
    }
    print("\n   class:  ");
    for (const MCC::NoteName value : values) {
        char chromatic[3];
        if (value.IsValid()) {
            Number(value.PitchClass().Value(), chromatic);
            Padded(print, chromatic, 7);
        } else {
            Padded(print, "-", 7);
        }
    }
    print("\n");
}

} // namespace

void Run(PrintFunction print) noexcept {
    print("========================================\n");
    print(" MCC :: Pitch / NoteNames\n");
    print("========================================\n");
    PitchClassTable(print);
    EqualityVersusEnharmonic(print);
    DiatonicMovement(print);
    BoundaryAccidentals(print);
    WrittenOrder(print);
    print("========================================\n");
}

} // namespace NoteNames
} // namespace Pitch
} // namespace MCCExamples
