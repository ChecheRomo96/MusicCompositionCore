#include <gtest/gtest.h>

#include "PitchTestSupport.h"

#include <algorithm>
#include <vector>
#include <type_traits>

using MCC::Accidental;
using MCC::PitchClass;
using MCC::Letter;
using MCC::NoteName;
using MCCTests::AllNoteNames;

// SPEC-EQ-1: operator== compares written spelling; C# != Db.
TEST(PitchComparisonTests, WrittenEqualityIsSpellingEqualityExhaustively) {
    const auto all = AllNoteNames();
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
    EXPECT_NE(NoteName(Letter::C, Accidental::Sharp()),
        NoteName(Letter::D, Accidental::Flat()));
}

// SPEC-EQ-2: enharmonic equivalence compares pitch classes and is
// distinct from written equality.
TEST(PitchComparisonTests, EnharmonicEquivalenceComparesClassesExhaustively) {
    const auto all = AllNoteNames();
    int enharmonicButUnequal = 0;
    for (const NoteName a : all) {
        for (const NoteName b : all) {
            const bool sameClass =
                MCCTests::ExpectedPitchClass(a) ==
                MCCTests::ExpectedPitchClass(b);
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

    const NoteName cSharp(Letter::C, Accidental::Sharp());
    const NoteName dFlat(Letter::D, Accidental::Flat());
    EXPECT_TRUE(MCC::IsEnharmonic(cSharp, dFlat));
    EXPECT_FALSE(cSharp == dFlat);
    EXPECT_TRUE(MCC::IsEnharmonic(NoteName(Letter::B, Accidental::Sharp()),
        NoteName(Letter::C)));
    EXPECT_TRUE(MCC::IsEnharmonic(NoteName(Letter::C, Accidental::QuadrupleFlat()),
        NoteName(Letter::G, Accidental::Sharp())));
    EXPECT_FALSE(MCC::IsEnharmonic(NoteName(Letter::C), NoteName(Letter::D)));
}

// SPEC-EQ-3: no implicit conversions between pitch types or from integers.
TEST(PitchComparisonTests, NoImplicitConversions) {
    static_assert(!std::is_convertible_v<NoteName, PitchClass>);
    static_assert(!std::is_convertible_v<PitchClass, NoteName>);
    static_assert(!std::is_convertible_v<int, PitchClass>);
    static_assert(!std::is_convertible_v<int, Accidental>);
    static_assert(!std::is_convertible_v<Letter, NoteName>);
    static_assert(!std::is_convertible_v<NoteName, int>);
    static_assert(!std::is_convertible_v<Accidental, int>);
    static_assert(!std::is_convertible_v<PitchClass, int>);
    static_assert(!std::is_convertible_v<Letter, int>);
    SUCCEED();
}

// SPEC-ORD-5: operator< is written order: letter, then accidental. It is
// not chromatic order: C## sorts before Db although its class is higher.
TEST(PitchComparisonTests, WrittenOrderIsLetterThenAccidentalExhaustively) {
    const auto all = AllNoteNames();  // Generated in written order.
    for (size_t i = 0; i < all.size(); ++i) {
        for (size_t j = 0; j < all.size(); ++j) {
            EXPECT_EQ(all[i] < all[j], i < j);
            EXPECT_EQ(all[i] > all[j], i > j);
            EXPECT_EQ(all[i] <= all[j], i <= j);
            EXPECT_EQ(all[i] >= all[j], i >= j);
        }
    }

    const NoteName cDoubleSharp(Letter::C, Accidental::DoubleSharp());
    const NoteName dFlat(Letter::D, Accidental::Flat());
    EXPECT_LT(cDoubleSharp, dFlat);
    EXPECT_GT(cDoubleSharp.PitchClass(), dFlat.PitchClass());

    auto shuffled = all;
    std::reverse(shuffled.begin(), shuffled.end());
    std::sort(shuffled.begin(), shuffled.end());
    EXPECT_EQ(shuffled, all);
}

// SPEC-EQ-1: written equality of pitches includes the octave; C#4 != Db4.
TEST(PitchComparisonTests, PitchWrittenEquality) {
    using MCC::Pitch;
    const Pitch cSharp4(Letter::C, Accidental::Sharp(), 4);
    const Pitch dFlat4(Letter::D, Accidental::Flat(), 4);
    EXPECT_NE(cSharp4, dFlat4);
    EXPECT_NE(cSharp4, Pitch(Letter::C, Accidental::Sharp(), 5));
    EXPECT_EQ(cSharp4, Pitch(MCC::NoteName(Letter::C, Accidental::Sharp()), 4));
    MCCTests::ForEachPitch([](Pitch pitch) {
        EXPECT_EQ(pitch, Pitch(pitch.NoteName(), pitch.Octave()));
    });
}

// SPEC-EQ-2: pitch enharmony compares chromatic indices: B#3 ~ C4, not C3.
TEST(PitchComparisonTests, PitchEnharmonicEquivalence) {
    using MCC::Pitch;
    const Pitch bSharp3(Letter::B, Accidental::Sharp(), 3);
    EXPECT_TRUE(MCC::IsEnharmonic(bSharp3, Pitch(Letter::C, 4)));
    EXPECT_FALSE(MCC::IsEnharmonic(bSharp3, Pitch(Letter::C, 3)));
    EXPECT_TRUE(MCC::IsEnharmonic(Pitch(Letter::C, Accidental::Sharp(), 4),
        Pitch(Letter::D, Accidental::Flat(), 4)));
    EXPECT_FALSE(MCC::IsEnharmonic(Pitch(Letter::C, Accidental::Sharp(), 4),
        Pitch(Letter::D, Accidental::Flat(), 5)));

    // Every pitch is enharmonic to exactly the spellings with its index.
    const Pitch reference(Letter::E, 2);
    int enharmonics = 0;
    MCCTests::ForEachPitch([&](Pitch pitch) {
        const bool expected = pitch.ChromaticIndex() == reference.ChromaticIndex();
        EXPECT_EQ(MCC::IsEnharmonic(pitch, reference), expected);
        enharmonics += expected ? 1 : 0;
    });
    EXPECT_EQ(enharmonics, 5);  // C####2, D##2, E2, Fb2, Gbbb2.
}

// SPEC-EQ-3: no implicit conversions between pitch and index types.
TEST(PitchComparisonTests, NoImplicitPitchConversions) {
    using MCC::ChromaticIndex;
    using MCC::Pitch;
    static_assert(!std::is_convertible_v<Pitch, ChromaticIndex>);
    static_assert(!std::is_convertible_v<ChromaticIndex, Pitch>);
    static_assert(!std::is_convertible_v<Pitch, NoteName>);
    static_assert(!std::is_convertible_v<NoteName, Pitch>);
    static_assert(!std::is_convertible_v<ChromaticIndex, PitchClass>);
    static_assert(!std::is_convertible_v<int, ChromaticIndex>);
    static_assert(!std::is_convertible_v<ChromaticIndex, int>);
    SUCCEED();
}

// SPEC-ORD-5: written order is octave, letter, accidental: B#3 < Cb4 although
// B#3 sounds higher.
TEST(PitchComparisonTests, PitchWrittenOrder) {
    using MCC::Pitch;
    const Pitch bSharp3(Letter::B, Accidental::Sharp(), 3);
    const Pitch cFlat4(Letter::C, Accidental::Flat(), 4);
    EXPECT_LT(bSharp3, cFlat4);
    EXPECT_GT(bSharp3.ChromaticIndex(), cFlat4.ChromaticIndex());

    // ForEachPitch visits pitches in written order.
    Pitch previous = Pitch::Invalid();
    bool first = true;
    MCCTests::ForEachPitch([&](Pitch pitch) {
        if (!first) {
            EXPECT_LT(previous, pitch);
            EXPECT_FALSE(pitch < previous);
        }
        previous = pitch;
        first = false;
    });
}

// SPEC-ORD-6: pitch height compares chromatic indices; enharmonic ties are
// broken by written order, so sorting is deterministic.
TEST(PitchComparisonTests, PitchHeightOrder) {
    using MCC::Pitch;
    const Pitch bSharp3(Letter::B, Accidental::Sharp(), 3);
    const Pitch cFlat4(Letter::C, Accidental::Flat(), 4);
    const Pitch c4(Letter::C, 4);
    EXPECT_TRUE(MCC::IsLowerThan(cFlat4, bSharp3));
    EXPECT_FALSE(MCC::IsLowerThan(bSharp3, cFlat4));
    EXPECT_TRUE(MCC::IsLowerThan(bSharp3, c4));   // Same height, B# written first.
    EXPECT_FALSE(MCC::IsLowerThan(c4, bSharp3));
    EXPECT_FALSE(MCC::IsLowerThan(c4, c4));

    std::vector<Pitch> pitches = {
        Pitch(Letter::D, 4), c4, bSharp3, cFlat4, Pitch(Letter::A, 3),
        Pitch(Letter::D, Accidental::DoubleFlat(), 4), Pitch::Invalid()};
    std::sort(pitches.begin(), pitches.end(), MCC::IsLowerThan);
    const std::vector<Pitch> expected = {
        Pitch(Letter::A, 3), cFlat4, bSharp3, c4,
        Pitch(Letter::D, Accidental::DoubleFlat(), 4), Pitch(Letter::D, 4),
        Pitch::Invalid()};
    EXPECT_EQ(pitches, expected);
}
