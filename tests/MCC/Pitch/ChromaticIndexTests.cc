#include <gtest/gtest.h>

#include "PitchTestSupport.h"

using MCC::PitchClass;
using MCC::ChromaticIndex;

// SPEC-CHR-1: origin C-1 = 0, so C0 = 12, C4 = 60 and A4 = 69.
TEST(ChromaticIndexTests, UsesScientificOrigin) {
    EXPECT_EQ(ChromaticIndex(0).Value(), 0);
    EXPECT_EQ(MCC::Pitch(MCC::Letter::C, -1).ChromaticIndex(), ChromaticIndex(0));
    EXPECT_EQ(MCC::Pitch(MCC::Letter::C, 0).ChromaticIndex(), ChromaticIndex(12));
    EXPECT_EQ(MCC::Pitch(MCC::Letter::C, 4).ChromaticIndex(), ChromaticIndex(60));
    EXPECT_EQ(MCC::Pitch(MCC::Letter::A, 4).ChromaticIndex(), ChromaticIndex(69));
}

// SPEC-CHR-2: the valid range is exactly [-1528, 1551].
TEST(ChromaticIndexTests, CoversTheWritablePitchRange) {
    EXPECT_EQ(ChromaticIndex::Minimum, -1528);
    EXPECT_EQ(ChromaticIndex::Maximum, 1551);
    for (int value = -1528; value <= 1551; ++value) {
        EXPECT_TRUE(ChromaticIndex(value).IsValid()) << value;
        EXPECT_EQ(ChromaticIndex(value).Value(), value);
    }
    EXPECT_FALSE(ChromaticIndex(-1529).IsValid());
    EXPECT_FALSE(ChromaticIndex(1552).IsValid());
}

// SPEC-CHR-3: indices are not limited to [0, 127].
TEST(ChromaticIndexTests, IsNotLimitedToAProtocolRange) {
    EXPECT_TRUE(ChromaticIndex(-1).IsValid());
    EXPECT_TRUE(ChromaticIndex(128).IsValid());
    EXPECT_EQ(MCC::Pitch(MCC::Letter::B, -2).ChromaticIndex(), ChromaticIndex(-1));
    EXPECT_EQ(MCC::Pitch(MCC::Letter::G, MCC::Accidental::Sharp(), 9)
        .ChromaticIndex(), ChromaticIndex(128));
}

// SPEC-ORD-4: the pitch class of an index is its value mod 12.
TEST(ChromaticIndexTests, PitchClassIsFlooredModulo) {
    for (int value = -1528; value <= 1551; ++value) {
        EXPECT_EQ(ChromaticIndex(value).PitchClass(),
            PitchClass(((value % 12) + 12) % 12)) << value;
    }
}

// SPEC-ERR-5: transposition outside the range is invalid.
TEST(ChromaticIndexTests, TransposedIsBounded) {
    EXPECT_EQ(ChromaticIndex(60).Transposed(12), ChromaticIndex(72));
    EXPECT_EQ(ChromaticIndex(60).Transposed(-72), ChromaticIndex(-12));
    EXPECT_EQ(ChromaticIndex(1551).Transposed(-3079), ChromaticIndex(-1528));
    EXPECT_FALSE(ChromaticIndex(1551).Transposed(1).IsValid());
    EXPECT_FALSE(ChromaticIndex(-1528).Transposed(-1).IsValid());
    EXPECT_FALSE(ChromaticIndex(0).Transposed(INT32_MAX).IsValid());
    EXPECT_FALSE(ChromaticIndex(0).Transposed(INT32_MIN).IsValid());
}

TEST(ChromaticIndexTests, OrdersByValue) {
    EXPECT_LT(ChromaticIndex(-1528), ChromaticIndex(0));
    EXPECT_LT(ChromaticIndex(59), ChromaticIndex(60));
    EXPECT_GE(ChromaticIndex(60), ChromaticIndex(60));
}
