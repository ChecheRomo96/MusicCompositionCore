#include <gtest/gtest.h>

#include <MCC.h>

#include <type_traits>

using MCC::Meter;
using MCC::MeterKind;
using MCC::NoteValue;

namespace {

constexpr Meter commonTime = Meter::CommonTime();
constexpr Meter compoundDuple = Meter::Compound(2, NoteValue::Quarter(1));
static_assert(commonTime == Meter(4, 4));
static_assert(commonTime.IsSimple());
static_assert(commonTime.BeatCount() == 4u);
static_assert(commonTime.BeatValue() == NoteValue::Quarter());
static_assert(compoundDuple == Meter(6, 8));
static_assert(compoundDuple.IsCompound());
static_assert(compoundDuple.BeatCount() == 2u);
static_assert(compoundDuple.BeatValue() == NoteValue::Quarter(1));
static_assert(compoundDuple.MeasureNumerator() == 3u);
static_assert(compoundDuple.MeasureDenominator() == 4u);

} // namespace

TEST(MeterTests, ConstructsWrittenSignaturesFromDenominatorOrPulseValue) {
    EXPECT_EQ(Meter(4, 4), Meter(4, NoteValue::Quarter()));
    EXPECT_EQ(Meter(3, 8), Meter(3, NoteValue::Eighth()));
    EXPECT_EQ(Meter(12, 16), Meter(12, NoteValue::Sixteenth()));
    EXPECT_EQ(Meter::CommonTime(), Meter(4, 4));
    EXPECT_EQ(Meter::CutTime(), Meter(2, 2));
}

TEST(MeterTests, ClassifiesSimpleCompoundAndIrregularMeters) {
    EXPECT_EQ(Meter(1, 4).Kind(), MeterKind::Simple);
    EXPECT_EQ(Meter(2, 2).Kind(), MeterKind::Simple);
    EXPECT_EQ(Meter(3, 8).Kind(), MeterKind::Simple);
    EXPECT_EQ(Meter(4, 4).Kind(), MeterKind::Simple);

    EXPECT_EQ(Meter(6, 8).Kind(), MeterKind::Compound);
    EXPECT_EQ(Meter(9, 8).Kind(), MeterKind::Compound);
    EXPECT_EQ(Meter(12, 16).Kind(), MeterKind::Compound);
    EXPECT_EQ(Meter(15, 16).Kind(), MeterKind::Compound);

    EXPECT_EQ(Meter(5, 8).Kind(), MeterKind::Irregular);
    EXPECT_EQ(Meter(7, 8).Kind(), MeterKind::Irregular);
    EXPECT_EQ(Meter(8, 8).Kind(), MeterKind::Irregular);
    EXPECT_EQ(Meter(11, 16).Kind(), MeterKind::Irregular);
    EXPECT_EQ(Meter::Invalid().Kind(), MeterKind::Invalid);
}

TEST(MeterTests, SimpleFactoryUsesUndottedBeats) {
    EXPECT_EQ(Meter::Simple(2, NoteValue::Half()), Meter(2, 2));
    EXPECT_EQ(Meter::Simple(3, NoteValue::Quarter()), Meter(3, 4));
    EXPECT_EQ(Meter::Simple(4, NoteValue::Eighth()), Meter(4, 8));
    EXPECT_EQ(Meter::Simple(3).BeatValue(), NoteValue::Quarter());

    EXPECT_EQ(Meter::Simple(0), Meter::Invalid());
    EXPECT_EQ(Meter::Simple(5), Meter::Invalid());
    EXPECT_EQ(Meter::Simple(3, NoteValue::Quarter(1)), Meter::Invalid());
}

TEST(MeterTests, CompoundFactoryConvertsDottedBeatsToWrittenSignatures) {
    EXPECT_EQ(Meter::Compound(2, NoteValue::Quarter(1)), Meter(6, 8));
    EXPECT_EQ(Meter::Compound(3, NoteValue::Quarter(1)), Meter(9, 8));
    EXPECT_EQ(Meter::Compound(4, NoteValue::Eighth(1)), Meter(12, 16));
    EXPECT_EQ(Meter::Compound(5, NoteValue::Half(1)), Meter(15, 4));
    EXPECT_EQ(Meter::Compound(2), Meter(6, 8));

    EXPECT_EQ(Meter::Compound(1), Meter::Invalid());
    EXPECT_EQ(Meter::Compound(86), Meter::Invalid());
    EXPECT_EQ(Meter::Compound(2, NoteValue::Quarter()), Meter::Invalid());
    EXPECT_EQ(Meter::Compound(2, NoteValue::Quarter(2)), Meter::Invalid());
    EXPECT_EQ(Meter::Compound(2, NoteValue::TwoHundredFiftySixth(1)),
              Meter::Invalid());
}

