#include <gtest/gtest.h>

#include "IntervalTestSupport.h"

using MCC::Interval;
using MCC::IntervalDirection;
using MCC::IntervalNumber;
using MCC::IntervalQuality;
using MCC::Letter;
using MCC::NoteName;
using MCC::Pitch;

// SPEC-ERR-1, SPEC-ERR-2: default construction is the invalid value.
TEST(InvalidStateTests, DefaultConstructionIsInvalid) {
    EXPECT_FALSE(Interval().IsValid());
    EXPECT_FALSE(IntervalNumber().IsValid());
    EXPECT_FALSE(IntervalQuality().IsValid());
    EXPECT_EQ(Interval(), Interval::Invalid());
    EXPECT_EQ(IntervalNumber(), IntervalNumber::Invalid());
    EXPECT_EQ(IntervalQuality(), IntervalQuality::Invalid());
}

// SPEC-ERR-3: out-of-range and inconsistent inputs are invalid.
TEST(InvalidStateTests, OutOfRangeInputIsInvalid) {
    EXPECT_FALSE(Interval::FromSteps(1792, 3072).IsValid());
    EXPECT_FALSE(Interval::FromSteps(0, 3080).IsValid());
    EXPECT_FALSE(Interval::FromSteps(INT32_MAX, 0).IsValid());
    EXPECT_FALSE(Interval::FromSteps(INT32_MIN, INT32_MIN).IsValid());
    EXPECT_FALSE(Interval(IntervalQuality::Invalid(), IntervalNumber(3)).IsValid());
    EXPECT_FALSE(Interval(IntervalQuality::Major(), IntervalNumber()).IsValid());
    EXPECT_FALSE(Interval(IntervalQuality::Perfect(), IntervalNumber(2)).IsValid());
}

// SPEC-ERR-4: invalid operands propagate.
TEST(InvalidStateTests, InvalidValuesPropagate) {
    const Interval M3(IntervalQuality::Major(), IntervalNumber(3));
    EXPECT_FALSE(Interval::Invalid().Inverted().IsValid());
    EXPECT_FALSE(Interval::Invalid().Simple().IsValid());
    EXPECT_FALSE(Interval::Invalid().Reversed().IsValid());
    EXPECT_FALSE((Interval::Invalid() + M3).IsValid());
    EXPECT_FALSE((M3 + Interval::Invalid()).IsValid());
    EXPECT_FALSE(Interval::Invalid().Number().IsValid());
    EXPECT_FALSE(Interval::Invalid().Quality().IsValid());
    EXPECT_FALSE((Pitch() + M3).IsValid());
    EXPECT_FALSE((Pitch(Letter::C, 4) + Interval::Invalid()).IsValid());
    EXPECT_FALSE((NoteName() + M3).IsValid());
    EXPECT_FALSE((NoteName(Letter::C) - Interval::Invalid()).IsValid());
    EXPECT_FALSE(MCC::IntervalBetween(Pitch(), Pitch(Letter::C, 4)).IsValid());
    EXPECT_FALSE(MCC::IntervalBetween(NoteName(Letter::C), NoteName()).IsValid());
    EXPECT_FALSE(IntervalNumber::Invalid().Simple().IsValid());
    EXPECT_FALSE(IntervalNumber::Invalid().Inverted().IsValid());
    EXPECT_FALSE(IntervalQuality::Invalid().Inverted().IsValid());
}

// SPEC-ERR-5: unrepresentable results are invalid.
TEST(InvalidStateTests, UnrepresentableResultsAreInvalid) {
    const Interval widest = Interval::FromSteps(1791, 3071);
    ASSERT_TRUE(widest.IsValid());
    EXPECT_FALSE((widest + Interval(IntervalQuality::Major(), IntervalNumber(2))).IsValid());
    const Interval A4(IntervalQuality::Augmented(4), IntervalNumber(2));
    EXPECT_FALSE((A4 + Interval(IntervalQuality::Augmented(), IntervalNumber(1))).IsValid());
}

// SPEC-ERR-6: invalid values equal each other; IsEnharmonic is false.
TEST(InvalidStateTests, InvalidValuesCompareEqualOnlyToThemselves) {
    EXPECT_EQ(Interval::FromSteps(1, 7), Interval::FromSteps(3000, 0));
    EXPECT_EQ(IntervalNumber(0), IntervalNumber(5000));
    EXPECT_EQ(IntervalQuality::Augmented(5), IntervalQuality::Diminished(0));
    EXPECT_FALSE(MCC::IsEnharmonic(Interval::Invalid(), Interval::Invalid()));
    EXPECT_FALSE(MCC::IsEnharmonic(Interval::Invalid(), Interval::Unison()));
    for (const Interval interval : MCCTests::AllIntervals(7)) {
        EXPECT_NE(interval, Interval::Invalid());
    }
    EXPECT_LT(IntervalNumber(1792), IntervalNumber::Invalid());
}

// SPEC-ERR-7: queries on invalid values return documented sentinels.
TEST(InvalidStateTests, InvalidQueriesReturnDocumentedSentinels) {
    EXPECT_EQ(Interval::Invalid().DiatonicSteps(), Interval::InvalidSteps);
    EXPECT_EQ(Interval::Invalid().Semitones(), 0);
    EXPECT_EQ(Interval::Invalid().Direction(), IntervalDirection::Unison);
    EXPECT_EQ(IntervalNumber::Invalid().Value(), IntervalNumber::InvalidValue);
    EXPECT_EQ(IntervalQuality::Invalid().Count(), 0);
    EXPECT_EQ(IntervalQuality::Invalid().Kind(), MCC::IntervalQualityKind::Perfect);
}
