#include <gtest/gtest.h>

#include "IntervalTestSupport.h"

#include <type_traits>

using MCC::Interval;
using MCC::IntervalDirection;
using MCC::IntervalNumber;
using MCC::IntervalQuality;

// SPEC-EMB-2: Interval fits in 4 bytes.
static_assert(sizeof(Interval) <= 4);
static_assert(sizeof(IntervalQuality) == 1);
static_assert(sizeof(IntervalNumber) == 2);
static_assert(sizeof(IntervalDirection) == 1);

// SPEC-EMB-1: trivially copyable, no virtual functions.
static_assert(std::is_trivially_copyable_v<Interval>);
static_assert(std::is_trivially_copyable_v<IntervalQuality>);
static_assert(std::is_trivially_copyable_v<IntervalNumber>);
static_assert(!std::is_polymorphic_v<Interval>);

// SPEC-EQ-3: no implicit conversions.
static_assert(!std::is_convertible_v<int, IntervalNumber>);
static_assert(!std::is_convertible_v<IntervalNumber, int>);
static_assert(!std::is_convertible_v<Interval, int>);

// SPEC-EMB-3: construction, interval arithmetic and transposition are
// constexpr.
constexpr Interval kM3(IntervalQuality::Major(), IntervalNumber(3));
constexpr Interval km3(IntervalQuality::Minor(), IntervalNumber(3));
static_assert(kM3 + km3 == Interval(IntervalQuality::Perfect(), IntervalNumber(5)));
static_assert(kM3.Inverted() == Interval(IntervalQuality::Minor(), IntervalNumber(6)));
static_assert(kM3.Quality() == IntervalQuality::Major());
static_assert(kM3.Number() == IntervalNumber(3));
static_assert(MCC::Pitch(MCC::Letter::E, 4) + kM3 ==
    MCC::Pitch(MCC::Letter::G, MCC::Accidental::Sharp(), 4));
static_assert(MCC::IntervalBetween(MCC::Pitch(MCC::Letter::C, 4),
    MCC::Pitch(MCC::Letter::E, 4)) == kM3);
static_assert(MCC::NoteName(MCC::Letter::B) + km3 ==
    MCC::NoteName(MCC::Letter::D));

TEST(LayoutTests, ReportsSizes) {
    EXPECT_EQ(sizeof(Interval), 4U);
    EXPECT_EQ(sizeof(IntervalQuality), 1U);
    EXPECT_EQ(sizeof(IntervalNumber), 2U);
}
