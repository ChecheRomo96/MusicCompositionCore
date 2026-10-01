#include <gtest/gtest.h>

#include <MCC.h>

#include <string>

namespace Notation = MCC::Notation;
using MCC::Accidental;
using MCC::Interval;
using MCC::IntervalDirection;
using MCC::IntervalNumber;
using MCC::IntervalQuality;
using MCC::Letter;
using MCC::NoteName;
using MCC::NotationOptions;
using MCC::Pitch;

namespace {

template <typename T>
std::string Text(T value, NotationOptions options = NotationOptions()) {
    char buffer[32];
    const size_t length = Notation::Format(buffer, sizeof(buffer), value, options);
    EXPECT_EQ(length, std::string(buffer).size());
    return buffer;
}

}

TEST(NotationTests, FormatsNoteNamesInAscii) {
    EXPECT_EQ(Text(NoteName(Letter::C)), "C");
    EXPECT_EQ(Text(NoteName(Letter::F, Accidental::Sharp())), "F#");
    EXPECT_EQ(Text(NoteName(Letter::B, Accidental(-3))), "Bbbb");
    EXPECT_EQ(Text(NoteName(Letter::E, Accidental(4))), "E####");
    NotationOptions natural;
    natural.explicitNatural = true;
    EXPECT_EQ(Text(NoteName(Letter::A), natural), "An");
    EXPECT_EQ(Text(NoteName::Invalid()), "(invalid)");
}

TEST(NotationTests, FormatsUnicodeAccidentals) {
    NotationOptions unicode;
    unicode.symbols = MCC::NotationSymbols::Unicode;
    EXPECT_EQ(Text(NoteName(Letter::F, Accidental::Sharp()), unicode), "F\u266F");
    EXPECT_EQ(Text(NoteName(Letter::B, Accidental::Flat()), unicode), "B\u266D");
    EXPECT_EQ(Text(NoteName(Letter::C, Accidental(2)), unicode), "C\U0001D12A");
    EXPECT_EQ(Text(NoteName(Letter::D, Accidental(-3)), unicode), "D\U0001D12B\u266D");
    unicode.explicitNatural = true;
    EXPECT_EQ(Text(NoteName(Letter::G), unicode), "G\u266E");
}

TEST(NotationTests, FormatsPitchesAndIntervals) {
    EXPECT_EQ(Text(Pitch(Letter::C, 4)), "C4");
    EXPECT_EQ(Text(Pitch(Letter::G, Accidental::Sharp(), -1)), "G#-1");
    EXPECT_EQ(Text(Pitch(Letter::B, Accidental::Flat(), 10)), "Bb10");
    EXPECT_EQ(Text(Pitch::Invalid()), "(invalid)");
    EXPECT_EQ(Text(Interval(IntervalQuality::Perfect(), IntervalNumber(5))), "P5");
    EXPECT_EQ(Text(Interval(IntervalQuality::Minor(), IntervalNumber(3),
                            IntervalDirection::Descending)), "-m3");
    EXPECT_EQ(Text(Interval(IntervalQuality::Augmented(2), IntervalNumber(4))), "AA4");
    EXPECT_EQ(Text(Interval(IntervalQuality::Diminished(), IntervalNumber(12))), "d12");
    EXPECT_EQ(Text(Interval::Invalid()), "(invalid)");
}

TEST(NotationTests, EncodesUtf16AndUtf32) {
    NotationOptions unicode;
    unicode.symbols = MCC::NotationSymbols::Unicode;
    const Pitch cDoubleSharp(Letter::C, Accidental(2), 4);

    char16_t utf16[8];
    EXPECT_EQ(Notation::Format(utf16, 8, cDoubleSharp, unicode), 4U);
    EXPECT_EQ(std::u16string(utf16), u"C\U0001D12A4");          // surrogate pair
    EXPECT_EQ(utf16[1], char16_t(0xD834));
    EXPECT_EQ(utf16[2], char16_t(0xDD2A));
    EXPECT_EQ(Notation::Format(utf16, 8, Pitch(Letter::B, Accidental::Flat(), 3), unicode), 3U);
    EXPECT_EQ(std::u16string(utf16), u"B\u266D3");

    char32_t utf32[8];
    EXPECT_EQ(Notation::Format(utf32, 8, cDoubleSharp, unicode), 3U);
    EXPECT_EQ(std::u32string(utf32), U"C\U0001D12A4");
    EXPECT_EQ(Notation::Format(utf32, 8, cDoubleSharp), 4U);        // ASCII symbols, UTF-32 units
    EXPECT_EQ(std::u32string(utf32), U"C##4");

    char16_t chord[16];
    Notation::Format(chord, 16, NoteName(Letter::C, Accidental::Sharp()),
                     MCC::Chords::Id::HalfDiminishedSeventh, unicode);
    EXPECT_EQ(std::u16string(chord), u"C\u266Fm7b5");
}

