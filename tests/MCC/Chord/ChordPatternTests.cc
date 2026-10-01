#include <gtest/gtest.h>

#include <MCC.h>

using MCC::ChordPattern;

TEST(ChordPatternTests, FormulaDefinesCompoundTones) {
    const ChordPattern thirteenth = ChordPattern::FromFormula("1 b3 5 b7 9 11 13");
    ASSERT_TRUE(thirteenth.IsValid());
    ASSERT_EQ(thirteenth.ToneCount(), 7);
    const int steps[] = {0, 2, 4, 6, 8, 10, 12};
    const int semitones[] = {0, 3, 7, 10, 14, 17, 21};
    for (int tone = 1; tone <= 7; ++tone) {
        EXPECT_EQ(thirteenth.ToneInterval(tone).DiatonicSteps(), steps[tone - 1]);
        EXPECT_EQ(thirteenth.ToneInterval(tone).Semitones(), semitones[tone - 1]);
    }
    EXPECT_FALSE(thirteenth.ToneInterval(0).IsValid());
    EXPECT_FALSE(thirteenth.ToneInterval(8).IsValid());
}

TEST(ChordPatternTests, PitchClassMaskReducesExtensions) {
    const ChordPattern ninth = ChordPattern::FromFormula("1 3 5 b7 9");
    // Semitones 0, 2 (the ninth), 4, 7 and 10.
    EXPECT_EQ(ninth.PitchClassMask(), (1u << 0) | (1u << 2) | (1u << 4) | (1u << 7) | (1u << 10));
    EXPECT_EQ(ChordPattern::Invalid().PitchClassMask(), 0u);
}

TEST(ChordPatternTests, RejectsMalformedFormulas) {
    const char* const invalid[] = {
        nullptr, "", "  ", "3 5", "b1 3", "1 14", "1 0", "1 3x", "1 5 3",
        "1 3 3", "1 3 5 7 9 11 13 #13", "1 bbbbb3", "1 b2 #1", "1 1", "1 #13 b14",
    };
    for (const char* formula : invalid) {
        EXPECT_FALSE(ChordPattern::FromFormula(formula).IsValid())
            << (formula == nullptr ? "null" : formula);
    }
}

TEST(ChordPatternTests, EqualityIncludesSpelling) {
    EXPECT_NE(ChordPattern::FromFormula("1 3 #5"), ChordPattern::FromFormula("1 3 b6"));
    EXPECT_EQ(ChordPattern::FromFormula("1 3 5"), ChordPattern::FromFormula(" 1  3 5 "));
    EXPECT_EQ(ChordPattern(), ChordPattern::Invalid());
}
