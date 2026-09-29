#include "Shared.h"

#include <MCC_Interval.h>

namespace MCCExamples::Interval::Intervals {

namespace {

// MCC has no text formatting yet (Phase 8), so the example writes pitches
// ("G#4") and intervals ("M3", "-A1", "dd5") itself.
constexpr char LetterNames[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};

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

int SpellNoteName(MCC::NoteName noteName, char* buffer) noexcept {
    int length = 0;
    buffer[length++] = LetterNames[MCC::DiatonicIndex(noteName.Letter())];
    const int semitones = noteName.Accidental().Semitones();
    for (int i = 0; i < (semitones > 0 ? semitones : -semitones); ++i) {
        buffer[length++] = semitones > 0 ? '#' : 'b';
    }
    buffer[length] = '\0';
    return length;
}

void SpellPitch(MCC::Pitch pitch, char* buffer) noexcept {
    if (!pitch.IsValid()) {
        const char invalid[] = "(inv)";
        for (int i = 0; i < 6; ++i) {
            buffer[i] = invalid[i];
        }
        return;
    }
    const int length = SpellNoteName(pitch.NoteName(), buffer);
    Integer(pitch.Octave(), buffer + length);
}

// Writes an interval as quality + number, "-" first when descending.
void SpellInterval(MCC::Interval interval, char* buffer) noexcept {
    if (!interval.IsValid()) {
        const char invalid[] = "(inv)";
        for (int i = 0; i < 6; ++i) {
            buffer[i] = invalid[i];
        }
        return;
    }
    int length = 0;
    if (interval.Direction() == MCC::IntervalDirection::Descending) {
        buffer[length++] = '-';
    }
    const MCC::IntervalQuality quality = interval.Quality();
    char symbol = 'P';
    switch (quality.Kind()) {
        case MCC::IntervalQualityKind::Major: symbol = 'M'; break;
        case MCC::IntervalQualityKind::Minor: symbol = 'm'; break;
        case MCC::IntervalQualityKind::Augmented: symbol = 'A'; break;
        case MCC::IntervalQualityKind::Diminished: symbol = 'd'; break;
        case MCC::IntervalQualityKind::Perfect: symbol = 'P'; break;
    }
    for (int i = 0; i < quality.Count(); ++i) {
        buffer[length++] = symbol;
    }
    Integer(interval.Number().Value(), buffer + length);
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

MCC::Interval Make(MCC::IntervalQuality quality, int number) noexcept {
    return MCC::Interval(quality, MCC::IntervalNumber(number));
}

void FromC4(PrintFunction print) noexcept {
    print("\n1) Intervals above C4: steps, semitones and result\n\n");
    print("   interval  steps  semis  C4 + interval\n");
    const MCC::Interval intervals[] = {
        Make(MCC::IntervalQuality::Perfect(), 1),
        Make(MCC::IntervalQuality::Augmented(), 1),
        Make(MCC::IntervalQuality::Minor(), 2),
        Make(MCC::IntervalQuality::Major(), 3),
        Make(MCC::IntervalQuality::Augmented(), 4),
        Make(MCC::IntervalQuality::Diminished(), 5),
        Make(MCC::IntervalQuality::Perfect(), 5),
        Make(MCC::IntervalQuality::Minor(), 7),
        Make(MCC::IntervalQuality::Perfect(), 8),
        Make(MCC::IntervalQuality::Major(), 10),
    };
    const MCC::Pitch c4(MCC::Letter::C, 4);
    for (const MCC::Interval interval : intervals) {
        char text[16];
        print("   ");
        SpellInterval(interval, text);
        Padded(print, text, 10);
        Integer(interval.DiatonicSteps(), text);
        Padded(print, text, 7);
        Integer(interval.Semitones(), text);
        Padded(print, text, 7);
        SpellPitch(c4 + interval, text);
        print(text);
        print("\n");
    }
}

void Spelling(PrintFunction print) noexcept {
    print("\n2) Transposition preserves spelling (same sound, different name)\n\n");
    const MCC::Pitch e4(MCC::Letter::E, 4);
    const MCC::Interval rows[] = {
        Make(MCC::IntervalQuality::Major(), 3),
        Make(MCC::IntervalQuality::Diminished(), 4),
    };
    for (const MCC::Interval interval : rows) {
        char text[16];
        print("   E4 + ");
        SpellInterval(interval, text);
        Padded(print, text, 4);
        print(" = ");
        const MCC::Pitch result = e4 + interval;
        SpellPitch(result, text);
        Padded(print, text, 5);
        print(" (index ");
        Integer(result.ChromaticIndex().Value(), text);
        print(text);
        print(")\n");
    }
}

void Between(PrintFunction print) noexcept {
    print("\n3) Intervals between pitches (direction follows the letters)\n\n");
    const MCC::Pitch pairs[][2] = {
        {MCC::Pitch(MCC::Letter::C, 4), MCC::Pitch(MCC::Letter::G, 4)},
        {MCC::Pitch(MCC::Letter::G, 4), MCC::Pitch(MCC::Letter::C, 4)},
        {MCC::Pitch(MCC::Letter::B, MCC::Accidental::Sharp(), 3),
         MCC::Pitch(MCC::Letter::C, 4)},
        {MCC::Pitch(MCC::Letter::C, 4),
         MCC::Pitch(MCC::Letter::C, MCC::Accidental::Flat(), 4)},
    };
    for (const auto& pair : pairs) {
        char text[16];
        print("   ");
        SpellPitch(pair[0], text);
        Padded(print, text, 5);
        print("-> ");
        SpellPitch(pair[1], text);
        Padded(print, text, 5);
        print(" ");
        SpellInterval(MCC::IntervalBetween(pair[0], pair[1]), text);
        print(text);
        print("\n");
    }
}

void Inversions(PrintFunction print) noexcept {
    print("\n4) Inversions: numbers add up to 9, qualities swap\n\n");
    const MCC::Interval intervals[] = {
        Make(MCC::IntervalQuality::Major(), 3),
        Make(MCC::IntervalQuality::Perfect(), 4),
        Make(MCC::IntervalQuality::Augmented(), 4),
        Make(MCC::IntervalQuality::Minor(), 7),
        Make(MCC::IntervalQuality::Augmented(), 8),
    };
    for (const MCC::Interval interval : intervals) {
        char text[16];
        print("   ");
        SpellInterval(interval, text);
        Padded(print, text, 4);
        print("-> ");
        SpellInterval(interval.Inverted(), text);
        print(text);
        print("\n");
    }
}

} // namespace

void Run(PrintFunction print) noexcept {
    print("========================================\n");
    print(" MCC :: Interval / Intervals\n");
    print("========================================\n");
    FromC4(print);
    Spelling(print);
    Between(print);
    Inversions(print);
    print("========================================\n");
}

} // namespace MCCExamples::Interval::Intervals
