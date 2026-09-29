#include <gtest/gtest.h>

#include "PitchTestSupport.h"

using MCC::Accidental;
using MCC::PitchClass;
using MCC::Letter;
using MCC::NoteName;
using MCCTests::AllAccidentals;
using MCCTests::AllLetters;
using MCCTests::AllNoteNames;

// SPEC-ORD-1, SPEC-ACC-1, SPEC-EQ-1: all 7 x 9 spellings are valid and keep
// their written letter and accidental.
TEST(NoteNameTests, PreservesWrittenSpellingExhaustively) {
    for (const Letter letter : AllLetters) {
        for (const Accidental accidental : AllAccidentals()) {
            const NoteName noteName(letter, accidental);
            EXPECT_TRUE(noteName.IsValid());
            EXPECT_EQ(noteName.Letter(), letter);
            EXPECT_EQ(noteName.Accidental(), accidental);
        }
    }
}

// SPEC-ACC-2: a natural is a written accidental of its own.
TEST(NoteNameTests, LetterOnlyConstructorIsNatural) {
    for (const Letter letter : AllLetters) {
        EXPECT_EQ(NoteName(letter), NoteName(letter, Accidental::Natural()));
    }
}

// SPEC-ORD-4: pitch class = (letter semitone + accidental) mod 12.
TEST(NoteNameTests, DerivesPitchClassExhaustively) {
    for (const NoteName noteName : AllNoteNames()) {
        const PitchClass pitchClass = noteName.PitchClass();
        EXPECT_TRUE(pitchClass.IsValid());
        EXPECT_LE(pitchClass.Value(), 11);
        EXPECT_EQ(pitchClass.Value(),
            MCCTests::ExpectedPitchClass(noteName));
    }
}

// SPEC-ORD-4: reduction wraps across C in both directions.
TEST(NoteNameTests, PitchClassWrapsAtOctaveBoundary) {
    EXPECT_EQ(NoteName(Letter::B, Accidental::Sharp()).PitchClass(),
        PitchClass(0));
    EXPECT_EQ(NoteName(Letter::C, Accidental::Flat()).PitchClass(),
        PitchClass(11));
    EXPECT_EQ(NoteName(Letter::C, Accidental::QuadrupleFlat()).PitchClass(),
        PitchClass(8));
    EXPECT_EQ(NoteName(Letter::B, Accidental::QuadrupleSharp()).PitchClass(),
        PitchClass(3));
}

// SPEC-ORD-4: the 63 spellings cover every class; each class has 5 or 6
// spellings.
TEST(NoteNameTests, EverySpellingMapsToAClass) {
    int counts[12] = {};
    for (const NoteName noteName : AllNoteNames()) {
        ++counts[noteName.PitchClass().Value()];
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
TEST(NoteNameTests, MovedDiatonicallyPreservesSpellingExhaustively) {
    for (const NoteName noteName : AllNoteNames()) {
        for (int steps = -15; steps <= 15; ++steps) {
            const NoteName moved = noteName.MovedDiatonically(steps);
            EXPECT_TRUE(moved.IsValid());
            EXPECT_EQ(moved.Letter(), MCC::MoveLetter(noteName.Letter(), steps));
            EXPECT_EQ(moved.Accidental(), noteName.Accidental());
            EXPECT_EQ(moved.MovedDiatonically(-steps), noteName);
        }
    }
    const NoteName bQuadSharp(Letter::B, Accidental::QuadrupleSharp());
    EXPECT_EQ(bQuadSharp.MovedDiatonically(1),
        NoteName(Letter::C, Accidental::QuadrupleSharp()));
    const NoteName cQuadFlat(Letter::C, Accidental::QuadrupleFlat());
    EXPECT_EQ(cQuadFlat.MovedDiatonically(-1),
        NoteName(Letter::B, Accidental::QuadrupleFlat()));
    EXPECT_EQ(NoteName(Letter::E).MovedDiatonically(1), NoteName(Letter::F));
}

// SPEC-ACC-3, SPEC-ERR-5: alteration keeps the letter; an accidental
// outside [-4, +4] is invalid and is never respelled with another letter.
TEST(NoteNameTests, AlteredKeepsLetterAndRejectsOverflowExhaustively) {
    for (const NoteName noteName : AllNoteNames()) {
        for (int delta = -9; delta <= 9; ++delta) {
            const NoteName altered = noteName.Altered(delta);
            const int expected = noteName.Accidental().Semitones() + delta;
            if (expected < -4 || expected > 4) {
                EXPECT_FALSE(altered.IsValid());
                EXPECT_EQ(altered, NoteName::Invalid());
            } else {
                EXPECT_EQ(altered.Letter(), noteName.Letter());
                EXPECT_EQ(altered.Accidental(), Accidental(expected));
                EXPECT_EQ(altered.PitchClass(),
                    noteName.PitchClass().Transposed(delta));
            }
        }
    }
    const NoteName cQuadSharp(Letter::C, Accidental::QuadrupleSharp());
    EXPECT_FALSE(cQuadSharp.Altered(1).IsValid());
    const NoteName fQuadFlat(Letter::F, Accidental::QuadrupleFlat());
    EXPECT_FALSE(fQuadFlat.Altered(-1).IsValid());
    EXPECT_EQ(NoteName(Letter::C, Accidental::Sharp()).Altered(1),
        NoteName(Letter::C, Accidental::DoubleSharp()));
}
