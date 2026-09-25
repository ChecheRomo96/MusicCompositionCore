#include <gtest/gtest.h>

#include "PitchTestSupport.h"

#include <cstdint>

using MCC::Accidental;
using MCC::ChromaticClass;
using MCC::Letter;
using MCC::PitchClass;

// SPEC-ERR-1: Letter is a closed enumeration without an invalid state.
TEST(InvalidStateTests, LetterIsAlwaysValid) {
    for (const Letter letter : MCCTests::AllLetters) {
        EXPECT_TRUE(PitchClass(letter).IsValid());
    }
}

// SPEC-ERR-1, SPEC-ERR-2: default construction is the invalid value.
TEST(InvalidStateTests, DefaultConstructionIsInvalid) {
    EXPECT_FALSE(Accidental().IsValid());
    EXPECT_FALSE(ChromaticClass().IsValid());
    EXPECT_FALSE(PitchClass().IsValid());
    EXPECT_EQ(Accidental(), Accidental::Invalid());
    EXPECT_EQ(ChromaticClass(), ChromaticClass::Invalid());
    EXPECT_EQ(PitchClass(), PitchClass::Invalid());
}

// SPEC-ERR-3: out-of-range checked input produces the invalid value.
TEST(InvalidStateTests, OutOfRangeInputIsInvalid) {
    EXPECT_EQ(Accidental(5), Accidental::Invalid());
    EXPECT_EQ(Accidental(-5), Accidental::Invalid());
    EXPECT_EQ(ChromaticClass(12), ChromaticClass::Invalid());
    EXPECT_EQ(ChromaticClass(-1), ChromaticClass::Invalid());
    EXPECT_EQ(PitchClass(Letter::C, Accidental(5)), PitchClass::Invalid());
    EXPECT_EQ(PitchClass(static_cast<Letter>(7)), PitchClass::Invalid());
    EXPECT_EQ(PitchClass(static_cast<Letter>(0xFF), Accidental::Sharp()),
        PitchClass::Invalid());
}

// SPEC-ERR-4: invalid operands propagate through every operation.
TEST(InvalidStateTests, InvalidValuesPropagate) {
    EXPECT_FALSE(Accidental::Invalid().Altered(0).IsValid());
    EXPECT_FALSE(ChromaticClass::Invalid().Transposed(0).IsValid());
    EXPECT_FALSE(PitchClass::Invalid().ChromaticClass().IsValid());
    EXPECT_FALSE(PitchClass::Invalid().MovedDiatonically(0).IsValid());
    EXPECT_FALSE(PitchClass::Invalid().MovedDiatonically(3).IsValid());
    EXPECT_FALSE(PitchClass::Invalid().Altered(0).IsValid());
    EXPECT_FALSE(PitchClass::Invalid().Accidental().IsValid());
}

// SPEC-ERR-5: unrepresentable results are invalid.
TEST(InvalidStateTests, UnrepresentableResultsAreInvalid) {
    EXPECT_FALSE(Accidental::QuadrupleSharp().Altered(1).IsValid());
    EXPECT_FALSE(PitchClass(Letter::G, Accidental::QuadrupleFlat())
        .Altered(-1).IsValid());
}

// SPEC-ERR-6: invalid values are equal to each other and unequal to every
// valid value; IsEnharmonic() with an invalid operand is false.
TEST(InvalidStateTests, InvalidValuesCompareEqualOnlyToThemselves) {
    const PitchClass invalidA = PitchClass();
    const PitchClass invalidB = PitchClass(Letter::A, Accidental(9));
    const PitchClass invalidC = PitchClass(Letter::B, Accidental(4)).Altered(1);
    EXPECT_EQ(invalidA, invalidB);
    EXPECT_EQ(invalidB, invalidC);
    EXPECT_EQ(Accidental(9), Accidental(-9));
    EXPECT_EQ(ChromaticClass(12), ChromaticClass(-3));

    for (const PitchClass valid : MCCTests::AllPitchClasses()) {
        EXPECT_NE(valid, invalidA);
        EXPECT_FALSE(MCC::IsEnharmonic(valid, invalidA));
        EXPECT_FALSE(MCC::IsEnharmonic(invalidA, valid));
        EXPECT_LT(valid, invalidA);  // Invalid sorts last.
    }
    for (const Accidental valid : MCCTests::AllAccidentals()) {
        EXPECT_NE(valid, Accidental::Invalid());
        EXPECT_LT(valid, Accidental::Invalid());
    }
    for (int value = 0; value < 12; ++value) {
        EXPECT_NE(ChromaticClass(value), ChromaticClass::Invalid());
        EXPECT_LT(ChromaticClass(value), ChromaticClass::Invalid());
    }
    EXPECT_FALSE(MCC::IsEnharmonic(invalidA, invalidB));
}

// SPEC-ERR-7: numeric queries on invalid values return documented sentinels.
TEST(InvalidStateTests, InvalidQueriesReturnDocumentedSentinels) {
    EXPECT_EQ(Accidental::Invalid().Semitones(), Accidental::InvalidValue);
    EXPECT_EQ(ChromaticClass::Invalid().Value(), ChromaticClass::InvalidValue);
    EXPECT_EQ(PitchClass::Invalid().Letter(), Letter::C);
    EXPECT_EQ(PitchClass::Invalid().Accidental(), Accidental::Invalid());
}