TEST(NotationTests, TruncationNeverSplitsACharacter) {
    NotationOptions unicode;
    unicode.symbols = MCC::NotationSymbols::Unicode;
    const NoteName cDoubleSharp(Letter::C, Accidental(2));
    char utf8[4];                                   // "C" + the 4-byte double sharp does not fit
    EXPECT_EQ(Notation::Format(utf8, sizeof(utf8), cDoubleSharp, unicode), 5U);
    EXPECT_STREQ(utf8, "C");
    char16_t utf16[3];                              // "C" + a surrogate pair does not fit
    EXPECT_EQ(Notation::Format(utf16, 3, cDoubleSharp, unicode), 3U);
    EXPECT_EQ(std::u16string(utf16), u"C");
    char32_t utf32[1];
    EXPECT_EQ(Notation::Format(utf32, 1, cDoubleSharp, unicode), 2U);
    EXPECT_EQ(utf32[0], U'\0');
}

TEST(NotationTests, FollowsSnprintfSemantics) {
    char small[3] = {'x', 'x', 'x'};
    EXPECT_EQ(Notation::Format(small, sizeof(small), Pitch(Letter::C, Accidental::Sharp(), -1)), 4U);
    EXPECT_STREQ(small, "C#");
    char untouched = 'x';
    EXPECT_EQ(Notation::Format(&untouched, 0, NoteName(Letter::C)), 1U);
    EXPECT_EQ(untouched, 'x');
    EXPECT_EQ(Notation::Format(static_cast<char*>(nullptr), 0, Pitch(Letter::A, 4)), 2U);
}

TEST(NotationTests, ParsesTheAsciiForm) {
    EXPECT_EQ(Notation::ParseNoteName("C"), NoteName(Letter::C));
    EXPECT_EQ(Notation::ParseNoteName("Ebb"), NoteName(Letter::E, Accidental(-2)));
    EXPECT_EQ(Notation::ParseNoteName("Bn"), NoteName(Letter::B));
    EXPECT_EQ(Notation::ParsePitch("F#3"), Pitch(Letter::F, Accidental::Sharp(), 3));
    EXPECT_EQ(Notation::ParsePitch("Cb-1"), Pitch(Letter::C, Accidental::Flat(), -1));
    EXPECT_EQ(Notation::ParseInterval("M3"), Interval(IntervalQuality::Major(), IntervalNumber(3)));
    EXPECT_EQ(Notation::ParseInterval("-P8"), Interval(IntervalQuality::Perfect(), IntervalNumber(8),
                                                       IntervalDirection::Descending));
    EXPECT_EQ(Notation::ParseInterval("ddd7"), Interval(IntervalQuality::Diminished(3), IntervalNumber(7)));
}

TEST(NotationTests, RejectsMalformedText) {
    const char* const noteNames[] = {nullptr, "", "H", "h", "C#b", "C#####", "C ", "Cxx#", "Cnb", "C\xE2\x99"};
    for (const char* text : noteNames) {
        EXPECT_FALSE(Notation::ParseNoteName(text).IsValid()) << (text ? text : "null");
    }
    const char* const pitches[] = {nullptr, "C", "C4x", "4", "C--1", "C99999", "C200"};
    for (const char* text : pitches) {
        EXPECT_FALSE(Notation::ParsePitch(text).IsValid()) << (text ? text : "null");
    }
    const char* const intervals[] = {nullptr, "", "3", "P3", "M5", "m4", "AAAAA4", "X3", "M-3", "P", "+-M3", "M+3"};
    for (const char* text : intervals) {
        EXPECT_FALSE(Notation::ParseInterval(text).IsValid()) << (text ? text : "null");
    }
}

TEST(NotationTests, ParsingIsFlexible) {
    const NoteName fSharp(Letter::F, Accidental::Sharp());
    const NoteName bFlat(Letter::B, Accidental::Flat());
    const NoteName gDoubleSharp(Letter::G, Accidental(2));
    // Either letter case, x for the double sharp, and mixed sharp symbols.
    EXPECT_EQ(Notation::ParseNoteName("f#"), fSharp);
    EXPECT_EQ(Notation::ParseNoteName("bb"), bFlat);
    EXPECT_EQ(Notation::ParseNoteName("Gx"), gDoubleSharp);
    EXPECT_EQ(Notation::ParseNoteName("Gx#"), NoteName(Letter::G, Accidental(3)));
    // Unicode symbols in UTF-8, UTF-16 and UTF-32.
    EXPECT_EQ(Notation::ParseNoteName("F\u266F"), fSharp);
    EXPECT_EQ(Notation::ParseNoteName("G\U0001D12A"), gDoubleSharp);
    EXPECT_EQ(Notation::ParseNoteName("B\u266E"), NoteName(Letter::B));
    EXPECT_EQ(Notation::ParseNoteName(u"B\u266D"), bFlat);
    EXPECT_EQ(Notation::ParseNoteName(u"E\U0001D12B"), NoteName(Letter::E, Accidental(-2)));
    EXPECT_EQ(Notation::ParseNoteName(U"f\u266F"), fSharp);
    EXPECT_EQ(Notation::ParsePitch(u"F\u266F3"), Pitch(Letter::F, Accidental::Sharp(), 3));
    EXPECT_EQ(Notation::ParsePitch(U"cx-1"), Pitch(Letter::C, Accidental(2), -1));
    EXPECT_EQ(Notation::ParseInterval("+M3"), Interval(IntervalQuality::Major(), IntervalNumber(3)));
    EXPECT_EQ(Notation::ParseInterval(u"-AA4"), Interval(IntervalQuality::Augmented(2), IntervalNumber(4),
                                                          IntervalDirection::Descending));
    // Malformed UTF-16 (a lone surrogate) is rejected.
    const char16_t lone[] = {u'C', char16_t(0xD834), 0};
    EXPECT_FALSE(Notation::ParseNoteName(lone).IsValid());
    EXPECT_FALSE(Notation::ParseNoteName(static_cast<const char32_t*>(nullptr)).IsValid());
}

