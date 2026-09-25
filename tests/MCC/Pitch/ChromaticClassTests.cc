#include <gtest/gtest.h>

#include "PitchTestSupport.h"

using MCC::ChromaticClass;

// SPEC-ORD-4: chromatic classes are 0-11.
TEST(ChromaticClassTests, AcceptsZeroToEleven) {
    EXPECT_EQ(ChromaticClass::Count, 12);
    for (int value = 0; value < 12; ++value) {
        const ChromaticClass chromaticClass(value);
        EXPECT_TRUE(chromaticClass.IsValid());
        EXPECT_EQ(chromaticClass.Value(), value);
    }
}

// SPEC-ERR-3: construction checks its input instead of reducing it.
TEST(ChromaticClassTests, RejectsOutOfRangeValues) {
    for (const int value : {-1, 12, 13, 255, -12, 1000}) {
        EXPECT_FALSE(ChromaticClass(value).IsValid()) << value;
    }
}

// SPEC-ORD-4: transposition reduces modulo 12 into [0, 11].
TEST(ChromaticClassTests, TransposedWrapsModuloTwelve) {
    for (int from = 0; from < 12; ++from) {
        for (int semitones = -50; semitones <= 50; ++semitones) {
            const int expected = (((from + semitones) % 12) + 12) % 12;
            EXPECT_EQ(ChromaticClass(from).Transposed(semitones),
                ChromaticClass(expected));
        }
    }
    EXPECT_EQ(ChromaticClass(0).Transposed(32767), ChromaticClass(32767 % 12));
    EXPECT_EQ(ChromaticClass(0).Transposed(-32767 - 1),
        ChromaticClass(((-32768 % 12) + 12) % 12));
}

TEST(ChromaticClassTests, OrdersByValue) {
    for (int value = 0; value < 11; ++value) {
        EXPECT_LT(ChromaticClass(value), ChromaticClass(value + 1));
    }
}
