#include <gtest/gtest.h>

#include "PitchTestSupport.h"

#include <algorithm>
#include <type_traits>

using MCC::Accidental;
using MCC::ChromaticClass;
using MCC::Letter;
using MCC::PitchClass;
using MCCTests::AllPitchClasses;

// SPEC-EQ-1: operator== compares written spelling; C# != Db.
TEST(PitchComparisonTests, WrittenEqualityIsSpellingEqualityExhaustively) {
    const auto all = AllPitchClasses();
    for (size_t i = 0; i < all.size(); ++i) {
        for (size_t j = 0; j < all.size(); ++j) {
            const bool sameSpelling =
                all[i].Letter() == all[j].Letter() &&
                all[i].Accidental() == all[j].Accidental();
            EXPECT_EQ(all[i] == all[j], i == j);
            EXPECT_EQ(all[i] == all[j], sameSpelling);
            EXPECT_EQ(all[i] != all[j], !sameSpelling);
        }
    }
    EXPECT_NE(PitchClass(Letter::C, Accidental::Sharp()),
        PitchClass(Letter::D, Accidental::Flat()));
}

// SPEC-EQ-2: enharmonic equivalence compares chromatic classes and is
// distinct from written equality.
TEST(PitchComparisonTests, EnharmonicEquivalenceComparesClassesExhaustively) {
    const auto all = AllPitchClasses();
    int enharmonicButUnequal = 0;
    for (const PitchClass a : all) {
        for (const PitchClass b : all) {
            const bool sameClass =
                MCCTests::ExpectedChromaticClass(a) ==
                MCCTests::ExpectedChromaticClass(b);
            EXPECT_EQ(MCC::IsEnharmonic(a, b), sameClass);
            EXPECT_EQ(MCC::IsEnharmonic(a, b), MCC::IsEnharmonic(b, a));
            if (a == b) {
                EXPECT_TRUE(MCC::IsEnharmonic(a, b));
            }
            if (sameClass && a != b) {
                ++enharmonicButUnequal;
            }
        }
    }
    EXPECT_GT(enharmonicButUnequal, 0);

    const PitchClass cSharp(Letter::C, Accidental::Sharp());
    const PitchClass dFlat(Letter::D, Accidental::Flat());
    EXPECT_TRUE(MCC::IsEnharmonic(cSharp, dFlat));
    EXPECT_FALSE(cSharp == dFlat);
    EXPECT_TRUE(MCC::IsEnharmonic(PitchClass(Letter::B, Accidental::Sharp()),
        PitchClass(Letter::C)));
    EXPECT_TRUE(MCC::IsEnharmonic(PitchClass(Letter::C, Accidental::QuadrupleFlat()),
        PitchClass(Letter::G, Accidental::Sharp())));
    EXPECT_FALSE(MCC::IsEnharmonic(PitchClass(Letter::C), PitchClass(Letter::D)));
}

// SPEC-EQ-3: no implicit conversions between pitch types or from integers.
TEST(PitchComparisonTests, NoImplicitConversions) {
    static_assert(!std::is_convertible_v<PitchClass, ChromaticClass>);
    static_assert(!std::is_convertible_v<ChromaticClass, PitchClass>);
    static_assert(!std::is_convertible_v<int, ChromaticClass>);
    static_assert(!std::is_convertible_v<int, Accidental>);
    static_assert(!std::is_convertible_v<Letter, PitchClass>);
    static_assert(!std::is_convertible_v<PitchClass, int>);
    static_assert(!std::is_convertible_v<Accidental, int>);
    static_assert(!std::is_convertible_v<ChromaticClass, int>);
    static_assert(!std::is_convertible_v<Letter, int>);
    SUCCEED();
}

// SPEC-ORD-5: operator< is written order: letter, then accidental. It is
// not chromatic order: C## sorts before Db although its class is higher.
TEST(PitchComparisonTests, WrittenOrderIsLetterThenAccidentalExhaustively) {
    const auto all = AllPitchClasses();  // Generated in written order.
    for (size_t i = 0; i < all.size(); ++i) {
        for (size_t j = 0; j < all.size(); ++j) {
            EXPECT_EQ(all[i] < all[j], i < j);
            EXPECT_EQ(all[i] > all[j], i > j);
            EXPECT_EQ(all[i] <= all[j], i <= j);
            EXPECT_EQ(all[i] >= all[j], i >= j);
        }
    }

    const PitchClass cDoubleSharp(Letter::C, Accidental::DoubleSharp());
    const PitchClass dFlat(Letter::D, Accidental::Flat());
    EXPECT_LT(cDoubleSharp, dFlat);
    EXPECT_GT(cDoubleSharp.ChromaticClass(), dFlat.ChromaticClass());

    auto shuffled = all;
    std::reverse(shuffled.begin(), shuffled.end());
    std::sort(shuffled.begin(), shuffled.end());
    EXPECT_EQ(shuffled, all);
}
