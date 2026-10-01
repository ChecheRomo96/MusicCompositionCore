#include <gtest/gtest.h>

#include <MCC.h>

using MCC::Accidental;
using MCC::Chord;
using MCC::ChordPattern;
using MCC::Letter;
using MCC::NoteName;
using MCC::Pitch;
using MCC::PitchClass;

namespace {

const ChordPattern Major = ChordPattern::FromFormula("1 3 5");
const ChordPattern DominantNinth = ChordPattern::FromFormula("1 3 5 b7 9");

}

TEST(ChordTests, SpellsTonesFromTheRoot) {
    const Chord eNinth(NoteName(Letter::E), DominantNinth);
    const NoteName expected[] = {
        NoteName(Letter::E), NoteName(Letter::G, Accidental::Sharp()),
        NoteName(Letter::B), NoteName(Letter::D), NoteName(Letter::F, Accidental::Sharp())};
    ASSERT_EQ(eNinth.ToneCount(), 5);
    for (int tone = 1; tone <= 5; ++tone) {
        EXPECT_EQ(eNinth.ToneAt(tone), expected[tone - 1]) << tone;
    }
    EXPECT_EQ(eNinth.PitchAt(5, 3), Pitch(Letter::F, Accidental::Sharp(), 4));
}

TEST(ChordTests, MembershipIsWrittenUnlessEnharmonicIsRequested) {
    const Chord eMajor(NoteName(Letter::E), Major);
    const NoteName aFlat(Letter::A, Accidental::Flat());
    EXPECT_TRUE(eMajor.Contains(NoteName(Letter::G, Accidental::Sharp())));
    EXPECT_FALSE(eMajor.Contains(aFlat));
    EXPECT_TRUE(eMajor.ContainsPitchClass(aFlat.PitchClass()));
    EXPECT_FALSE(eMajor.ContainsPitchClass(PitchClass(0)));
    // The ninth of C9 is D (pitch class 2) even though it lies above the octave.
    EXPECT_TRUE(Chord(NoteName(Letter::C), DominantNinth).ContainsPitchClass(PitchClass(2)));
}

TEST(ChordTests, VoicingsPlaceEachInversionInClosePosition) {
    const Chord cMajor(NoteName(Letter::C), Major);
    Pitch pitches[3];
    ASSERT_EQ(cMajor.Voicing(0, 4, pitches, 3), 3U);
    EXPECT_EQ(pitches[0], Pitch(Letter::C, 4));
    EXPECT_EQ(pitches[1], Pitch(Letter::E, 4));
    EXPECT_EQ(pitches[2], Pitch(Letter::G, 4));

    ASSERT_EQ(cMajor.Voicing(1, 4, pitches, 3), 3U);
    EXPECT_EQ(pitches[0], Pitch(Letter::E, 4));
    EXPECT_EQ(pitches[1], Pitch(Letter::G, 4));
    EXPECT_EQ(pitches[2], Pitch(Letter::C, 5));

    ASSERT_EQ(cMajor.Voicing(2, 4, pitches, 3), 3U);
    EXPECT_EQ(pitches[0], Pitch(Letter::G, 4));
    EXPECT_EQ(pitches[1], Pitch(Letter::C, 5));
    EXPECT_EQ(pitches[2], Pitch(Letter::E, 5));
}

TEST(ChordTests, VoicingsOfExtendedChordsStayAscending) {
    const Chord cNinth(NoteName(Letter::C), DominantNinth);
    for (int inversion = 0; inversion < 5; ++inversion) {
        Pitch pitches[5];
        ASSERT_EQ(cNinth.Voicing(inversion, 4, pitches, 5), 5U);
        EXPECT_EQ(pitches[0].NoteName(), cNinth.ToneAt(inversion + 1));
        for (int i = 1; i < 5; ++i) {
            EXPECT_TRUE(MCC::IsLowerThan(pitches[i - 1], pitches[i])) << inversion << ':' << i;
        }
    }
}

TEST(ChordTests, VoicingReportsSizeAndRejectsBadInversions) {
    const Chord cMajor(NoteName(Letter::C), Major);
    Pitch one[1];
    EXPECT_EQ(cMajor.Voicing(0, 4, one, 1), 3U);
    EXPECT_EQ(one[0], Pitch(Letter::C, 4));
    EXPECT_EQ(cMajor.Voicing(0, 4, nullptr, 0), 3U);
    EXPECT_EQ(cMajor.Voicing(3, 4, one, 1), 0U);
    EXPECT_EQ(cMajor.Voicing(-1, 4, one, 1), 0U);
    EXPECT_EQ(Chord::Invalid().Voicing(0, 4, one, 1), 0U);
}

TEST(ChordTests, InvalidInputsProduceTheInvalidChord) {
    EXPECT_FALSE(Chord().IsValid());
    EXPECT_EQ(Chord(NoteName::Invalid(), Major), Chord::Invalid());
    EXPECT_EQ(Chord(NoteName(Letter::C), ChordPattern::Invalid()), Chord::Invalid());
    EXPECT_FALSE(Chord::Invalid().ToneAt(1).IsValid());
    EXPECT_FALSE(Chord::Invalid().ContainsPitchClass(PitchClass(0)));
}
