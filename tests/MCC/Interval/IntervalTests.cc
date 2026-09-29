#include <gtest/gtest.h>

#include "IntervalTestSupport.h"

using MCC::Accidental;
using MCC::Interval;
using MCC::IntervalDirection;
using MCC::IntervalNumber;
using MCC::IntervalQuality;
using MCC::Letter;
using MCC::NoteName;
using MCC::Pitch;

namespace {

Interval Ascending(IntervalQuality quality, int number) {
    return Interval(quality, IntervalNumber(number));
}

} // namespace

// SPEC-INT-1: an interval stores diatonic steps and semitones; number and
// quality are derived from both.
TEST(IntervalTests, StoresStepsAndSemitones) {
    for (const auto& expected : MCCTests::CommonSimpleIntervals()) {
        const Interval interval = Ascending(expected.quality, expected.number);
        ASSERT_TRUE(interval.IsValid()) << expected.name;
        EXPECT_EQ(interval.DiatonicSteps(), expected.steps) << expected.name;
        EXPECT_EQ(interval.Semitones(), expected.semitones) << expected.name;
        EXPECT_EQ(interval.Number(), IntervalNumber(expected.number)) << expected.name;
        EXPECT_EQ(interval.Quality(), expected.quality) << expected.name;
        EXPECT_EQ(Interval::FromSteps(expected.steps, expected.semitones), interval)
            << expected.name;
    }
}

// SPEC-INT-2: intervals are ascending, descending or unison; the number is
// always positive.
TEST(IntervalTests, Direction) {
    const Interval up = Ascending(IntervalQuality::Major(), 3);
    const Interval down(IntervalQuality::Major(), IntervalNumber(3),
        IntervalDirection::Descending);
    EXPECT_EQ(up.Direction(), IntervalDirection::Ascending);
    EXPECT_EQ(down.Direction(), IntervalDirection::Descending);
    EXPECT_EQ(down.DiatonicSteps(), -2);
    EXPECT_EQ(down.Semitones(), -4);
    EXPECT_EQ(down.Number(), IntervalNumber(3));
    EXPECT_EQ(down.Quality(), IntervalQuality::Major());
    EXPECT_EQ(up.Reversed(), down);
    EXPECT_EQ(Interval::Unison().Direction(), IntervalDirection::Unison);

    // The direction follows the letters: a diminished second whose letters
    // rise is ascending even with 0 semitones, and a triply diminished third
    // is ascending with a negative semitone count.
    const Interval d2 = Ascending(IntervalQuality::Diminished(), 2);
    EXPECT_EQ(d2.Semitones(), 0);
    EXPECT_EQ(d2.Direction(), IntervalDirection::Ascending);
    const Interval dddd3 = Ascending(IntervalQuality::Diminished(4), 3);
    EXPECT_EQ(dddd3.Semitones(), -1);
    EXPECT_EQ(dddd3.Direction(), IntervalDirection::Ascending);
}

// SPEC-INT-3: compound intervals reduce to simple ones by removing octaves.
TEST(IntervalTests, CompoundIntervals) {
    const Interval majorTenth = Ascending(IntervalQuality::Major(), 10);
    EXPECT_EQ(majorTenth.DiatonicSteps(), 9);
    EXPECT_EQ(majorTenth.Semitones(), 16);
    EXPECT_TRUE(majorTenth.IsCompound());
    EXPECT_EQ(majorTenth.Simple(), Ascending(IntervalQuality::Major(), 3));

    const Interval doubleOctave = Ascending(IntervalQuality::Perfect(), 15);
    EXPECT_EQ(doubleOctave.Semitones(), 24);
    EXPECT_EQ(doubleOctave.Simple(), Ascending(IntervalQuality::Perfect(), 8));
    EXPECT_TRUE(Ascending(IntervalQuality::Perfect(), 8).IsSimple());

    const Interval downNinth(IntervalQuality::Minor(), IntervalNumber(9),
        IntervalDirection::Descending);
    EXPECT_EQ(downNinth.Semitones(), -13);
    EXPECT_EQ(downNinth.Simple(), Interval(IntervalQuality::Minor(),
        IntervalNumber(2), IntervalDirection::Descending));

    // Compound intervals keep the quality of their simple part.
    for (const auto& expected : MCCTests::CommonSimpleIntervals()) {
        if (expected.number == 1) {
            continue;
        }
        for (int octaves = 1; octaves <= 3; ++octaves) {
            const Interval compound = Ascending(expected.quality, expected.number + 7 * octaves);
            ASSERT_TRUE(compound.IsValid()) << expected.name;
            EXPECT_EQ(compound.Semitones(), expected.semitones + 12 * octaves);
            EXPECT_EQ(compound.Quality(), expected.quality) << expected.name;
        }
    }
}

