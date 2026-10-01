#include <gtest/gtest.h>

#include <MCC.h>

using MCC::ScalePattern;

TEST(ScalePatternTests, FormulaDefinesStepsAndSemitones) {
    const ScalePattern blues = ScalePattern::FromFormula("1 b3 4 b5 5 b7");
    ASSERT_TRUE(blues.IsValid());
    ASSERT_EQ(blues.DegreeCount(), 6);
    const int steps[] = {0, 2, 3, 4, 4, 6};
    const int semitones[] = {0, 3, 5, 6, 7, 10};
    for (int degree = 1; degree <= 6; ++degree) {
        EXPECT_EQ(blues.DegreeInterval(degree).DiatonicSteps(), steps[degree - 1]);
        EXPECT_EQ(blues.DegreeInterval(degree).Semitones(), semitones[degree - 1]);
    }
    EXPECT_FALSE(blues.DegreeInterval(0).IsValid());
    EXPECT_FALSE(blues.DegreeInterval(7).IsValid());
}

TEST(ScalePatternTests, AcceptsTwelveDegreesAndExtraSpaces) {
    const ScalePattern chromatic =
        ScalePattern::FromFormula("  1 #1 2 #2 3 4 #4 5 #5 6 #6 7 ");
    ASSERT_TRUE(chromatic.IsValid());
    EXPECT_EQ(chromatic.DegreeCount(), 12);
    for (int k = 0; k < 12; ++k) {
        EXPECT_TRUE(chromatic.ContainsSemitone(k));
    }
}

TEST(ScalePatternTests, RejectsMalformedFormulas) {
    const char* const invalid[] = {
        nullptr, "", "   ", "2 3 4", "b1 2", "1 8", "1 0", "1 2x", "1 3 2",
        "1 2 2", "1 #7", "1 b2 #1", "1 x2", "1 1",
    };
    for (const char* formula : invalid) {
        EXPECT_FALSE(ScalePattern::FromFormula(formula).IsValid())
            << (formula == nullptr ? "null" : formula);
    }
}

TEST(ScalePatternTests, ContainsSemitoneReducesModuloTwelve) {
    const ScalePattern major = ScalePattern::FromFormula("1 2 3 4 5 6 7");
    EXPECT_TRUE(major.ContainsSemitone(4));
    EXPECT_TRUE(major.ContainsSemitone(16));
    EXPECT_TRUE(major.ContainsSemitone(-1));
    EXPECT_FALSE(major.ContainsSemitone(-2));
    EXPECT_FALSE(ScalePattern::Invalid().ContainsSemitone(0));
}

TEST(ScalePatternTests, EqualityIncludesSpelling) {
    const ScalePattern sharps = ScalePattern::FromFormula("1 #4 5");
    const ScalePattern flats = ScalePattern::FromFormula("1 b5 5");
    EXPECT_NE(sharps, flats);
    EXPECT_EQ(sharps, ScalePattern::FromFormula("1 #4 5"));
    EXPECT_EQ(ScalePattern(), ScalePattern::Invalid());
    EXPECT_EQ(ScalePattern::Invalid().DegreeCount(), 0);
}
