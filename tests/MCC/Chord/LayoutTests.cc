#include <gtest/gtest.h>

#include <MCC.h>

#include <type_traits>

using MCC::ChordPattern;

// SPEC-EMB-1/2: patterns are eight trivially copyable bytes, the same
// representation as the flash catalog.
static_assert(sizeof(ChordPattern) == 8);
static_assert(std::is_trivially_copyable_v<ChordPattern>);
static_assert(std::is_trivially_copyable_v<MCC::Chord>);
static_assert(std::is_trivially_copyable_v<MCC::Chords::ScaleChord>);

// SPEC-EMB-3: formulas and spelling are constexpr.
constexpr ChordPattern kNinth = ChordPattern::FromFormula("1 3 5 b7 9");
static_assert(kNinth.IsValid());
static_assert(kNinth.ToneCount() == 5);
static_assert(kNinth.ToneInterval(5).DiatonicSteps() == 8);
static_assert(kNinth.ToneInterval(5).Semitones() == 14);
static_assert(MCC::Chord(MCC::NoteName(MCC::Letter::C), kNinth).ToneAt(5) ==
    MCC::NoteName(MCC::Letter::D));

TEST(ChordLayoutTests, ReportsSizes) {
    EXPECT_EQ(sizeof(ChordPattern), 8U);
    EXPECT_LE(sizeof(MCC::Chord), 12U);
}