// SPEC-INT-4: perfect applies to 1/4/5/8, major/minor to the rest, and
// augmented/diminished repeat up to four times.
TEST(IntervalTests, QualityRules) {
    EXPECT_FALSE(Ascending(IntervalQuality::Perfect(), 3).IsValid());
    EXPECT_FALSE(Ascending(IntervalQuality::Major(), 5).IsValid());
    EXPECT_FALSE(Ascending(IntervalQuality::Minor(), 1).IsValid());
    EXPECT_FALSE(Ascending(IntervalQuality::Major(), 11).IsValid());
    EXPECT_TRUE(Ascending(IntervalQuality::Perfect(), 11).IsValid());

    EXPECT_EQ(Ascending(IntervalQuality::Augmented(4), 2).Semitones(), 6);
    EXPECT_EQ(Ascending(IntervalQuality::Diminished(4), 2).Semitones(), -3);
    EXPECT_EQ(Ascending(IntervalQuality::Augmented(4), 5).Semitones(), 11);
    EXPECT_EQ(Ascending(IntervalQuality::Diminished(4), 5).Semitones(), 3);
    EXPECT_FALSE(Interval::FromSteps(1, 7).IsValid());   // 5x augmented second.
    EXPECT_FALSE(Interval::FromSteps(1, -4).IsValid());  // 5x diminished second.
    EXPECT_FALSE(Interval::FromSteps(4, 12).IsValid());  // 5x augmented fifth.
}

// SPEC-INT-5: there is no diminished unison; C to Cb is a descending
// augmented unison.
TEST(IntervalTests, NoDiminishedUnison) {
    EXPECT_FALSE(Ascending(IntervalQuality::Diminished(), 1).IsValid());
    EXPECT_FALSE(Interval(IntervalQuality::Diminished(), IntervalNumber(1),
        IntervalDirection::Descending).IsValid());

    const Interval cToCFlat = MCC::IntervalBetween(Pitch(Letter::C, 4),
        Pitch(Letter::C, Accidental::Flat(), 4));
    EXPECT_EQ(cToCFlat.Direction(), IntervalDirection::Descending);
    EXPECT_EQ(cToCFlat.Quality(), IntervalQuality::Augmented());
    EXPECT_EQ(cToCFlat.Number(), IntervalNumber(1));
    EXPECT_EQ(cToCFlat, Interval(IntervalQuality::Augmented(), IntervalNumber(1),
        IntervalDirection::Descending));
    EXPECT_EQ(MCC::IntervalBetween(NoteName(Letter::C),
        NoteName(Letter::C, Accidental::Flat())), cToCFlat);

    // No combination of steps 0 and semitones yields a diminished quality.
    for (int semitones = -4; semitones <= 4; ++semitones) {
        const Interval unison = Interval::FromSteps(0, semitones);
        ASSERT_TRUE(unison.IsValid());
        EXPECT_NE(unison.Quality().Kind(), MCC::IntervalQualityKind::Diminished);
    }

    // The perfect unison ignores direction; an augmented unison needs one.
    EXPECT_EQ(Interval(IntervalQuality::Perfect(), IntervalNumber(1),
        IntervalDirection::Descending), Interval::Unison());
    EXPECT_FALSE(Interval(IntervalQuality::Augmented(), IntervalNumber(1),
        IntervalDirection::Unison).IsValid());
    EXPECT_FALSE(Interval(IntervalQuality::Major(), IntervalNumber(3),
        IntervalDirection::Unison).IsValid());
}

