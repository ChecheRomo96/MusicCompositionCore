#include <gtest/gtest.h>

#include <MCC.h>

#include <vector>

namespace Chords = MCC::Chords;
namespace Scales = MCC::Scales;
using MCC::Letter;
using MCC::NoteName;

namespace {

std::vector<Chords::ScaleChord> Pool(const MCC::Scale& scale) {
    const size_t count = Chords::FromScale(scale, nullptr, 0);
    std::vector<Chords::ScaleChord> chords(count);
    EXPECT_EQ(Chords::FromScale(scale, chords.data(), chords.size()), count);
    return chords;
}

// The single chord of `candidates` found on `degree`, or Id::Invalid when
// none or several are.
Chords::Id OnlyOf(const std::vector<Chords::ScaleChord>& pool, uint8_t degree,
                  std::initializer_list<Chords::Id> candidates) {
    Chords::Id found = Chords::Id::Invalid;
    int matches = 0;
    for (const Chords::ScaleChord& chord : pool) {
        for (Chords::Id candidate : candidates) {
            if (chord.degree == degree && chord.id == candidate) {
                found = candidate;
                ++matches;
            }
        }
    }
    return matches == 1 ? found : Chords::Id::Invalid;
}

}

TEST(FromScaleTests, MajorScaleYieldsTheDiatonicTriadsAndSevenths) {
    const auto pool = Pool(Scales::Make(NoteName(Letter::C), Scales::Id::Major));
    using Id = Chords::Id;
    const Id triads[] = {Id::Major, Id::Minor, Id::Minor, Id::Major, Id::Major, Id::Minor, Id::Diminished};
    const Id sevenths[] = {Id::MajorSeventh, Id::MinorSeventh, Id::MinorSeventh, Id::MajorSeventh,
                           Id::DominantSeventh, Id::MinorSeventh, Id::HalfDiminishedSeventh};
    for (uint8_t degree = 1; degree <= 7; ++degree) {
        EXPECT_EQ(OnlyOf(pool, degree, {Id::Major, Id::Minor, Id::Augmented, Id::Diminished}),
                  triads[degree - 1]) << int(degree);
        EXPECT_EQ(OnlyOf(pool, degree, {Id::MajorSeventh, Id::MinorSeventh, Id::DominantSeventh,
                                        Id::HalfDiminishedSeventh, Id::DiminishedSeventh,
                                        Id::MinorMajorSeventh, Id::AugmentedSeventh}),
                  sevenths[degree - 1]) << int(degree);
    }
}

TEST(FromScaleTests, HarmonicMinorYieldsAugmentedAndDiminishedSevenths) {
    const auto pool = Pool(Scales::Make(NoteName(Letter::A), Scales::Id::HarmonicMinor));
    using Id = Chords::Id;
    EXPECT_EQ(OnlyOf(pool, 1, {Id::MinorMajorSeventh}), Id::MinorMajorSeventh);
    EXPECT_EQ(OnlyOf(pool, 3, {Id::Augmented}), Id::Augmented);
    EXPECT_EQ(OnlyOf(pool, 5, {Id::DominantSeventh}), Id::DominantSeventh);
    EXPECT_EQ(OnlyOf(pool, 7, {Id::DiminishedSeventh}), Id::DiminishedSeventh);
}

TEST(FromScaleTests, ResultsAreOrderedAndEverySpelledToneIsInTheScale) {
    const MCC::Scale scale = Scales::Make(NoteName(Letter::E), Scales::Id::Dorian);
    const auto pool = Pool(scale);
    ASSERT_FALSE(pool.empty());
    for (std::size_t i = 0; i < pool.size(); ++i) {
        if (i > 0) {
            EXPECT_TRUE(pool[i - 1].degree < pool[i].degree ||
                        (pool[i - 1].degree == pool[i].degree && pool[i - 1].id < pool[i].id));
        }
        const MCC::Chord chord = Chords::Make(scale.NoteAt(pool[i].degree), pool[i].id);
        for (int tone = 1; tone <= chord.ToneCount(); ++tone) {
            EXPECT_TRUE(scale.Contains(chord.ToneAt(tone)));
        }
    }
}

TEST(FromScaleTests, ReportsTheNeededSizeWhenTheBufferIsSmall) {
    const MCC::Scale scale = Scales::Make(NoteName(Letter::C), Scales::Id::Major);
    const size_t total = Chords::FromScale(scale, nullptr, 0);
    Chords::ScaleChord two[2];
    EXPECT_EQ(Chords::FromScale(scale, two, 2), total);
    EXPECT_EQ(two[0].degree, 1);
    EXPECT_EQ(two[0].id, Chords::Id::Major);
    EXPECT_EQ(Chords::FromScale(MCC::Scale::Invalid(), two, 2), 0U);
}
