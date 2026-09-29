#include <gtest/gtest.h>

#include "PitchTestSupport.h"

#include <type_traits>

using MCC::Accidental;
using MCC::PitchClass;
using MCC::Letter;
using MCC::NoteName;

// SPEC-EMB-2: size budgets.
static_assert(sizeof(Letter) == 1);
static_assert(sizeof(Accidental) == 1);
static_assert(sizeof(PitchClass) == 1);
static_assert(sizeof(NoteName) <= 2);

// SPEC-EMB-1: trivially copyable, no virtual functions.
static_assert(std::is_trivially_copyable_v<Letter>);
static_assert(std::is_trivially_copyable_v<Accidental>);
static_assert(std::is_trivially_copyable_v<PitchClass>);
static_assert(std::is_trivially_copyable_v<NoteName>);
static_assert(!std::is_polymorphic_v<Accidental>);
static_assert(!std::is_polymorphic_v<PitchClass>);
static_assert(!std::is_polymorphic_v<NoteName>);
static_assert(std::is_standard_layout_v<Accidental>);
static_assert(std::is_standard_layout_v<PitchClass>);
static_assert(std::is_standard_layout_v<NoteName>);

// SPEC-EMB-3: construction, queries, comparison and movement are constexpr.
constexpr NoteName kCSharp(Letter::C, Accidental::Sharp());
constexpr NoteName kDFlat(Letter::D, Accidental::Flat());
static_assert(kCSharp.IsValid());
static_assert(kCSharp.Letter() == Letter::C);
static_assert(kCSharp.Accidental() == Accidental::Sharp());
static_assert(kCSharp.PitchClass() == PitchClass(1));
static_assert(kCSharp != kDFlat);
static_assert(MCC::IsEnharmonic(kCSharp, kDFlat));
static_assert(kCSharp < kDFlat);
static_assert(kCSharp.MovedDiatonically(2) == NoteName(Letter::E, Accidental::Sharp()));
static_assert(kCSharp.Altered(1) == NoteName(Letter::C, Accidental::DoubleSharp()));
static_assert(!NoteName().IsValid());
static_assert(!Accidental(5).IsValid());
static_assert(PitchClass(11).Transposed(1) == PitchClass(0));
static_assert(MCC::MoveLetter(Letter::B, 1) == Letter::C);
static_assert(MCC::NaturalSemitone(Letter::A) == 9);
static_assert(MCC::DiatonicIndex(Letter::G) == 4);

// SPEC-EMB-3: values usable as constexpr table data (flash-friendly).
constexpr NoteName kCMajor[] = {
    NoteName(Letter::C), NoteName(Letter::D), NoteName(Letter::E),
    NoteName(Letter::F), NoteName(Letter::G), NoteName(Letter::A),
    NoteName(Letter::B)};
static_assert(kCMajor[3].PitchClass() == PitchClass(5));

using MCC::ChromaticIndex;
using MCC::Pitch;

// SPEC-EMB-2: ChromaticIndex is 16 bits and Pitch fits in 4 bytes.
static_assert(sizeof(ChromaticIndex) == 2);
static_assert(sizeof(Pitch) <= 4);

// SPEC-EMB-1: trivially copyable, no virtual functions.
static_assert(std::is_trivially_copyable_v<ChromaticIndex>);
static_assert(std::is_trivially_copyable_v<Pitch>);
static_assert(!std::is_polymorphic_v<ChromaticIndex>);
static_assert(!std::is_polymorphic_v<Pitch>);

// SPEC-EMB-3: pitch construction, queries, comparison and movement are
// constexpr.
constexpr Pitch kBSharp3(Letter::B, Accidental::Sharp(), 3);
constexpr Pitch kC4(Letter::C, 4);
static_assert(kC4.ChromaticIndex() == ChromaticIndex(60));
static_assert(kC4.DiatonicIndex() == 28);
static_assert(MCC::IsEnharmonic(kBSharp3, kC4));
static_assert(kBSharp3 != kC4);
static_assert(kBSharp3 < kC4);
static_assert(MCC::IsLowerThan(Pitch(Letter::C, Accidental::Flat(), 4), kBSharp3));
static_assert(kBSharp3.MovedDiatonically(1) == Pitch(Letter::C, Accidental::Sharp(), 4));
static_assert(kC4.MovedByOctaves(-1) == Pitch(Letter::C, 3));
static_assert(kC4.Altered(1) == Pitch(Letter::C, Accidental::Sharp(), 4));
static_assert(ChromaticIndex(60).Transposed(9) == ChromaticIndex(69));
static_assert(!Pitch(Letter::B, 127).MovedDiatonically(1).IsValid());

// SPEC-EMB-1..3: layout guarantees are checked at compile time above.
TEST(LayoutTests, ReportsSizes) {
    EXPECT_EQ(sizeof(Letter), 1U);
    EXPECT_EQ(sizeof(Accidental), 1U);
    EXPECT_EQ(sizeof(PitchClass), 1U);
    EXPECT_EQ(sizeof(NoteName), 2U);
    EXPECT_EQ(sizeof(ChromaticIndex), 2U);
    EXPECT_EQ(sizeof(Pitch), 3U);
}
