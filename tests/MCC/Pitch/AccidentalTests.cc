#include <gtest/gtest.h>

#include "PitchTestSupport.h"

using MCC::Accidental;

// SPEC-ACC-1: accidentals range from -4 to +4 (9 values).
TEST(AccidentalTests, SupportsMinusFourToPlusFour) {
    EXPECT_EQ(Accidental::Minimum, -4);
    EXPECT_EQ(Accidental::Maximum, 4);
    for (int semitones = -4; semitones <= 4; ++semitones) {
        const Accidental accidental(semitones);
        EXPECT_TRUE(accidental.IsValid()) << semitones;
        EXPECT_EQ(accidental.Semitones(), semitones);
    }
}

// SPEC-ACC-1, SPEC-ERR-3: values outside the range are invalid.
TEST(AccidentalTests, RejectsOutOfRangeValues) {
    for (const int semitones : {-128, -5, 5, 127, 1000, -1000}) {
        EXPECT_FALSE(Accidental(semitones).IsValid()) << semitones;
    }
}

// SPEC-ACC-1, SPEC-ACC-2: named accidentals, natural is a distinct value.
TEST(AccidentalTests, NamedAccidentalsMatchSemitones) {
    EXPECT_EQ(Accidental::QuadrupleFlat(), Accidental(-4));
    EXPECT_EQ(Accidental::TripleFlat(), Accidental(-3));
    EXPECT_EQ(Accidental::DoubleFlat(), Accidental(-2));
    EXPECT_EQ(Accidental::Flat(), Accidental(-1));
    EXPECT_EQ(Accidental::Natural(), Accidental(0));
    EXPECT_EQ(Accidental::Sharp(), Accidental(1));
    EXPECT_EQ(Accidental::DoubleSharp(), Accidental(2));
    EXPECT_EQ(Accidental::TripleSharp(), Accidental(3));
    EXPECT_EQ(Accidental::QuadrupleSharp(), Accidental(4));
    EXPECT_TRUE(Accidental::Natural().IsValid());
    EXPECT_NE(Accidental::Natural(), Accidental::Invalid());
}

// SPEC-ACC-3, SPEC-ERR-5: alteration stays in range or becomes invalid.
TEST(AccidentalTests, AlteredIsExhaustivelyBounded) {
    for (int from = -4; from <= 4; ++from) {
        for (int delta = -20; delta <= 20; ++delta) {
            const Accidental result = Accidental(from).Altered(delta);
            const int expected = from + delta;
            if (expected < -4 || expected > 4) {
                EXPECT_FALSE(result.IsValid()) << from << " + " << delta;
            } else {
                EXPECT_EQ(result, Accidental(expected)) << from << " + " << delta;
            }
        }
    }
    EXPECT_FALSE(Accidental::QuadrupleSharp().Altered(1).IsValid());
    EXPECT_FALSE(Accidental::QuadrupleFlat().Altered(-1).IsValid());
    EXPECT_FALSE(Accidental::Natural().Altered(32767).IsValid());
    EXPECT_FALSE(Accidental::Natural().Altered(-32767 - 1).IsValid());
}

// SPEC-ACC-1: accidentals are ordered by semitones.
TEST(AccidentalTests, OrdersBySemitones) {
    const auto all = MCCTests::AllAccidentals();
    for (size_t i = 0; i + 1 < all.size(); ++i) {
        EXPECT_LT(all[i], all[i + 1]);
        EXPECT_GT(all[i + 1], all[i]);
        EXPECT_LE(all[i], all[i]);
        EXPECT_GE(all[i], all[i]);
    }
}
