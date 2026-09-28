#include <gtest/gtest.h>

#include <MCC.h>

#include <cfloat>
#include <cmath>
#include <limits>
#include <type_traits>

#ifndef MCC_TUNING
    #error "MCC.h must expose MCC_TUNING when the Tuning facade is available"
#endif

using MCC::Accidental;
using MCC::EqualTemperament;
using MCC::Letter;
using MCC::Pitch;
using MCC::Tuning;

namespace {

// Reference frequency computed in double precision with pow().
double ReferenceFrequency(Pitch pitch, Tuning tuning) {
    const int distance = pitch.ChromaticIndex().Value() -
        tuning.Reference().ChromaticIndex().Value();
    return tuning.ReferenceFrequency() * std::pow(2.0, distance / 12.0);
}

} // namespace

// SPEC-OCT-2: under the standard tuning A4 is exactly 440 Hz.
TEST(TuningTests, StandardTuningIsA440) {
    const Tuning standard = Tuning::Standard();
    EXPECT_TRUE(standard.IsValid());
    EXPECT_EQ(standard.Reference(), Pitch(Letter::A, 4));
    EXPECT_EQ(standard.ReferenceFrequency(), 440.0f);
    EXPECT_EQ(EqualTemperament::Standard().Frequency(Pitch(Letter::A, 4)), 440.0f);
    EXPECT_EQ(EqualTemperament::Standard().Tuning(), standard);
}

// SPEC-OCT-2: C4 is about 261.63 Hz and octaves double exactly.
TEST(TuningTests, KnownFrequencies) {
    const EqualTemperament temperament = EqualTemperament::Standard();
    EXPECT_NEAR(temperament.Frequency(Pitch(Letter::C, 4)), 261.6256f, 0.001f);
    EXPECT_NEAR(temperament.Frequency(Pitch(Letter::C, -1)), 8.1758f, 0.0001f);
    EXPECT_EQ(temperament.Frequency(Pitch(Letter::A, 5)), 880.0f);
    EXPECT_EQ(temperament.Frequency(Pitch(Letter::A, 3)), 220.0f);
    EXPECT_EQ(temperament.Frequency(Pitch(Letter::A, 0)), 27.5f);
}

// SPEC-OCT-2: equal temperament matches 440 * 2^(n / 12) for every spelling
// in a wide range of octaves, with float precision.
TEST(TuningTests, MatchesReferenceFormula) {
    const Tuning standard = Tuning::Standard();
    const EqualTemperament temperament(standard);
    for (int octave = -10; octave <= 20; ++octave) {
        for (int letter = 0; letter < 7; ++letter) {
            for (int accidental = -4; accidental <= 4; ++accidental) {
                const Pitch pitch(static_cast<Letter>(letter),
                    Accidental(accidental), octave);
                const double expected = ReferenceFrequency(pitch, standard);
                EXPECT_NEAR(temperament.Frequency(pitch), expected, expected * 1e-6)
                    << "letter " << letter << " accidental " << accidental
                    << " octave " << octave;
            }
        }
    }
}

// SPEC-EQ-2: enharmonic pitches sound at the same frequency.
TEST(TuningTests, EnharmonicPitchesShareFrequency) {
    const EqualTemperament temperament = EqualTemperament::Standard();
    EXPECT_EQ(temperament.Frequency(Pitch(Letter::B, Accidental::Sharp(), 3)),
        temperament.Frequency(Pitch(Letter::C, 4)));
    EXPECT_EQ(temperament.Frequency(Pitch(Letter::C, Accidental::Sharp(), 4)),
        temperament.Frequency(Pitch(Letter::D, Accidental::Flat(), 4)));
    EXPECT_EQ(temperament.Frequency(Pitch(Letter::C, Accidental::Flat(), 4)),
        temperament.Frequency(Pitch(Letter::B, 3)));
}

// Frequencies increase with pitch height until they leave the float range,
// which under A4 = 440 Hz happens after B123.
TEST(TuningTests, FrequencyIncreasesWithPitchHeight) {
    const EqualTemperament temperament = EqualTemperament::Standard();
    float previous = 0.0f;
    for (int octave = -128; octave <= 127; ++octave) {
        for (int letter = 0; letter < 7; ++letter) {
            const Pitch pitch(static_cast<Letter>(letter), octave);
            const float frequency = temperament.Frequency(pitch);
            if (octave <= 123) {
                EXPECT_GT(frequency, previous) << octave;
                EXPECT_TRUE(std::isfinite(frequency));
            } else {
                EXPECT_EQ(frequency, 0.0f) << octave;
            }
            previous = frequency;
        }
    }
}

