#include <gtest/gtest.h>

#include "PitchTestSupport.h"

using MCC::Accidental;
using MCC::ChromaticIndex;
using MCC::Letter;
using MCC::Pitch;
using MCC::NoteName;

// SPEC-OCT-1, SPEC-OCT-4: every note name in every octave -128..127 is
// writable and keeps its spelling and octave.
TEST(PitchTests, PreservesSpellingAndOctaveExhaustively) {
    int count = 0;
    MCCTests::ForEachPitch([&](Pitch pitch) {
        EXPECT_TRUE(pitch.IsValid());
        ++count;
    });
    EXPECT_EQ(count, 7 * 9 * 256);

    for (int octave = -128; octave <= 127; ++octave) {
        for (const NoteName noteName : MCCTests::AllNoteNames()) {
            const Pitch pitch(noteName, octave);
            EXPECT_EQ(pitch.NoteName(), noteName);
            EXPECT_EQ(pitch.Letter(), noteName.Letter());
            EXPECT_EQ(pitch.Accidental(), noteName.Accidental());
            EXPECT_EQ(pitch.Octave(), octave);
            EXPECT_EQ(pitch.PitchClass(), noteName.PitchClass());
        }
    }
}

// SPEC-OCT-1: middle C is C4.
TEST(PitchTests, MiddleCIsC4) {
    EXPECT_EQ(Pitch(Letter::C, 4).ChromaticIndex(), ChromaticIndex(60));
    EXPECT_EQ(Pitch(Letter::C, 4), Pitch(Letter::C, Accidental::Natural(), 4));
    EXPECT_EQ(Pitch(Letter::C, 4), Pitch(NoteName(Letter::C), 4));
}

// SPEC-OCT-4: octaves outside [-128, 127] are invalid.
TEST(PitchTests, RejectsOutOfRangeOctaves) {
    EXPECT_TRUE(Pitch(Letter::C, -128).IsValid());
    EXPECT_TRUE(Pitch(Letter::B, 127).IsValid());
    EXPECT_FALSE(Pitch(Letter::C, -129).IsValid());
    EXPECT_FALSE(Pitch(Letter::C, 128).IsValid());
    EXPECT_FALSE(Pitch(Letter::C, INT32_MAX).IsValid());
}

// SPEC-ORD-2: diatonic index = octave * 7 + letterIndex.
TEST(PitchTests, DiatonicIndexExhaustively) {
    MCCTests::ForEachPitch([](Pitch pitch) {
        EXPECT_EQ(pitch.DiatonicIndex(),
            pitch.Octave() * 7 + MCC::DiatonicIndex(pitch.Letter()));
    });
    EXPECT_EQ(Pitch(Letter::C, 0).DiatonicIndex(), 0);
    EXPECT_EQ(Pitch(Letter::B, -1).DiatonicIndex(), -1);
    EXPECT_EQ(Pitch(Letter::C, 4).DiatonicIndex(), 28);
}

// SPEC-ORD-3, SPEC-CHR-2: chromatic index =
// (octave + 1) * 12 + letterSemitone + accidental, always representable.
TEST(PitchTests, ChromaticIndexExhaustively) {
    MCCTests::ForEachPitch([](Pitch pitch) {
        const ChromaticIndex index = pitch.ChromaticIndex();
        EXPECT_TRUE(index.IsValid());
        EXPECT_EQ(index.Value(), MCCTests::ExpectedChromaticIndex(pitch));
        EXPECT_EQ(index.PitchClass(), pitch.PitchClass());
    });
    EXPECT_EQ(Pitch(Letter::C, Accidental::QuadrupleFlat(), -128).ChromaticIndex(),
        ChromaticIndex(-1528));
    EXPECT_EQ(Pitch(Letter::B, Accidental::QuadrupleSharp(), 127).ChromaticIndex(),
        ChromaticIndex(1551));
}

// SPEC-OCT-3: the octave belongs to the letter: B#3 sounds as C4 and Cb4
// sounds as B3.
TEST(PitchTests, OctaveBelongsToTheLetter) {
    const Pitch bSharp3(Letter::B, Accidental::Sharp(), 3);
    const Pitch cFlat4(Letter::C, Accidental::Flat(), 4);
    EXPECT_EQ(bSharp3.Octave(), 3);
    EXPECT_EQ(cFlat4.Octave(), 4);
    EXPECT_EQ(bSharp3.ChromaticIndex(), Pitch(Letter::C, 4).ChromaticIndex());
    EXPECT_EQ(cFlat4.ChromaticIndex(), Pitch(Letter::B, 3).ChromaticIndex());
    EXPECT_EQ(Pitch(Letter::B, Accidental::QuadrupleSharp(), 3).ChromaticIndex(),
        ChromaticIndex(63));
    EXPECT_EQ(Pitch(Letter::C, Accidental::QuadrupleFlat(), 4).ChromaticIndex(),
        ChromaticIndex(56));
}

