#include <gtest/gtest.h>

#include "IntervalTestSupport.h"

using MCC::Interval;
using MCC::IntervalDirection;
using MCC::IntervalNumber;
using MCC::IntervalQuality;
using MCC::IntervalQualityKind;
using MCC::NoteName;
using MCC::Pitch;

// SPEC-INT-1, SPEC-INT-4: every valid interval round-trips through its
// derived quality, number and direction.
TEST(IntervalPropertyTests, QualityNumberDirectionRoundTrip) {
    const auto intervals = MCCTests::AllIntervals(22);
    EXPECT_GT(intervals.size(), 45U * 9U);
    for (const Interval interval : intervals) {
        const Interval rebuilt(interval.Quality(), interval.Number(),
            interval.Direction() == IntervalDirection::Unison
                ? IntervalDirection::Ascending : interval.Direction());
        EXPECT_EQ(rebuilt, interval)
            << interval.DiatonicSteps() << " steps, " << interval.Semitones();
        EXPECT_EQ(interval.Reversed().Reversed(), interval);
        EXPECT_EQ(interval.Reversed().Quality(), interval.Quality());
        EXPECT_EQ(interval.Reversed().Number(), interval.Number());
    }
}

// SPEC-INT-3: reducing a compound interval keeps direction and quality and
// removes whole octaves.
TEST(IntervalPropertyTests, SimpleReduction) {
    for (const Interval interval : MCCTests::AllIntervals(22)) {
        const Interval simple = interval.Simple();
        ASSERT_TRUE(simple.IsValid());
        EXPECT_TRUE(simple.IsSimple());
        EXPECT_EQ(simple.Number(), interval.Number().Simple());
        EXPECT_EQ(simple.Quality(), interval.Quality());
        EXPECT_EQ((interval.Semitones() - simple.Semitones()) % 12, 0);
        EXPECT_EQ((interval.DiatonicSteps() - simple.DiatonicSteps()) % 7, 0);
        if (interval.Direction() != IntervalDirection::Unison) {
            EXPECT_EQ(simple.Direction(), interval.Direction());
        }
    }
}

// SPEC-INT-6: inversion of a simple interval: numbers add up to 9, major
// and minor swap, augmented and diminished swap. The only exception is the
// augmented octave, whose inversion would be a diminished unison
// (SPEC-INT-5) and is the augmented unison in the other direction.
TEST(IntervalPropertyTests, Inversion) {
    int checked = 0;
    for (const Interval interval : MCCTests::AllIntervals(7)) {
        const Interval inverted = interval.Inverted();
        ASSERT_TRUE(inverted.IsValid());
        EXPECT_EQ(interval.Number().Value() + inverted.Number().Value(), 9);

        const bool augmentedOctave = interval.Number() == IntervalNumber(8) &&
            interval.Quality().Kind() == IntervalQualityKind::Augmented;
        if (augmentedOctave) {
            EXPECT_EQ(inverted.Quality(), interval.Quality());
            EXPECT_EQ(inverted.Direction(), interval.Reversed().Direction());
        } else {
            EXPECT_EQ(inverted.Quality(), interval.Quality().Inverted());
            if (interval != Interval::Unison() && inverted != Interval::Unison()) {
                EXPECT_EQ(inverted.Direction(), interval.Direction());
                EXPECT_EQ(inverted.Inverted(), interval);
                const int total = (interval.Semitones() + inverted.Semitones()) *
                    (interval.Direction() == IntervalDirection::Ascending ? 1 : -1);
                EXPECT_EQ(total, 12);
            }
        }
        ++checked;
    }
    EXPECT_GT(checked, 0);

    const Interval A8(IntervalQuality::Augmented(), IntervalNumber(8));
    EXPECT_EQ(A8.Inverted(), Interval(IntervalQuality::Augmented(),
        IntervalNumber(1), IntervalDirection::Descending));
    EXPECT_EQ(Interval::Unison().Inverted(),
        Interval(IntervalQuality::Perfect(), IntervalNumber(8)));
    EXPECT_EQ(Interval(IntervalQuality::Major(), IntervalNumber(10)).Inverted(),
        Interval(IntervalQuality::Minor(), IntervalNumber(6)));
}

// SPEC-INT-7: transposition round-trips and moves both indices by exactly
// the interval, or is invalid only when the accidental or octave overflows.
TEST(IntervalPropertyTests, PitchTranspositionRoundTrip) {
    const auto intervals = MCCTests::AllIntervals(14);
    int valid = 0;
    int overflow = 0;
    for (const Pitch pitch : MCCTests::SamplePitches()) {
        for (const Interval interval : intervals) {
            const Pitch moved = pitch + interval;
            if (!moved.IsValid()) {
                // Only the accidental can overflow for octaves 2-5.
                const int naturalIndex = (pitch.DiatonicIndex() + interval.DiatonicSteps());
                const Pitch natural(static_cast<MCC::Letter>(((naturalIndex % 7) + 7) % 7),
                    naturalIndex >= 0 ? naturalIndex / 7 : -((-naturalIndex + 6) / 7));
                const int accidental = pitch.ChromaticIndex().Value() +
                    interval.Semitones() - natural.ChromaticIndex().Value();
                EXPECT_TRUE(accidental < -4 || accidental > 4);
                ++overflow;
                continue;
            }
            ++valid;
            EXPECT_EQ(moved.DiatonicIndex(), pitch.DiatonicIndex() + interval.DiatonicSteps());
            EXPECT_EQ(moved.ChromaticIndex().Value(),
                pitch.ChromaticIndex().Value() + interval.Semitones());
            EXPECT_EQ(MCC::IntervalBetween(pitch, moved), interval);
            EXPECT_EQ(moved - interval, pitch);
        }
    }
    EXPECT_GT(valid, 0);
    EXPECT_GT(overflow, 0);
}

// SPEC-INT-7: note-name transposition agrees with pitch transposition and
// with pitch-class arithmetic.
TEST(IntervalPropertyTests, NoteNameTransposition) {
    const auto intervals = MCCTests::AllIntervals(14);
    for (const NoteName noteName : MCCTests::AllNoteNames()) {
        for (const Interval interval : intervals) {
            const NoteName moved = noteName + interval;
            const Pitch movedPitch = Pitch(noteName, 4) + interval;
            EXPECT_EQ(moved, movedPitch.NoteName());
            if (moved.IsValid()) {
                EXPECT_EQ(moved.PitchClass(),
                    noteName.PitchClass().Transposed(interval.Semitones()));
                EXPECT_EQ(moved - interval, noteName);
            }
        }
    }
}
