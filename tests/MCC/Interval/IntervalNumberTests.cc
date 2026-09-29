#include <gtest/gtest.h>

#include "IntervalTestSupport.h"

using MCC::IntervalNumber;

// SPEC-INT-2: numbers are 1-based and positive.
TEST(IntervalNumberTests, AcceptsOneToMaximum) {
    EXPECT_EQ(IntervalNumber::Maximum, 1792);
    EXPECT_TRUE(IntervalNumber(1).IsValid());
    EXPECT_TRUE(IntervalNumber(1792).IsValid());
    EXPECT_EQ(IntervalNumber(10).Value(), 10);
    EXPECT_FALSE(IntervalNumber(0).IsValid());
    EXPECT_FALSE(IntervalNumber(-3).IsValid());
    EXPECT_FALSE(IntervalNumber(1793).IsValid());
}

// SPEC-INT-3: 1-8 are simple; larger numbers are compound and reduce by
// removing octaves.
TEST(IntervalNumberTests, SimpleAndCompound) {
    for (int value = 1; value <= 8; ++value) {
        EXPECT_TRUE(IntervalNumber(value).IsSimple());
        EXPECT_FALSE(IntervalNumber(value).IsCompound());
        EXPECT_EQ(IntervalNumber(value).Simple(), IntervalNumber(value));
    }
    EXPECT_EQ(IntervalNumber(9).Simple(), IntervalNumber(2));
    EXPECT_EQ(IntervalNumber(10).Simple(), IntervalNumber(3));
    EXPECT_EQ(IntervalNumber(15).Simple(), IntervalNumber(8));
    EXPECT_EQ(IntervalNumber(16).Simple(), IntervalNumber(2));
    for (int value = 9; value <= 1792; ++value) {
        const IntervalNumber number(value);
        EXPECT_TRUE(number.IsCompound());
        const int simple = number.Simple().Value();
        EXPECT_GE(simple, 2);
        EXPECT_LE(simple, 8);
        EXPECT_EQ((value - simple) % 7, 0) << value;
    }
}

// SPEC-INT-4: unisons, fourths, fifths, octaves and their compounds are
// perfect-type.
TEST(IntervalNumberTests, PerfectTypes) {
    for (const int value : {1, 4, 5, 8, 11, 12, 15, 18, 19, 22}) {
        EXPECT_TRUE(IntervalNumber(value).IsPerfectType()) << value;
    }
    for (const int value : {2, 3, 6, 7, 9, 10, 13, 14}) {
        EXPECT_FALSE(IntervalNumber(value).IsPerfectType()) << value;
    }
}

// SPEC-INT-6: number + inverted number = 9 for simple numbers.
TEST(IntervalNumberTests, InvertedAddsUpToNine) {
    for (int value = 1; value <= 8; ++value) {
        EXPECT_EQ(IntervalNumber(value).Inverted().Value() + value, 9);
    }
    EXPECT_EQ(IntervalNumber(10).Inverted(), IntervalNumber(6));
}
