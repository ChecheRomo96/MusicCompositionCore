#include <gtest/gtest.h>

#include "PitchTestSupport.h"

#include <cstdint>

using MCC::Accidental;
using MCC::PitchClass;
using MCC::Letter;
using MCC::NoteName;

// SPEC-ERR-1: Letter is a closed enumeration without an invalid state.
TEST(InvalidStateTests, LetterIsAlwaysValid) {
    for (const Letter letter : MCCTests::AllLetters) {
        EXPECT_TRUE(NoteName(letter).IsValid());
    }
}

// SPEC-ERR-1, SPEC-ERR-2: default construction is the invalid value.
TEST(InvalidStateTests, DefaultConstructionIsInvalid) {
    EXPECT_FALSE(Accidental().IsValid());
    EXPECT_FALSE(PitchClass().IsValid());
    EXPECT_FALSE(NoteName().IsValid());
    EXPECT_EQ(Accidental(), Accidental::Invalid());
    EXPECT_EQ(PitchClass(), PitchClass::Invalid());
    EXPECT_EQ(NoteName(), NoteName::Invalid());
}

// SPEC-ERR-3: out-of-range checked input produces the invalid value.
TEST(InvalidStateTests, OutOfRangeInputIsInvalid) {
    EXPECT_EQ(Accidental(5), Accidental::Invalid());
    EXPECT_EQ(Accidental(-5), Accidental::Invalid());
    EXPECT_EQ(PitchClass(12), PitchClass::Invalid());
    EXPECT_EQ(PitchClass(-1), PitchClass::Invalid());
    EXPECT_EQ(NoteName(Letter::C, Accidental(5)), NoteName::Invalid());
    EXPECT_EQ(NoteName(static_cast<Letter>(7)), NoteName::Invalid());
    EXPECT_EQ(NoteName(static_cast<Letter>(0xFF), Accidental::Sharp()),
        NoteName::Invalid());
}

// SPEC-ERR-4: invalid operands propagate through every operation.
TEST(InvalidStateTests, InvalidValuesPropagate) {
    EXPECT_FALSE(Accidental::Invalid().Altered(0).IsValid());
    EXPECT_FALSE(PitchClass::Invalid().Transposed(0).IsValid());
    EXPECT_FALSE(NoteName::Invalid().PitchClass().IsValid());
    EXPECT_FALSE(NoteName::Invalid().MovedDiatonically(0).IsValid());
    EXPECT_FALSE(NoteName::Invalid().MovedDiatonically(3).IsValid());
    EXPECT_FALSE(NoteName::Invalid().Altered(0).IsValid());
    EXPECT_FALSE(NoteName::Invalid().Accidental().IsValid());
}

// SPEC-ERR-5: unrepresentable results are invalid.
TEST(InvalidStateTests, UnrepresentableResultsAreInvalid) {
    EXPECT_FALSE(Accidental::QuadrupleSharp().Altered(1).IsValid());
    EXPECT_FALSE(NoteName(Letter::G, Accidental::QuadrupleFlat())
        .Altered(-1).IsValid());
}

// SPEC-ERR-6: invalid values are equal to each other and unequal to every
// valid value; IsEnharmonic() with an invalid operand is false.
TEST(InvalidStateTests, InvalidValuesCompareEqualOnlyToThemselves) {
    const NoteName invalidA = NoteName();
    const NoteName invalidB = NoteName(Letter::A, Accidental(9));
    const NoteName invalidC = NoteName(Letter::B, Accidental(4)).Altered(1);
    EXPECT_EQ(invalidA, invalidB);
    EXPECT_EQ(invalidB, invalidC);
    EXPECT_EQ(Accidental(9), Accidental(-9));
    EXPECT_EQ(PitchClass(12), PitchClass(-3));

    for (const NoteName valid : MCCTests::AllNoteNames()) {
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
        EXPECT_NE(PitchClass(value), PitchClass::Invalid());
        EXPECT_LT(PitchClass(value), PitchClass::Invalid());
    }
    EXPECT_FALSE(MCC::IsEnharmonic(invalidA, invalidB));
}

// SPEC-ERR-7: numeric queries on invalid values return documented sentinels.
TEST(InvalidStateTests, InvalidQueriesReturnDocumentedSentinels) {
    EXPECT_EQ(Accidental::Invalid().Semitones(), Accidental::InvalidValue);
    EXPECT_EQ(PitchClass::Invalid().Value(), PitchClass::InvalidValue);
    EXPECT_EQ(NoteName::Invalid().Letter(), Letter::C);
    EXPECT_EQ(NoteName::Invalid().Accidental(), Accidental::Invalid());
}

