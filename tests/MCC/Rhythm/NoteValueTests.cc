#include <gtest/gtest.h>

#include <MCC.h>

#include <type_traits>

#ifndef MCC_RHYTHM
    #error "MCC.h must expose MCC_RHYTHM when the Rhythm facade is available"
#endif

using MCC::NoteValue;

namespace {

constexpr NoteValue constexprQuarter = NoteValue::Quarter();
constexpr NoteValue constexprDottedQuarter = NoteValue::Quarter(1);
constexpr NoteValue constexprDoubleDottedQuarter = NoteValue::Quarter(2);
static_assert(constexprQuarter.IsValid());
static_assert(constexprQuarter.Numerator() == 1u);
static_assert(constexprQuarter.Denominator() == 4u);
static_assert(constexprDottedQuarter.Numerator() == 3u);
static_assert(constexprDottedQuarter.Denominator() == 8u);
static_assert(constexprDoubleDottedQuarter.Numerator() == 7u);
static_assert(constexprDoubleDottedQuarter.Denominator() == 16u);
static_assert(NoteValue::FromDenominator(256, 4).IsValid());
static_assert(!NoteValue::FromDenominator(3).IsValid());

} // namespace

TEST(NoteValueTests, NamedBasesUsePowerOfTwoDenominators) {
    const NoteValue values[] = {
        NoteValue::Whole(),
        NoteValue::Half(),
        NoteValue::Quarter(),
        NoteValue::Eighth(),
        NoteValue::Sixteenth(),
        NoteValue::ThirtySecond(),
        NoteValue::SixtyFourth(),
        NoteValue::OneHundredTwentyEighth(),
        NoteValue::TwoHundredFiftySixth(),
    };

    for (uint16_t index = 0; index < 9u; ++index) {
        EXPECT_TRUE(values[index].IsValid());
        EXPECT_EQ(values[index].BaseDenominator(), uint16_t(1u << index));
        EXPECT_EQ(values[index].Numerator(), 1u);
        EXPECT_EQ(values[index].Denominator(), uint16_t(1u << index));
        EXPECT_EQ(values[index].DotCount(), 0u);
        EXPECT_FALSE(values[index].IsDotted());
    }
}

TEST(NoteValueTests, DotsProduceExactReducedFractions) {
    const NoteValue values[] = {
        NoteValue::Quarter(0),
        NoteValue::Quarter(1),
        NoteValue::Quarter(2),
        NoteValue::Quarter(3),
        NoteValue::Quarter(4),
    };
    const uint16_t numerators[] = {1u, 3u, 7u, 15u, 31u};
    const uint16_t denominators[] = {4u, 8u, 16u, 32u, 64u};

    for (uint16_t dots = 0; dots <= NoteValue::MaximumDots; ++dots) {
        EXPECT_EQ(values[dots].Numerator(), numerators[dots]);
        EXPECT_EQ(values[dots].Denominator(), denominators[dots]);
        EXPECT_EQ(values[dots].DotCount(), dots);
        EXPECT_EQ(values[dots].IsDotted(), dots != 0u);
    }
}

TEST(NoteValueTests, EverySupportedValueMatchesTheDotFormula) {
    for (uint16_t base = 1u; base <= 256u; base = static_cast<uint16_t>(base << 1u)) {
        for (uint16_t dots = 0u; dots <= NoteValue::MaximumDots; ++dots) {
            const NoteValue value = NoteValue::FromDenominator(base, dots);
            EXPECT_TRUE(value.IsValid());
            EXPECT_EQ(value.BaseDenominator(), base);
            EXPECT_EQ(value.Numerator(), uint16_t((1u << (dots + 1u)) - 1u));
            EXPECT_EQ(value.Denominator(), uint16_t(base << dots));
        }
    }
}

TEST(NoteValueTests, InvalidInputsProduceTheCanonicalInvalidValue) {
    const int invalidBases[] = {-256, -1, 0, 3, 6, 255, 257};
    for (const int base : invalidBases) {
        EXPECT_EQ(NoteValue::FromDenominator(base), NoteValue::Invalid());
    }

    EXPECT_EQ(NoteValue(), NoteValue::Invalid());
    EXPECT_FALSE(NoteValue().IsValid());
    EXPECT_FALSE(NoteValue().IsDotted());
    EXPECT_EQ(NoteValue().BaseDenominator(), 0u);
    EXPECT_EQ(NoteValue().Numerator(), 0u);
    EXPECT_EQ(NoteValue().Denominator(), 0u);
    EXPECT_EQ(NoteValue().DotCount(), NoteValue::InvalidDotCount);
    EXPECT_EQ(NoteValue::Whole(-1), NoteValue::Invalid());
    EXPECT_EQ(NoteValue::Whole(5), NoteValue::Invalid());
    EXPECT_EQ(NoteValue::TwoHundredFiftySixth(5), NoteValue::Invalid());
}

TEST(NoteValueTests, WithDotsPreservesTheBase) {
    EXPECT_EQ(NoteValue::Eighth().WithDots(3), NoteValue::Eighth(3));
    EXPECT_EQ(NoteValue::Eighth(3).WithDots(0), NoteValue::Eighth());
    EXPECT_EQ(NoteValue::Eighth().WithDots(-1), NoteValue::Invalid());
    EXPECT_EQ(NoteValue::Eighth().WithDots(5), NoteValue::Invalid());
    EXPECT_EQ(NoteValue::Invalid().WithDots(1), NoteValue::Invalid());
}

TEST(NoteValueTests, EqualityPreservesWrittenIdentityAndOrderingUsesDuration) {
    EXPECT_EQ(NoteValue::Quarter(1), NoteValue::Quarter(1));
    EXPECT_NE(NoteValue::Quarter(), NoteValue::Quarter(1));
    EXPECT_NE(NoteValue::Quarter(1), NoteValue::Eighth(1));

    EXPECT_LT(NoteValue::Eighth(), NoteValue::Quarter());
    EXPECT_LT(NoteValue::Quarter(), NoteValue::Quarter(1));
    EXPECT_LT(NoteValue::Quarter(1), NoteValue::Half());
    EXPECT_GT(NoteValue::Whole(), NoteValue::TwoHundredFiftySixth(4));
}

TEST(NoteValueTests, InvalidValuesSortAfterValidValues) {
    EXPECT_LT(NoteValue::Whole(), NoteValue::Invalid());
    EXPECT_FALSE(NoteValue::Invalid() < NoteValue::Whole());
    EXPECT_FALSE(NoteValue::Invalid() < NoteValue::Invalid());
    EXPECT_LE(NoteValue::Invalid(), NoteValue::Invalid());
    EXPECT_GE(NoteValue::Invalid(), NoteValue::Invalid());
}

TEST(NoteValueTests, LayoutAndConstexprMeetEmbeddedRequirements) {
    static_assert(std::is_trivially_copyable_v<NoteValue>);
    static_assert(!std::is_polymorphic_v<NoteValue>);
    static_assert(sizeof(NoteValue) <= 2u);
    SUCCEED();
}
