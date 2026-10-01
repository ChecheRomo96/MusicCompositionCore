#include <gtest/gtest.h>

#include <MCC.h>

#include <type_traits>

using MCC::ScalePattern;

// SPEC-EMB-1/2: patterns are eight trivially copyable bytes, so the same
// representation is stored in the flash catalog.
static_assert(sizeof(ScalePattern) == 8);
static_assert(std::is_trivially_copyable_v<ScalePattern>);
static_assert(std::is_trivially_copyable_v<MCC::Scale>);
static_assert(!std::is_polymorphic_v<MCC::Scale>);

// SPEC-EMB-3: formulas, degrees and spelling are constexpr.
constexpr ScalePattern kMajor = ScalePattern::FromFormula("1 2 3 4 5 6 7");
static_assert(kMajor.IsValid());
static_assert(kMajor.DegreeCount() == 7);
static_assert(kMajor.DegreeInterval(3).Semitones() == 4);
static_assert(MCC::Scale(MCC::NoteName(MCC::Letter::E), kMajor).NoteAt(3) ==
    MCC::NoteName(MCC::Letter::G, MCC::Accidental::Sharp()));

TEST(ScaleLayoutTests, ReportsSizes) {
    EXPECT_EQ(sizeof(ScalePattern), 8U);
    EXPECT_LE(sizeof(MCC::Scale), 12U);
}