// SPEC-INT-1: intervals between pitches are the difference of their
// diatonic and chromatic indices.
TEST(IntervalTests, BetweenPitches) {
    const Pitch c4(Letter::C, 4);
    EXPECT_EQ(MCC::IntervalBetween(c4, Pitch(Letter::E, 4)),
        Ascending(IntervalQuality::Major(), 3));
    EXPECT_EQ(MCC::IntervalBetween(Pitch(Letter::E, 4), c4),
        Ascending(IntervalQuality::Major(), 3).Reversed());
    EXPECT_EQ(MCC::IntervalBetween(Pitch(Letter::B, Accidental::Sharp(), 3), c4),
        Ascending(IntervalQuality::Diminished(), 2));
    EXPECT_EQ(MCC::IntervalBetween(c4, Pitch(Letter::C, 5)),
        Ascending(IntervalQuality::Perfect(), 8));
    EXPECT_EQ(MCC::IntervalBetween(c4, Pitch(Letter::E, 5)),
        Ascending(IntervalQuality::Major(), 10));
    EXPECT_EQ(MCC::IntervalBetween(c4, Pitch(Letter::F, Accidental::Sharp(), 4)),
        Ascending(IntervalQuality::Augmented(), 4));
    EXPECT_EQ(MCC::IntervalBetween(c4, Pitch(Letter::G, Accidental::Flat(), 4)),
        Ascending(IntervalQuality::Diminished(), 5));
    EXPECT_EQ(MCC::IntervalBetween(c4, c4), Interval::Unison());

    // Extreme spans are still representable.
    const Interval widest = MCC::IntervalBetween(Pitch(Letter::C, -128),
        Pitch(Letter::B, 127));
    EXPECT_EQ(widest.Number(), IntervalNumber(1792));
    EXPECT_EQ(widest.Quality(), IntervalQuality::Major());

    // Eight semitones of accidental difference exceed 4x augmented.
    EXPECT_FALSE(MCC::IntervalBetween(Pitch(Letter::C, Accidental::QuadrupleFlat(), 4),
        Pitch(Letter::C, Accidental::QuadrupleSharp(), 4)).IsValid());
}

// SPEC-INT-1: between note names the interval is the simple ascending one
// to the next occurrence of the target letter.
TEST(IntervalTests, BetweenNoteNames) {
    EXPECT_EQ(MCC::IntervalBetween(NoteName(Letter::B), NoteName(Letter::C)),
        Ascending(IntervalQuality::Minor(), 2));
    EXPECT_EQ(MCC::IntervalBetween(NoteName(Letter::E), NoteName(Letter::C)),
        Ascending(IntervalQuality::Minor(), 6));
    EXPECT_EQ(MCC::IntervalBetween(NoteName(Letter::C), NoteName(Letter::C)),
        Interval::Unison());
    EXPECT_EQ(MCC::IntervalBetween(NoteName(Letter::C),
        NoteName(Letter::C, Accidental::Sharp())),
        Ascending(IntervalQuality::Augmented(), 1));

    for (const NoteName from : MCCTests::AllNoteNames()) {
        for (const NoteName to : MCCTests::AllNoteNames()) {
            const Interval interval = MCC::IntervalBetween(from, to);
            if (!interval.IsValid()) {
                continue;
            }
            EXPECT_GE(interval.DiatonicSteps(), 0);
            EXPECT_LE(interval.DiatonicSteps(), 6);
            EXPECT_EQ(from + interval, to);
        }
    }
}