// SPEC-ERR-1..3: ChromaticIndex and Pitch have one invalid value, produced by
// default construction and out-of-range input.
TEST(InvalidStateTests, PitchAndIndexInvalidValues) {
    using MCC::ChromaticIndex;
    using MCC::Pitch;
    EXPECT_FALSE(ChromaticIndex().IsValid());
    EXPECT_FALSE(Pitch().IsValid());
    EXPECT_EQ(ChromaticIndex(), ChromaticIndex::Invalid());
    EXPECT_EQ(Pitch(), Pitch::Invalid());
    EXPECT_EQ(ChromaticIndex(1552), ChromaticIndex::Invalid());
    EXPECT_EQ(Pitch(Letter::C, 128), Pitch::Invalid());
    EXPECT_EQ(Pitch(NoteName(), 4), Pitch::Invalid());
    EXPECT_EQ(Pitch(Letter::C, Accidental(5), 4), Pitch::Invalid());
}

// SPEC-ERR-4: invalid pitches propagate through every operation.
TEST(InvalidStateTests, InvalidPitchesPropagate) {
    using MCC::Pitch;
    EXPECT_FALSE(Pitch::Invalid().ChromaticIndex().IsValid());
    EXPECT_FALSE(Pitch::Invalid().PitchClass().IsValid());
    EXPECT_FALSE(Pitch::Invalid().NoteName().IsValid());
    EXPECT_FALSE(Pitch::Invalid().MovedDiatonically(0).IsValid());
    EXPECT_FALSE(Pitch::Invalid().MovedByOctaves(0).IsValid());
    EXPECT_FALSE(Pitch::Invalid().Altered(0).IsValid());
    EXPECT_FALSE(MCC::ChromaticIndex::Invalid().Transposed(0).IsValid());
    EXPECT_FALSE(MCC::ChromaticIndex::Invalid().PitchClass().IsValid());
}

// SPEC-ERR-6: invalid pitches equal each other, differ from valid ones, sort
// last in both orders, and are never enharmonic.
TEST(InvalidStateTests, InvalidPitchesCompareEqualOnlyToThemselves) {
    using MCC::Pitch;
    const Pitch invalidA = Pitch();
    const Pitch invalidB = Pitch(Letter::B, 127).MovedDiatonically(1);
    const Pitch invalidC = Pitch(Letter::C, Accidental::QuadrupleFlat(), 0).Altered(-1);
    EXPECT_EQ(invalidA, invalidB);
    EXPECT_EQ(invalidB, invalidC);
    EXPECT_FALSE(MCC::IsEnharmonic(invalidA, invalidB));
    EXPECT_FALSE(invalidA < invalidB);
    EXPECT_FALSE(MCC::IsLowerThan(invalidA, invalidB));
    MCCTests::ForEachPitch([&](Pitch valid) {
        EXPECT_NE(valid, invalidA);
        EXPECT_LT(valid, invalidA);
        EXPECT_FALSE(invalidA < valid);
        EXPECT_TRUE(MCC::IsLowerThan(valid, invalidA));
        EXPECT_FALSE(MCC::IsLowerThan(invalidA, valid));
        EXPECT_FALSE(MCC::IsEnharmonic(valid, invalidA));
    });
    EXPECT_EQ(MCC::ChromaticIndex(-2000), MCC::ChromaticIndex(2000));
    EXPECT_LT(MCC::ChromaticIndex(1551), MCC::ChromaticIndex::Invalid());
}

// SPEC-ERR-7: numeric queries on invalid values return documented sentinels.
TEST(InvalidStateTests, InvalidPitchQueriesReturnDocumentedSentinels) {
    using MCC::Pitch;
    EXPECT_EQ(MCC::ChromaticIndex::Invalid().Value(),
        MCC::ChromaticIndex::InvalidValue);
    EXPECT_EQ(Pitch::Invalid().DiatonicIndex(), Pitch::InvalidDiatonicIndex);
    EXPECT_EQ(Pitch::Invalid().Octave(), 0);
    EXPECT_EQ(Pitch::Invalid().Letter(), Letter::C);
    EXPECT_FALSE(Pitch::Invalid().Accidental().IsValid());
}