TEST(NotationTests, FormatsThroughACodePointSink) {
    struct Collector {
        std::u32string text;
        static void Add(uint32_t codePoint, void* context) {
            static_cast<Collector*>(context)->text.push_back(static_cast<char32_t>(codePoint));
        }
    };
    Collector collector;
    NotationOptions unicode;
    unicode.symbols = MCC::NotationSymbols::Unicode;
    EXPECT_EQ(Notation::Format(&Collector::Add, &collector,
                               Pitch(Letter::E, Accidental(-2), 2), unicode), 3U);
    EXPECT_EQ(collector.text, U"E\U0001D12B2");
    collector.text.clear();
    EXPECT_EQ(Notation::Format(&Collector::Add, &collector,
                               MCC::Key(NoteName(Letter::D), MCC::KeyMode::Dorian)), 8U);
    EXPECT_EQ(collector.text, U"D Dorian");
    // A null sink only counts.
    EXPECT_EQ(Notation::Format(static_cast<Notation::CodePointSink>(nullptr), nullptr,
                               NoteName(Letter::C, Accidental::Sharp())), 2U);
}

TEST(NotationTests, FormattingRoundTripsThroughParsing) {
    for (int letter = 0; letter < 7; ++letter) {
        for (int accidental = -4; accidental <= 4; ++accidental) {
            for (int octave = -2; octave <= 9; ++octave) {
                const Pitch pitch(static_cast<Letter>(letter), Accidental(accidental), octave);
                EXPECT_EQ(Notation::ParsePitch(Text(pitch).c_str()), pitch) << Text(pitch);
            }
        }
    }
    NotationOptions unicode;
    unicode.symbols = MCC::NotationSymbols::Unicode;
    for (int letter = 0; letter < 7; ++letter) {
        for (int accidental = -4; accidental <= 4; ++accidental) {
            const Pitch pitch(static_cast<Letter>(letter), Accidental(accidental), 4);
            char utf8[16];
            char16_t utf16[16];
            char32_t utf32[16];
            Notation::Format(utf8, 16, pitch, unicode);
            Notation::Format(utf16, 16, pitch, unicode);
            Notation::Format(utf32, 16, pitch, unicode);
            EXPECT_EQ(Notation::ParsePitch(utf8), pitch);
            EXPECT_EQ(Notation::ParsePitch(utf16), pitch);
            EXPECT_EQ(Notation::ParsePitch(utf32), pitch);
        }
    }
    for (int steps = -15; steps <= 15; ++steps) {
        for (int semitones = -26; semitones <= 26; ++semitones) {
            const Interval interval = Interval::FromSteps(steps, semitones);
            if (interval.IsValid()) {
                EXPECT_EQ(Notation::ParseInterval(Text(interval).c_str()), interval) << Text(interval);
            }
        }
    }
}

TEST(NotationTests, FormatsScalesChordsAndKeys) {
    char buffer[40];
    const NoteName cSharp(Letter::C, Accidental::Sharp());
    Notation::Format(buffer, sizeof(buffer), NoteName(Letter::D), MCC::Scales::Id::Dorian);
    EXPECT_STREQ(buffer, "D Dorian");
    Notation::Format(buffer, sizeof(buffer), cSharp, MCC::Chords::Id::HalfDiminishedSeventh);
    EXPECT_STREQ(buffer, "C#m7b5");
    Notation::Format(buffer, sizeof(buffer), NoteName(Letter::C), MCC::Chords::Id::Major);
    EXPECT_STREQ(buffer, "C");
    Notation::Format(buffer, sizeof(buffer), MCC::Key(NoteName(Letter::E), MCC::KeyMode::Minor));
    EXPECT_STREQ(buffer, "E minor");
    Notation::Format(buffer, sizeof(buffer), MCC::Key(cSharp, MCC::KeyMode::Major));
    EXPECT_STREQ(buffer, "C# major");
    Notation::Format(buffer, sizeof(buffer), NoteName(Letter::C), MCC::Chords::Id::Invalid);
    EXPECT_STREQ(buffer, "(invalid)");
    Notation::Format(buffer, sizeof(buffer), MCC::Key());
    EXPECT_STREQ(buffer, "(invalid)");
}