// Intervals add by steps and semitones; enharmonic intervals share their
// signed semitone count.
TEST(IntervalTests, AdditionAndEnharmony) {
    const Interval M3 = Ascending(IntervalQuality::Major(), 3);
    const Interval m3 = Ascending(IntervalQuality::Minor(), 3);
    EXPECT_EQ(M3 + m3, Ascending(IntervalQuality::Perfect(), 5));
    EXPECT_EQ(M3 + M3, Ascending(IntervalQuality::Augmented(), 5));
    EXPECT_EQ(M3 + M3.Reversed(), Interval::Unison());
    const Interval P8 = Ascending(IntervalQuality::Perfect(), 8);
    EXPECT_EQ(P8 + P8, Ascending(IntervalQuality::Perfect(), 15));

    const Interval A4 = Ascending(IntervalQuality::Augmented(), 4);
    const Interval d5 = Ascending(IntervalQuality::Diminished(), 5);
    EXPECT_NE(A4, d5);
    EXPECT_TRUE(MCC::IsEnharmonic(A4, d5));
    EXPECT_FALSE(MCC::IsEnharmonic(A4, d5.Reversed()));
    EXPECT_TRUE(MCC::IsEnharmonic(Interval::Unison(),
        Ascending(IntervalQuality::Diminished(), 2)));
}

// SPEC-INT-7: transposition preserves spelling.
TEST(IntervalTests, TransposesPreservingSpelling) {
    const Interval M3 = Ascending(IntervalQuality::Major(), 3);
    EXPECT_EQ(Pitch(Letter::E, 4) + M3, Pitch(Letter::G, Accidental::Sharp(), 4));
    EXPECT_EQ(Pitch(Letter::G, Accidental::Sharp(), 4) - M3, Pitch(Letter::E, 4));
    EXPECT_EQ(Pitch(Letter::B, 3) + Ascending(IntervalQuality::Minor(), 2),
        Pitch(Letter::C, 4));
    EXPECT_EQ(Pitch(Letter::B, 3) + Ascending(IntervalQuality::Augmented(), 1),
        Pitch(Letter::B, Accidental::Sharp(), 3));
    EXPECT_EQ(Pitch(Letter::C, 4) + Ascending(IntervalQuality::Augmented(), 4),
        Pitch(Letter::F, Accidental::Sharp(), 4));
    EXPECT_EQ(Pitch(Letter::C, 4) + Ascending(IntervalQuality::Diminished(), 5),
        Pitch(Letter::G, Accidental::Flat(), 4));
    EXPECT_EQ(Pitch(Letter::C, 4) + Ascending(IntervalQuality::Major(), 10),
        Pitch(Letter::E, 5));

    EXPECT_EQ(NoteName(Letter::E) + M3, NoteName(Letter::G, Accidental::Sharp()));
    EXPECT_EQ(NoteName(Letter::B) + Ascending(IntervalQuality::Minor(), 2),
        NoteName(Letter::C));
    EXPECT_EQ(NoteName(Letter::C) + Ascending(IntervalQuality::Major(), 10),
        NoteName(Letter::E));
    EXPECT_EQ(NoteName(Letter::C) - M3, NoteName(Letter::A, Accidental::Flat()));

    // Never respelled: an accidental outside +-4 is invalid.
    const Pitch bQuadSharp(Letter::B, Accidental::QuadrupleSharp(), 3);
    EXPECT_FALSE((bQuadSharp + Ascending(IntervalQuality::Augmented(), 1)).IsValid());
    EXPECT_FALSE((NoteName(Letter::F, Accidental::QuadrupleFlat()) -
        Ascending(IntervalQuality::Augmented(), 1)).IsValid());

    // Octave overflow is invalid.
    EXPECT_FALSE((Pitch(Letter::B, 127) + Ascending(IntervalQuality::Minor(), 2)).IsValid());
    EXPECT_FALSE((Pitch(Letter::C, -128) - Ascending(IntervalQuality::Minor(), 2)).IsValid());
}
