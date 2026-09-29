#include <gtest/gtest.h>

#include "IntervalTestSupport.h"

#ifndef MCC_INTERVAL
    #error "MCC.h must expose MCC_INTERVAL when the Interval facade is available"
#endif

using MCC::IntervalQuality;
using MCC::IntervalQualityKind;

// SPEC-INT-4: perfect, major, minor, and augmented/diminished 1-4 times.
TEST(IntervalQualityTests, SupportsEveryQuality) {
    EXPECT_EQ(IntervalQuality::Perfect().Kind(), IntervalQualityKind::Perfect);
    EXPECT_EQ(IntervalQuality::Major().Kind(), IntervalQualityKind::Major);
    EXPECT_EQ(IntervalQuality::Minor().Kind(), IntervalQualityKind::Minor);
    EXPECT_EQ(IntervalQuality::Perfect().Count(), 1);
    for (int count = 1; count <= 4; ++count) {
        const IntervalQuality augmented = IntervalQuality::Augmented(count);
        const IntervalQuality diminished = IntervalQuality::Diminished(count);
        EXPECT_TRUE(augmented.IsValid());
        EXPECT_TRUE(diminished.IsValid());
        EXPECT_EQ(augmented.Kind(), IntervalQualityKind::Augmented);
        EXPECT_EQ(diminished.Kind(), IntervalQualityKind::Diminished);
        EXPECT_EQ(augmented.Count(), count);
        EXPECT_EQ(diminished.Count(), count);
    }
    EXPECT_EQ(IntervalQuality::Augmented(), IntervalQuality::Augmented(1));
    const auto all = MCCTests::AllQualities();
    for (size_t i = 0; i < all.size(); ++i) {
        for (size_t j = 0; j < all.size(); ++j) {
            EXPECT_EQ(all[i] == all[j], i == j);
        }
    }
}

// SPEC-INT-4, SPEC-ERR-3: repetition counts outside 1-4 are invalid.
TEST(IntervalQualityTests, RejectsOutOfRangeCounts) {
    for (const int count : {0, 5, -1, 100}) {
        EXPECT_FALSE(IntervalQuality::Augmented(count).IsValid()) << count;
        EXPECT_FALSE(IntervalQuality::Diminished(count).IsValid()) << count;
    }
}

// SPEC-INT-6: inversion swaps major/minor and augmented/diminished.
TEST(IntervalQualityTests, InvertedSwapsQualities) {
    EXPECT_EQ(IntervalQuality::Perfect().Inverted(), IntervalQuality::Perfect());
    EXPECT_EQ(IntervalQuality::Major().Inverted(), IntervalQuality::Minor());
    EXPECT_EQ(IntervalQuality::Minor().Inverted(), IntervalQuality::Major());
    for (int count = 1; count <= 4; ++count) {
        EXPECT_EQ(IntervalQuality::Augmented(count).Inverted(),
            IntervalQuality::Diminished(count));
        EXPECT_EQ(IntervalQuality::Diminished(count).Inverted(),
            IntervalQuality::Augmented(count));
    }
    for (const IntervalQuality quality : MCCTests::AllQualities()) {
        EXPECT_EQ(quality.Inverted().Inverted(), quality);
    }
}
