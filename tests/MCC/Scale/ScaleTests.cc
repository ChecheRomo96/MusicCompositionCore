#include <gtest/gtest.h>

#include <MCC.h>

using MCC::Accidental;
using MCC::Letter;
using MCC::NoteName;
using MCC::Pitch;
using MCC::PitchClass;
using MCC::Scale;
using MCC::ScalePattern;

namespace {

const ScalePattern Major = ScalePattern::FromFormula("1 2 3 4 5 6 7");

}

TEST(ScaleTests, SpellsDegreesFromTheRoot) {
    const Scale eMajor(NoteName(Letter::E), Major);
    const NoteName expected[] = {
        NoteName(Letter::E), NoteName(Letter::F, Accidental::Sharp()),
        NoteName(Letter::G, Accidental::Sharp()), NoteName(Letter::A),
        NoteName(Letter::B), NoteName(Letter::C, Accidental::Sharp()),
        NoteName(Letter::D, Accidental::Sharp())};
    ASSERT_EQ(eMajor.DegreeCount(), 7);
    for (int degree = 1; degree <= 7; ++degree) {
        EXPECT_EQ(eMajor.NoteAt(degree), expected[degree - 1]) << degree;
    }
    EXPECT_FALSE(eMajor.NoteAt(8).IsValid());
}

TEST(ScaleTests, PitchesCrossTheOctave) {
    const Scale aMajor(NoteName(Letter::A), Major);
    EXPECT_EQ(aMajor.PitchAt(1, 4), Pitch(Letter::A, 4));
    EXPECT_EQ(aMajor.PitchAt(3, 4), Pitch(Letter::C, Accidental::Sharp(), 5));
    EXPECT_FALSE(aMajor.PitchAt(9, 4).IsValid());
}

TEST(ScaleTests, MembershipIsWrittenUnlessEnharmonicIsRequested) {
    const Scale eMajor(NoteName(Letter::E), Major);
    const NoteName gSharp(Letter::G, Accidental::Sharp());
    const NoteName aFlat(Letter::A, Accidental::Flat());
    EXPECT_EQ(eMajor.DegreeOf(gSharp), 3);
    EXPECT_TRUE(eMajor.Contains(gSharp));
    EXPECT_FALSE(eMajor.Contains(aFlat));
    EXPECT_TRUE(eMajor.ContainsPitchClass(aFlat.PitchClass()));
    EXPECT_FALSE(eMajor.ContainsPitchClass(PitchClass(0)));
    EXPECT_EQ(eMajor.DegreeOf(NoteName::Invalid()), 0);
}

TEST(ScaleTests, UnspellableDegreesAreInvalid) {
    // SPEC-SCL-3: B#### has no room for the sharpened degrees above it.
    const Scale extreme(NoteName(Letter::B, Accidental(4)), Major);
    ASSERT_TRUE(extreme.IsValid());
    EXPECT_TRUE(extreme.NoteAt(1).IsValid());
    EXPECT_FALSE(extreme.NoteAt(2).IsValid());
}

TEST(ScaleTests, InvalidInputsProduceTheInvalidScale) {
    EXPECT_FALSE(Scale().IsValid());
    EXPECT_EQ(Scale(NoteName::Invalid(), Major), Scale::Invalid());
    EXPECT_EQ(Scale(NoteName(Letter::C), ScalePattern::Invalid()), Scale::Invalid());
    EXPECT_FALSE(Scale::Invalid().NoteAt(1).IsValid());
    EXPECT_FALSE(Scale::Invalid().ContainsPitchClass(PitchClass(0)));
    EXPECT_EQ(Scale::Invalid().DegreeCount(), 0);
}
