#include "Shared.h"

#include <MCC_Tuning.h>

namespace MCCExamples::Tuning::Pitches {

namespace {

// MCC has no text formatting yet (Phase 8), so the example writes pitches
// itself with the ASCII convention: '#' sharp, 'b' flat, octave number.
constexpr char LetterNames[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};

// Writes `value` into `buffer` (at least 12 chars) and returns its length.
int Integer(long value, char* buffer) noexcept {
    char digits[12];
    int count = 0;
    const bool negative = value < 0;
    unsigned long magnitude = negative ? 0UL - static_cast<unsigned long>(value)
                                       : static_cast<unsigned long>(value);
    do {
        digits[count++] = static_cast<char>('0' + magnitude % 10);
        magnitude /= 10;
    } while (magnitude != 0);

    int length = 0;
    if (negative) {
        buffer[length++] = '-';
    }
    while (count > 0) {
        buffer[length++] = digits[--count];
    }
    buffer[length] = '\0';
    return length;
}

// Writes `pitch` (for example "C#4" or "Cbbbb-128") into `buffer`.
void Spell(MCC::Pitch pitch, char* buffer) noexcept {
    if (!pitch.IsValid()) {
        const char invalid[] = "(inv)";
        for (int i = 0; i < 6; ++i) {
            buffer[i] = invalid[i];
        }
        return;
    }
    int length = 0;
    buffer[length++] = LetterNames[MCC::DiatonicIndex(pitch.Letter())];
    const int semitones = pitch.Accidental().Semitones();
    for (int i = 0; i < (semitones > 0 ? semitones : -semitones); ++i) {
        buffer[length++] = semitones > 0 ? '#' : 'b';
    }
    Integer(pitch.Octave(), buffer + length);
}

// Writes `hertz` with two decimals into `buffer`.
void Hertz(float hertz, char* buffer) noexcept {
    const long hundredths = static_cast<long>(hertz * 100.0f + 0.5f);
    int length = Integer(hundredths / 100, buffer);
    const long fraction = hundredths % 100;
    buffer[length++] = '.';
    buffer[length++] = static_cast<char>('0' + fraction / 10);
    buffer[length++] = static_cast<char>('0' + fraction % 10);
    buffer[length] = '\0';
}

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

void PrintPitchRow(PrintFunction print, MCC::Pitch pitch,
                   MCC::EqualTemperament temperament) noexcept {
    char text[16];
    print("   ");
    Spell(pitch, text);
    Padded(print, text, 11);
    Integer(pitch.ChromaticIndex().Value(), text);
    Padded(print, text, 8);
    Hertz(temperament.Frequency(pitch), text);
    print(text);
    print(" Hz\n");
}

void WrittenOctaves(PrintFunction print, MCC::EqualTemperament temperament) noexcept {
    print("\n1) The octave belongs to the letter (middle C is C4)\n\n");
    print("   pitch      index   frequency\n");
    const MCC::Pitch pitches[] = {
        MCC::Pitch(MCC::Letter::B, 3),
        MCC::Pitch(MCC::Letter::B, MCC::Accidental::Sharp(), 3),
        MCC::Pitch(MCC::Letter::C, 4),
        MCC::Pitch(MCC::Letter::C, MCC::Accidental::Flat(), 4),
        MCC::Pitch(MCC::Letter::A, 4),
    };
    for (const MCC::Pitch pitch : pitches) {
        PrintPitchRow(print, pitch, temperament);
    }
}

void DiatonicWalk(PrintFunction print, MCC::EqualTemperament temperament) noexcept {
    print("\n2) Diatonic movement from A#3 crosses into octave 4 at C\n\n");
    print("   pitch      index   frequency\n");
    const MCC::Pitch start(MCC::Letter::A, MCC::Accidental::Sharp(), 3);
    for (int steps = 0; steps <= 4; ++steps) {
        PrintPitchRow(print, start.MovedDiatonically(steps), temperament);
    }
}

void HeightVersusWritten(PrintFunction print) noexcept {
    print("\n3) Written order versus pitch height\n\n");
    MCC::Pitch written[] = {
        MCC::Pitch(MCC::Letter::C, 4),
        MCC::Pitch(MCC::Letter::B, MCC::Accidental::Sharp(), 3),
        MCC::Pitch(MCC::Letter::C, MCC::Accidental::Flat(), 4),
        MCC::Pitch(MCC::Letter::A, 3),
    };
    MCC::Pitch height[4];
    constexpr int count = 4;
    for (int i = 0; i < count; ++i) {
        height[i] = written[i];
    }

    // Insertion sort: no standard library on AVR.
    auto sort = [](MCC::Pitch* values, bool (*less)(MCC::Pitch, MCC::Pitch)) {
        for (int i = 1; i < count; ++i) {
            const MCC::Pitch current = values[i];
            int j = i - 1;
            while (j >= 0 && less(current, values[j])) {
                values[j + 1] = values[j];
                --j;
            }
            values[j + 1] = current;
        }
    };
    sort(written, [](MCC::Pitch a, MCC::Pitch b) { return a < b; });
    sort(height, MCC::IsLowerThan);

    char text[16];
    print("   operator<:   ");
    for (const MCC::Pitch pitch : written) {
        Spell(pitch, text);
        Padded(print, text, 6);
    }
    print("\n   IsLowerThan: ");
    for (const MCC::Pitch pitch : height) {
        Spell(pitch, text);
        Padded(print, text, 6);
    }
    print("\n");
}

void Tunings(PrintFunction print) noexcept {
    print("\n4) Frequency of C4 under different tunings\n\n");
    const MCC::Tuning tunings[] = {
        MCC::Tuning::Standard(),
        MCC::Tuning(MCC::Pitch(MCC::Letter::A, 4), 432.0f),
        MCC::Tuning(MCC::Pitch(MCC::Letter::C, 4), 256.0f),
    };
    const char* names[] = {"A4 = 440 Hz", "A4 = 432 Hz", "C4 = 256 Hz"};
    for (int i = 0; i < 3; ++i) {
        char text[16];
        print("   ");
        Padded(print, names[i], 14);
        Hertz(MCC::EqualTemperament(tunings[i])
            .Frequency(MCC::Pitch(MCC::Letter::C, 4)), text);
        print(text);
        print(" Hz\n");
    }
}

} // namespace

void Run(PrintFunction print) noexcept {
    const MCC::EqualTemperament temperament = MCC::EqualTemperament::Standard();
    print("========================================\n");
    print(" MCC :: Tuning / Pitches\n");
    print("========================================\n");
    WrittenOctaves(print, temperament);
    DiatonicWalk(print, temperament);
    HeightVersusWritten(print);
    Tunings(print);
    print("========================================\n");
}

} // namespace MCCExamples::Tuning::Pitches