TEST(MeterTests, ReportsPulseAndBeatInterpretations) {
    const Meter simple(3, 4);
    EXPECT_EQ(simple.PulseCount(), 3u);
    EXPECT_EQ(simple.PulseValue(), NoteValue::Quarter());
    EXPECT_EQ(simple.BeatCount(), 3u);
    EXPECT_EQ(simple.BeatValue(), NoteValue::Quarter());

    const Meter compound(12, 8);
    EXPECT_EQ(compound.PulseCount(), 12u);
    EXPECT_EQ(compound.PulseValue(), NoteValue::Eighth());
    EXPECT_EQ(compound.BeatCount(), 4u);
    EXPECT_EQ(compound.BeatValue(), NoteValue::Quarter(1));
}

TEST(MeterTests, DoesNotInventAnIrregularGrouping) {
    const Meter fiveEight(5, 8);
    EXPECT_TRUE(fiveEight.IsIrregular());
    EXPECT_EQ(fiveEight.BeatCount(), 0u);
    EXPECT_FALSE(fiveEight.BeatValue().IsValid());
    EXPECT_EQ(fiveEight.PulseCount(), 5u);
    EXPECT_EQ(fiveEight.PulseValue(), NoteValue::Eighth());
}

TEST(MeterTests, ReducesTheExactMeasureDuration) {
    EXPECT_EQ(Meter(4, 4).MeasureNumerator(), 1u);
    EXPECT_EQ(Meter(4, 4).MeasureDenominator(), 1u);
    EXPECT_EQ(Meter(3, 4).MeasureNumerator(), 3u);
    EXPECT_EQ(Meter(3, 4).MeasureDenominator(), 4u);
    EXPECT_EQ(Meter(6, 8).MeasureNumerator(), 3u);
    EXPECT_EQ(Meter(6, 8).MeasureDenominator(), 4u);
    EXPECT_EQ(Meter(12, 8).MeasureNumerator(), 3u);
    EXPECT_EQ(Meter(12, 8).MeasureDenominator(), 2u);
    EXPECT_TRUE(MCC::HasSameMeasureDuration(Meter(3, 4), Meter(6, 8)));
    EXPECT_FALSE(MCC::HasSameMeasureDuration(Meter(3, 4), Meter(4, 4)));
}

TEST(MeterTests, RejectsInvalidWrittenSignatures) {
    const int invalidNumerators[] = {-1, 0, 256, 1000};
    for (const int numerator : invalidNumerators) {
        EXPECT_EQ(Meter(numerator, 4), Meter::Invalid());
    }

    const int invalidDenominators[] = {-4, 0, 3, 6, 255, 257, 512};
    for (const int denominator : invalidDenominators) {
        EXPECT_EQ(Meter(4, denominator), Meter::Invalid());
    }

    EXPECT_EQ(Meter(4, NoteValue::Quarter(1)), Meter::Invalid());
    EXPECT_EQ(Meter(6, 1), Meter::Invalid());
    EXPECT_EQ(Meter(), Meter::Invalid());
    EXPECT_EQ(Meter::Invalid().Numerator(), 0u);
    EXPECT_EQ(Meter::Invalid().Denominator(), 0u);
    EXPECT_EQ(Meter::Invalid().MeasureNumerator(), 0u);
    EXPECT_EQ(Meter::Invalid().MeasureDenominator(), 0u);
}

TEST(MeterTests, WrittenEqualityDiffersFromEqualMeasureDuration) {
    EXPECT_NE(Meter(3, 4), Meter(6, 8));
    EXPECT_TRUE(MCC::HasSameMeasureDuration(Meter(3, 4), Meter(6, 8)));
    EXPECT_LT(Meter(3, 4), Meter(4, 4));
    EXPECT_LT(Meter(12, 8), Meter::Invalid());
    EXPECT_FALSE(Meter::Invalid() < Meter(4, 4));
}

TEST(MeterTests, EverySupportedSignatureKeepsItsWrittenValues) {
    const int denominators[] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    for (const int denominator : denominators) {
        for (int numerator = 1; numerator <= 255; ++numerator) {
            const Meter meter(numerator, denominator);
            if (denominator == 1 && numerator >= 6 && numerator % 3 == 0) {
                EXPECT_FALSE(meter.IsValid());
            } else {
                EXPECT_TRUE(meter.IsValid());
                EXPECT_EQ(meter.Numerator(), numerator);
                EXPECT_EQ(meter.Denominator(), denominator);
            }
        }
    }
}

TEST(MeterTests, LayoutAndConstexprMeetEmbeddedRequirements) {
    static_assert(std::is_trivially_copyable_v<Meter>);
    static_assert(!std::is_polymorphic_v<Meter>);
    static_assert(sizeof(Meter) <= 3u);
    SUCCEED();
}