// Custom tunings move every frequency proportionally.
TEST(TuningTests, CustomReference) {
    const EqualTemperament a432(Tuning(Pitch(Letter::A, 4), 432.0f));
    EXPECT_EQ(a432.Frequency(Pitch(Letter::A, 4)), 432.0f);
    EXPECT_EQ(a432.Frequency(Pitch(Letter::A, 2)), 108.0f);

    const EqualTemperament scientific(Tuning(Pitch(Letter::C, 4), 256.0f));
    EXPECT_EQ(scientific.Frequency(Pitch(Letter::C, 5)), 512.0f);
    EXPECT_NEAR(scientific.Frequency(Pitch(Letter::A, 4)), 430.54f, 0.01f);

    // A spelled reference works like its enharmonic equivalent.
    const EqualTemperament spelled(
        Tuning(Pitch(Letter::G, Accidental::DoubleSharp(), 4), 440.0f));
    EXPECT_EQ(spelled.Frequency(Pitch(Letter::A, 4)), 440.0f);
}

// SPEC-OCT-4, SPEC-ERR-5: every octave is accepted; frequencies above the
// float range (after B123 under A4 = 440 Hz) return 0.
TEST(TuningTests, ExtremePitches) {
    const EqualTemperament temperament = EqualTemperament::Standard();
    const float lowest =
        temperament.Frequency(Pitch(Letter::C, Accidental::QuadrupleFlat(), -128));
    EXPECT_GT(lowest, 0.0f);
    EXPECT_NEAR(lowest / ReferenceFrequency(
        Pitch(Letter::C, Accidental::QuadrupleFlat(), -128), Tuning::Standard()),
        1.0, 1e-5);
    EXPECT_GT(temperament.Frequency(Pitch(Letter::B, 123)), 3e38f);
    EXPECT_EQ(temperament.Frequency(Pitch(Letter::C, 124)), 0.0f);
    EXPECT_EQ(temperament.Frequency(Pitch(Letter::C, 127)), 0.0f);
    EXPECT_EQ(temperament.Frequency(
        Pitch(Letter::B, Accidental::QuadrupleSharp(), 127)), 0.0f);
}

// SPEC-ERR-2, SPEC-ERR-3: invalid tunings.
TEST(TuningTests, InvalidTunings) {
    EXPECT_FALSE(Tuning().IsValid());
    EXPECT_EQ(Tuning(), Tuning::Invalid());
    EXPECT_FALSE(Tuning(Pitch(), 440.0f).IsValid());
    EXPECT_FALSE(Tuning(Pitch(Letter::A, 4), 0.0f).IsValid());
    EXPECT_FALSE(Tuning(Pitch(Letter::A, 4), -440.0f).IsValid());
    EXPECT_FALSE(Tuning(Pitch(Letter::A, 4),
        std::numeric_limits<float>::infinity()).IsValid());
    EXPECT_FALSE(Tuning(Pitch(Letter::A, 4),
        std::numeric_limits<float>::quiet_NaN()).IsValid());
    EXPECT_TRUE(Tuning(Pitch(Letter::A, 4), FLT_MAX).IsValid());
    EXPECT_EQ(Tuning::Invalid().ReferenceFrequency(), 0.0f);
    EXPECT_FALSE(Tuning::Invalid().Reference().IsValid());
}

// SPEC-ERR-4, SPEC-ERR-6, SPEC-ERR-7: invalid inputs yield frequency 0.
TEST(TuningTests, InvalidInputsYieldZero) {
    EXPECT_FALSE(EqualTemperament().IsValid());
    EXPECT_EQ(EqualTemperament().Frequency(Pitch(Letter::A, 4)), 0.0f);
    EXPECT_EQ(EqualTemperament::Standard().Frequency(Pitch()), 0.0f);
    EXPECT_EQ(EqualTemperament(Tuning(Pitch(Letter::A, 4), -1.0f))
        .Frequency(Pitch(Letter::A, 4)), 0.0f);
    EXPECT_EQ(EqualTemperament(), EqualTemperament(Tuning::Invalid()));
}

// SPEC-EMB-1, SPEC-EMB-3: value types usable in constant expressions.
TEST(TuningTests, LayoutAndConstexpr) {
    static_assert(std::is_trivially_copyable_v<Tuning>);
    static_assert(std::is_trivially_copyable_v<EqualTemperament>);
    static_assert(!std::is_polymorphic_v<Tuning>);
    static_assert(!std::is_polymorphic_v<EqualTemperament>);
    static_assert(sizeof(Tuning) <= 8);
    static_assert(sizeof(EqualTemperament) <= 8);

    constexpr EqualTemperament temperament = EqualTemperament::Standard();
    static_assert(temperament.Frequency(Pitch(Letter::A, 4)) == 440.0f);
    static_assert(temperament.Frequency(Pitch(Letter::A, 6)) == 1760.0f);
    static_assert(temperament.Frequency(Pitch(Letter::C, 127)) == 0.0f);
    constexpr float c4 = temperament.Frequency(Pitch(Letter::C, 4));
    static_assert(c4 > 261.62f && c4 < 261.63f);
    SUCCEED();
}
