#include <gtest/gtest.h>

#include "PitchTestSupport.h"

using MCC::Accidental;
using MCC::ChromaticClass;
using MCC::Letter;
using MCC::PitchClass;
using MCCTests::AllAccidentals;
using MCCTests::AllLetters;
using MCCTests::AllPitchClasses;

// SPEC-ORD-1, SPEC-ACC-1, SPEC-EQ-1: all 7 x 9 spellings are valid and keep
// their written letter and accidental.
TEST(PitchClassTests, PreservesWrittenSpellingExhaustively) {
    for (const Letter letter : AllLetters) {
        for (const Accidental accidental : AllAccidentals()) {
            const PitchClass pitchClass(letter, accidental);
            EXPECT_TRUE(pitchClass.IsValid());
            EXPECT_EQ(pitchClass.Letter(), letter);
            EXPECT_EQ(pitchClass.Accidental(), accidental);
        }
    }
}

// SPEC-ACC-2: a natural is a written accidental of its own.
TEST(PitchClassTests, LetterOnlyConstructorIsNatural) {
    for (const Letter letter : AllLetters) {
        EXPECT_EQ(PitchClass(letter), PitchClass(letter, Accidental::Natural()));
    }
}

// SPEC-ORD-4: chromatic class = (letter semitone + accidental) mod 12.
TEST(PitchClassTests, DerivesChromaticClassExhaustively) {
    for (const PitchClass pitchClass : AllPitchClasses()) {
        const ChromaticClass chromaticClass = pitchClass.ChromaticClass();
        EXPECT_TRUE(chromaticClass.IsValid());
        EXPECT_LE(chromaticClass.Value(), 11);
        EXPECT_EQ(chromaticClass.Value(),
            MCCTests::ExpectedChromaticClass(pitchClass));
    }
}

// SPEC-ORD-4: reduction wraps across C in both directions.
TEST(PitchClassTests, ChromaticClassWrapsAtOctaveBoundary) {
    EXPECT_EQ(PitchClass(Letter::B, Accidental::Sharp()).ChromaticClass(),
        ChromaticClass(0));
    EXPECT_EQ(PitchClass(Letter::C, Accidental::Flat()).ChromaticClass(),
        ChromaticClass(11));
    EXPECT_EQ(PitchClass(Letter::C, Accidental::QuadrupleFlat()).ChromaticClass(),
        ChromaticClass(8));
    EXPECT_EQ(PitchClass(Letter::B, Accidental::QuadrupleSharp()).ChromaticClass(),
        ChromaticClass(3));
}

// SPEC-ORD-4: the 63 spellings cover every class; each class has 5 or 6
// spellings.
TEST(PitchClassTests, EverySpellingMapsToAClass) {
    int counts[12] = {};
    for (const PitchClass pitchClass : AllPitchClasses()) {
        ++counts[pitchClass.ChromaticClass().Value()];
    }
    int total = 0;
    for (const int count : counts) {
        EXPECT_GE(count, 5);
        EXPECT_LE(count, 6);
        total += count;
    }
    EXPECT_EQ(total, 63);
}

// SPEC-ACC-3: diatonic movement changes the letter and keeps the written
// accidental, including the +-4 boundary spellings; it never respells.
TEST(PitchClassTests, MovedDiatonicallyPreservesSpellingExhaustively) {
    for (const PitchClass pitchClass : AllPitchClasses()) {
        for (int steps = -15; steps <= 15; ++steps) {
            const PitchClass moved = pitchClass.MovedDiatonically(steps);
            EXPECT_TRUE(moved.IsValid());
            EXPECT_EQ(moved.Letter(), MCC::MoveLetter(pitchClass.Letter(), steps));
            EXPECT_EQ(moved.Accidental(), pitchClass.Accidental());
            EXPECT_EQ(moved.MovedDiatonically(-steps), pitchClass);
        }
    }
    const PitchClass bQuadSharp(Letter::B, Accidental::QuadrupleSharp());
    EXPECT_EQ(bQuadSharp.MovedDiatonically(1),
        PitchClass(Letter::C, Accidental::QuadrupleSharp()));
    const PitchClass cQuadFlat(Letter::C, Accidental::QuadrupleFlat());
    EXPECT_EQ(cQuadFlat.MovedDiatonically(-1),
        PitchClass(Letter::B, Accidental::QuadrupleFlat()));
    EXPECT_EQ(PitchClass(Letter::E).MovedDiatonically(1), PitchClass(Letter::F));
}

// SPEC-ACC-3, SPEC-ERR-5: alteration keeps the letter; an accidental
// outside [-4, +4] is invalid and is never respelled with another letter.
TEST(PitchClassTests, AlteredKeepsLetterAndRejectsOverflowExhaustively) {
    for (const PitchClass pitchClass : AllPitchClasses()) {
        for (int delta = -9; delta <= 9; ++delta) {
            const PitchClass altered = pitchClass.Altered(delta);
            const int expected = pitchClass.Accidental().Semitones() + delta;
            if (expected < -4 || expected > 4) {
                EXPECT_FALSE(altered.IsValid());
                EXPECT_EQ(altered, PitchClass::Invalid());
            } else {
                EXPECT_EQ(altered.Letter(), pitchClass.Letter());
                EXPECT_EQ(altered.Accidental(), Accidental(expected));
                EXPECT_EQ(altered.ChromaticClass(),
                    pitchClass.ChromaticClass().Transposed(delta));
            }
        }
    }
    const PitchClass cQuadSharp(Letter::C, Accidental::QuadrupleSharp());
    EXPECT_FALSE(cQuadSharp.Altered(1).IsValid());
    const PitchClass fQuadFlat(Letter::F, Accidental::QuadrupleFlat());
    EXPECT_FALSE(fQuadFlat.Altered(-1).IsValid());
    EXPECT_EQ(PitchClass(Letter::C, Accidental::Sharp()).Altered(1),
        PitchClass(Letter::C, Accidental::DoubleSharp()));
}