// SPEC-OCT-3, SPEC-ORD-2: diatonic movement changes octave between B and C
// and keeps the written accidental.
TEST(PitchTests, MovedDiatonicallyCrossesOctavesExhaustively) {
    for (int octave = -3; octave <= 3; ++octave) {
        for (const NoteName noteName : MCCTests::AllNoteNames()) {
            const Pitch pitch(noteName, octave);
            for (int steps = -22; steps <= 22; ++steps) {
                const Pitch moved = pitch.MovedDiatonically(steps);
                const int index = pitch.DiatonicIndex() + steps;
                ASSERT_TRUE(moved.IsValid());
                EXPECT_EQ(moved.DiatonicIndex(), index);
                EXPECT_EQ(moved.Accidental(), pitch.Accidental());
                EXPECT_EQ(moved.Octave(), index >= 0 ? index / 7 : -((-index + 6) / 7));
                EXPECT_EQ(moved.MovedDiatonically(-steps), pitch);
            }
        }
    }
    EXPECT_EQ(Pitch(Letter::B, Accidental::Sharp(), 3).MovedDiatonically(1),
        Pitch(Letter::C, Accidental::Sharp(), 4));
    EXPECT_EQ(Pitch(Letter::C, Accidental::Flat(), 4).MovedDiatonically(-1),
        Pitch(Letter::B, Accidental::Flat(), 3));
    EXPECT_EQ(Pitch(Letter::C, 4).MovedDiatonically(7), Pitch(Letter::C, 5));
    EXPECT_EQ(Pitch(Letter::C, 0).MovedDiatonically(-1), Pitch(Letter::B, -1));
}

// SPEC-OCT-4, SPEC-ERR-5: diatonic movement past octave -128 or 127 is
// invalid.
TEST(PitchTests, MovedDiatonicallyRejectsOctaveOverflow) {
    EXPECT_EQ(Pitch(Letter::A, 127).MovedDiatonically(1), Pitch(Letter::B, 127));
    EXPECT_FALSE(Pitch(Letter::B, 127).MovedDiatonically(1).IsValid());
    EXPECT_FALSE(Pitch(Letter::C, -128).MovedDiatonically(-1).IsValid());
    EXPECT_EQ(Pitch(Letter::C, -128).MovedDiatonically(1791), Pitch(Letter::B, 127));
    EXPECT_FALSE(Pitch(Letter::C, 4).MovedDiatonically(INT32_MAX).IsValid());
    EXPECT_FALSE(Pitch(Letter::C, 4).MovedDiatonically(INT32_MIN).IsValid());
}

// SPEC-OCT-4: octave movement keeps the spelling and is bounded.
TEST(PitchTests, MovedByOctavesIsBounded) {
    const Pitch cSharp4(Letter::C, Accidental::Sharp(), 4);
    EXPECT_EQ(cSharp4.MovedByOctaves(1), Pitch(Letter::C, Accidental::Sharp(), 5));
    EXPECT_EQ(cSharp4.MovedByOctaves(-132), Pitch(Letter::C, Accidental::Sharp(), -128));
    EXPECT_EQ(cSharp4.MovedByOctaves(123), Pitch(Letter::C, Accidental::Sharp(), 127));
    EXPECT_FALSE(cSharp4.MovedByOctaves(124).IsValid());
    EXPECT_FALSE(cSharp4.MovedByOctaves(-133).IsValid());
    EXPECT_FALSE(cSharp4.MovedByOctaves(INT32_MAX).IsValid());
    MCCTests::ForEachPitch([](Pitch pitch) {
        if (pitch.Octave() < 127) {
            EXPECT_EQ(pitch.MovedByOctaves(1).ChromaticIndex(),
                pitch.ChromaticIndex().Transposed(12));
        }
    });
}

// SPEC-ACC-3: alteration keeps letter and octave; outside +-4 it is invalid
// and never respelled, even across the octave boundary.
TEST(PitchTests, AlteredNeverRespells) {
    const Pitch bDoubleSharp3(Letter::B, Accidental::DoubleSharp(), 3);
    EXPECT_EQ(bDoubleSharp3.Altered(2), Pitch(Letter::B, Accidental::QuadrupleSharp(), 3));
    EXPECT_FALSE(bDoubleSharp3.Altered(3).IsValid());
    EXPECT_EQ(Pitch(Letter::C, 4).Altered(-4), Pitch(Letter::C, Accidental::QuadrupleFlat(), 4));
    EXPECT_FALSE(Pitch(Letter::C, 4).Altered(-5).IsValid());
    MCCTests::ForEachPitch([](Pitch pitch) {
        const Pitch altered = pitch.Altered(1);
        if (altered.IsValid()) {
            EXPECT_EQ(altered.Letter(), pitch.Letter());
            EXPECT_EQ(altered.Octave(), pitch.Octave());
            EXPECT_EQ(altered.ChromaticIndex(), pitch.ChromaticIndex().Transposed(1));
        } else {
            EXPECT_EQ(pitch.Accidental(), Accidental::QuadrupleSharp());
        }
    });
}
