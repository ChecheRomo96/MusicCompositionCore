#include <gtest/gtest.h>

#include "PitchTestSupport.h"

#ifndef MCC_PITCH
    #error "MCC.h must expose MCC_PITCH when the Pitch facade is available"
#endif

using MCC::Letter;
using MCCTests::AllLetters;
using MCCTests::NaturalSemitones;

// SPEC-ORD-1: letters are ordered C D E F G A B with indices 0-6.
TEST(LetterTests, DiatonicIndicesFollowLetterOrder) {
    EXPECT_EQ(MCC::LetterCount, 7);
    for (int i = 0; i < 7; ++i) {
        EXPECT_EQ(MCC::DiatonicIndex(AllLetters[static_cast<std::size_t>(i)]), i);
    }
    EXPECT_LT(Letter::C, Letter::D);
    EXPECT_LT(Letter::A, Letter::B);
}

// SPEC-ORD-1: natural semitone offsets are 0 2 4 5 7 9 11.
TEST(LetterTests, NaturalSemitonesMatchSpecification) {
    for (int i = 0; i < 7; ++i) {
        EXPECT_EQ(MCC::NaturalSemitone(AllLetters[static_cast<std::size_t>(i)]),
                  NaturalSemitones[static_cast<std::size_t>(i)]);
    }
}

// SPEC-ORD-1: letter movement wraps around the seven letters.
TEST(LetterTests, MoveLetterWrapsInBothDirections) {
    for (int from = 0; from < 7; ++from) {
        for (int steps = -30; steps <= 30; ++steps) {
            const int expected = (((from + steps) % 7) + 7) % 7;
            EXPECT_EQ(MCC::MoveLetter(AllLetters[static_cast<std::size_t>(from)], steps),
                AllLetters[static_cast<std::size_t>(expected)])
                << "from " << from << " steps " << steps;
        }
    }
    EXPECT_EQ(MCC::MoveLetter(Letter::B, 1), Letter::C);
    EXPECT_EQ(MCC::MoveLetter(Letter::C, -1), Letter::B);
}
