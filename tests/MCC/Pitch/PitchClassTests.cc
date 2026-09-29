#include <gtest/gtest.h>

#include "PitchTestSupport.h"

using MCC::PitchClass;

// SPEC-ORD-4: pitch classes are 0-11.
TEST(PitchClassTests, AcceptsZeroToEleven) {
    EXPECT_EQ(PitchClass::Count, 12);
    for (int value = 0; value < 12; ++value) {
        const PitchClass pitchClass(value);
        EXPECT_TRUE(pitchClass.IsValid());
        EXPECT_EQ(pitchClass.Value(), value);
    }
}

// SPEC-ERR-3: construction checks its input instead of reducing it.
TEST(PitchClassTests, RejectsOutOfRangeValues) {
    for (const int value : {-1, 12, 13, 255, -12, 1000}) {
        EXPECT_FALSE(PitchClass(value).IsValid()) << value;
    }
}

// SPEC-ORD-4: transposition reduces modulo 12 into [0, 11].
TEST(PitchClassTests, TransposedWrapsModuloTwelve) {
    for (int from = 0; from < 12; ++from) {
        for (int semitones = -50; semitones <= 50; ++semitones) {
            const int expected = (((from + semitones) % 12) + 12) % 12;
            EXPECT_EQ(PitchClass(from).Transposed(semitones),
                PitchClass(expected));
        }
    }
    EXPECT_EQ(PitchClass(0).Transposed(32767), PitchClass(32767 % 12));
    EXPECT_EQ(PitchClass(0).Transposed(-32767 - 1),
        PitchClass(((-32768 % 12) + 12) % 12));
}

TEST(PitchClassTests, OrdersByValue) {
    for (int value = 0; value < 11; ++value) {
        EXPECT_LT(PitchClass(value), PitchClass(value + 1));
    }
}
