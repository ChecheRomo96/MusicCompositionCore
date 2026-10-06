#include <gtest/gtest.h>

#include <MCC.h>

#include <stdint.h>
#include <string>
#include <utility>

using MCC::RhythmPattern;


TEST(RhythmPatternTests, ParsesBoxNotation) {
    const RhythmPattern tresillo = RhythmPattern::FromString("x..x..x.");
    EXPECT_TRUE(tresillo.IsValid());
    EXPECT_EQ(tresillo.StepCount(), 8u);
    EXPECT_TRUE(tresillo.IsOnset(0));
    EXPECT_TRUE(tresillo.IsOnset(3));
    EXPECT_TRUE(tresillo.IsOnset(6));
    EXPECT_EQ(tresillo.OnsetCount(), 3u);

    EXPECT_EQ(RhythmPattern::FromString("x . . x . . x ."), tresillo);
    EXPECT_EQ(RhythmPattern::FromString("X..X..X."), tresillo);
    EXPECT_EQ(RhythmPattern::FromString("x..x|..x."), tresillo);
    EXPECT_EQ(RhythmPattern::FromString("........").OnsetCount(), 0u);
    EXPECT_TRUE(RhythmPattern::FromString("........").IsValid());
}

TEST(RhythmPatternTests, RejectsMalformedBoxNotation) {
    EXPECT_EQ(RhythmPattern::FromString(nullptr), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromString(""), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromString("   "), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromString("x..o"), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromString("x-x"), RhythmPattern::Invalid());

    // The step count is limited only by MaximumSteps.
    const std::string longest(RhythmPattern::MaximumSteps, '.');
    EXPECT_EQ(RhythmPattern::FromString(longest.c_str()).StepCount(),
              RhythmPattern::MaximumSteps);
    const std::string tooLong(RhythmPattern::MaximumSteps + 1u, '.');
    EXPECT_EQ(RhythmPattern::FromString(tooLong.c_str()), RhythmPattern::Invalid());
}

TEST(RhythmPatternTests, ParsesInteronsetIntervals) {
    EXPECT_EQ(RhythmPattern::FromIntervals("3-3-2"), RhythmPattern::FromString("x..x..x."));
    EXPECT_EQ(RhythmPattern::FromIntervals("2-2-1-2-2-2-1"),
              RhythmPattern::FromString("x.x.xx.x.x.x"));
    EXPECT_EQ(RhythmPattern::FromIntervals("16"), RhythmPattern::FromString("x..............."));
    EXPECT_EQ(RhythmPattern::FromIntervals("32").StepCount(), 32u);
    EXPECT_EQ(RhythmPattern::FromIntervals("100-28").StepCount(), 128u);
    EXPECT_EQ(RhythmPattern::FromIntervals("65535").StepCount(), 65535u);

    EXPECT_EQ(RhythmPattern::FromIntervals(nullptr), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromIntervals(""), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromIntervals("3-0-2"), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromIntervals("3--2"), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromIntervals("3-2-"), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromIntervals("-3-2"), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromIntervals("3 3 2"), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromIntervals("65535-1"), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromIntervals("99999999999"), RhythmPattern::Invalid());
}

TEST(RhythmPatternTests, CreatesFromMask) {
    EXPECT_EQ(RhythmPattern::FromMask(0x49u, 8), RhythmPattern::FromString("x..x..x."));
    EXPECT_EQ(RhythmPattern::FromMask(0xFFFFFFFFul, 32).OnsetCount(), 32u);
    EXPECT_EQ(RhythmPattern::FromMask(0u, 1), RhythmPattern::FromString("."));

    EXPECT_EQ(RhythmPattern::FromMask(0u, 0), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromMask(0u, 33), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromMask(0u, -1), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromMask(0x100u, 8), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::FromMask(0x80000000ul, 32).OnsetStep(0), 31);
}

TEST(RhythmPatternTests, QueriesStepsCyclically) {
    const RhythmPattern son = RhythmPattern::FromString("x..x..x...x.x...");
    EXPECT_TRUE(son.IsOnset(0));
    EXPECT_FALSE(son.IsOnset(1));
    EXPECT_TRUE(son.IsOnset(12));
    EXPECT_TRUE(son.IsOnset(16));
    EXPECT_TRUE(son.IsOnset(19));
    EXPECT_TRUE(son.IsOnset(-4));
    EXPECT_FALSE(son.IsOnset(-1));
    EXPECT_FALSE(RhythmPattern::Invalid().IsOnset(0));

    EXPECT_EQ(son.OnsetStep(0), 0);
    EXPECT_EQ(son.OnsetStep(4), 12);
    EXPECT_EQ(son.OnsetStep(5), -1);
    EXPECT_EQ(son.OnsetStep(-1), -1);
}

TEST(RhythmPatternTests, ReportsInteronsetIntervals) {
    const RhythmPattern son = RhythmPattern::FromString("x..x..x...x.x...");
    const int32_t expected[] = {3, 3, 4, 2, 4};
    for (int32_t i = 0; i < 5; ++i) {
        EXPECT_EQ(son.InteronsetInterval(i), expected[i]);
    }
    EXPECT_EQ(son.InteronsetInterval(5), 0);

    // Wrapping from the last onset back to a first onset that is not step 0.
    const RhythmPattern reverse = son.Rotated(8);
    EXPECT_EQ(reverse.InteronsetInterval(4), 4);
    EXPECT_EQ(RhythmPattern::FromString("..x.....").InteronsetInterval(0), 8);
    EXPECT_EQ(RhythmPattern::FromString("........").InteronsetInterval(0), 0);
}

TEST(RhythmPatternTests, RotatesTheCycle) {
    const RhythmPattern son = RhythmPattern::FromString("x..x..x...x.x...");
    EXPECT_EQ(son.Rotated(0), son);
    EXPECT_EQ(son.Rotated(16), son);
    EXPECT_EQ(son.Rotated(8), RhythmPattern::FromString("..x.x...x..x..x."));
    EXPECT_EQ(son.Rotated(-8), son.Rotated(8));
    EXPECT_EQ(son.Rotated(3).Rotated(-3), son);

    const RhythmPattern rumba = RhythmPattern::FromString("x..x...x..x.x...");
    EXPECT_EQ(rumba.Rotated(8), RhythmPattern::FromString("..x.x...x..x...x"));

    // Toussaint ch. 7: the shiko started on its second onset.
    const RhythmPattern shiko = RhythmPattern::FromIntervals("4-2-4-2-4");
    EXPECT_EQ(shiko.Rotated(4), RhythmPattern::FromIntervals("2-4-2-4-4"));

    const RhythmPattern edges = RhythmPattern::FromMask(0x80000001ul, 32);
    EXPECT_EQ(edges.Rotated(1), RhythmPattern::FromMask(0xC0000000ul, 32));
    EXPECT_EQ(RhythmPattern::Invalid().Rotated(3), RhythmPattern::Invalid());
}

TEST(RhythmPatternTests, DetectsNecklaces) {
    const RhythmPattern son = RhythmPattern::FromString("x..x..x...x.x...");
    const RhythmPattern rumba = RhythmPattern::FromString("x..x...x..x.x...");
    for (int32_t shift = 0; shift < 16; ++shift) {
        EXPECT_TRUE(son.Rotated(shift).IsRotationOf(son));
        EXPECT_TRUE(son.IsRotationOf(son.Rotated(shift)));
    }
    EXPECT_FALSE(son.IsRotationOf(rumba));
    EXPECT_FALSE(RhythmPattern::FromString("x..x..x.").IsRotationOf(son));
    EXPECT_FALSE(RhythmPattern::Invalid().IsRotationOf(RhythmPattern::Invalid()));
    EXPECT_FALSE(son.IsRotationOf(RhythmPattern::Invalid()));
}

TEST(RhythmPatternTests, ComplementsAndConcatenates) {
    const RhythmPattern tresillo = RhythmPattern::FromString("x..x..x.");
    EXPECT_EQ(tresillo.Complement(), RhythmPattern::FromString(".xx.xx.x"));
    EXPECT_EQ(tresillo.Complement().Complement(), tresillo);
    EXPECT_EQ(RhythmPattern::FromMask(0u, 32).Complement().OnsetCount(), 32u);
    EXPECT_EQ(RhythmPattern::Invalid().Complement(), RhythmPattern::Invalid());

    EXPECT_EQ(RhythmPattern::FromString("x..x..x.").Concatenated(
                  RhythmPattern::FromString("..x.x...")),
              RhythmPattern::FromString("x..x..x...x.x..."));
    const RhythmPattern sixteen = RhythmPattern::FromString("x...............");
    const RhythmPattern thirtyThree =
        sixteen.Concatenated(sixteen).Concatenated(RhythmPattern::FromString("x"));
    EXPECT_EQ(thirtyThree.StepCount(), 33u);
    EXPECT_EQ(thirtyThree.OnsetCount(), 3u);
    EXPECT_EQ(thirtyThree.OnsetStep(2), 32);
    RhythmPattern longest(RhythmPattern::MaximumSteps);
    EXPECT_EQ(longest.Concatenated(RhythmPattern::FromString(".")), RhythmPattern::Invalid());
    EXPECT_EQ(tresillo.Concatenated(RhythmPattern::Invalid()), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern::Invalid().Concatenated(tresillo), RhythmPattern::Invalid());
}

TEST(RhythmPatternTests, InvalidStateIsCanonical) {
    const RhythmPattern invalid;
    EXPECT_FALSE(invalid.IsValid());
    EXPECT_EQ(invalid, RhythmPattern::Invalid());
    EXPECT_EQ(invalid.StepCount(), 0u);
    EXPECT_EQ(invalid.OnsetCount(), 0u);
    EXPECT_EQ(invalid.OnsetStep(0), -1);
    EXPECT_EQ(invalid.InteronsetInterval(0), 0);
    EXPECT_NE(invalid, RhythmPattern::FromString("."));
}

TEST(RhythmPatternTests, ChoosesTheStepCountAtRuntime) {
    for (int32_t steps : {1, 7, 31, 32, 33, 64, 128, 1000}) {
        RhythmPattern pattern(steps);
        EXPECT_TRUE(pattern.IsValid());
        EXPECT_EQ(pattern.StepCount(), static_cast<uint32_t>(steps));
        EXPECT_EQ(pattern.OnsetCount(), 0u);
    }
    EXPECT_EQ(RhythmPattern(0), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern(-3), RhythmPattern::Invalid());
    EXPECT_EQ(RhythmPattern(65536), RhythmPattern::Invalid());
}

TEST(RhythmPatternTests, EditsStepsAndResizes) {
    RhythmPattern pattern(8);
    EXPECT_TRUE(pattern.SetOnset(0));
    EXPECT_TRUE(pattern.SetOnset(3));
    EXPECT_TRUE(pattern.SetOnset(6));
    EXPECT_EQ(pattern, RhythmPattern::FromString("x..x..x."));
    EXPECT_TRUE(pattern.SetOnset(3, false));
    EXPECT_EQ(pattern, RhythmPattern::FromString("x.....x."));
    EXPECT_FALSE(pattern.SetOnset(8));
    EXPECT_FALSE(pattern.SetOnset(-1));

    // Growing keeps every step and adds rests.
    EXPECT_TRUE(pattern.Resize(48));
    EXPECT_EQ(pattern.StepCount(), 48u);
    EXPECT_TRUE(pattern.SetOnset(47));
    EXPECT_EQ(pattern.OnsetCount(), 3u);
    EXPECT_TRUE(pattern.IsOnset(-1));

    // Shrinking drops the removed steps.
    EXPECT_TRUE(pattern.Resize(4));
    EXPECT_EQ(pattern, RhythmPattern::FromString("x..."));

    EXPECT_FALSE(pattern.Resize(0));
    EXPECT_FALSE(pattern.Resize(65536));
    EXPECT_EQ(pattern, RhythmPattern::FromString("x..."));

    RhythmPattern invalid;
    EXPECT_FALSE(invalid.SetOnset(0));
    EXPECT_TRUE(invalid.Resize(3));
    EXPECT_EQ(invalid, RhythmPattern::FromString("..."));
}

TEST(RhythmPatternTests, CopiesAndMovesLongPatterns) {
    // A 128-step pattern, the length of the longest Indian talas.
    RhythmPattern tala(128);
    for (int32_t step = 0; step < 128; step += 5) {
        tala.SetOnset(step);
    }
    RhythmPattern copy(tala);
    EXPECT_EQ(copy, tala);
    copy.SetOnset(1);
    EXPECT_NE(copy, tala);
    EXPECT_FALSE(tala.IsOnset(1));

    RhythmPattern assigned = RhythmPattern::FromString("x.");
    assigned = tala;
    EXPECT_EQ(assigned, tala);
    assigned = RhythmPattern::FromString("x.");
    EXPECT_EQ(assigned, RhythmPattern::FromString("x."));

    RhythmPattern moved(std::move(copy));
    EXPECT_EQ(moved.StepCount(), 128u);
    EXPECT_FALSE(copy.IsValid());
    copy = std::move(moved);
    EXPECT_EQ(copy.StepCount(), 128u);
    EXPECT_FALSE(moved.IsValid());

    RhythmPattern& self = copy;
    copy = self;
    EXPECT_EQ(copy.StepCount(), 128u);

    EXPECT_EQ(tala.Rotated(5).Rotated(-5), tala);
    EXPECT_TRUE(tala.Rotated(37).IsRotationOf(tala));
    EXPECT_EQ(tala.Complement().Complement(), tala);
    EXPECT_EQ(tala.Complement().OnsetCount(), 128u - tala.OnsetCount());
}

TEST(RhythmPatternTests, KeepsCapacityLikeAVector) {
    EXPECT_EQ(RhythmPattern().Capacity(), 0u);

    // Capacity is whole bytes: 33 steps need 5 bytes, so 40 steps fit.
    RhythmPattern pattern(33);
    EXPECT_TRUE(pattern.OwnsStorage());
    EXPECT_EQ(pattern.Capacity(), 40u);
    EXPECT_TRUE(pattern.Resize(40));
    EXPECT_EQ(pattern.Capacity(), 40u);

    // Shrinking keeps the capacity and clears the removed steps, so growing
    // again within it adds rests.
    EXPECT_TRUE(pattern.SetOnset(39));
    EXPECT_TRUE(pattern.Resize(10));
    EXPECT_EQ(pattern.Capacity(), 40u);
    EXPECT_TRUE(pattern.Resize(40));
    EXPECT_FALSE(pattern.IsOnset(39));

    // Growing past the capacity reallocates; how much is the vector's choice.
    EXPECT_TRUE(pattern.Resize(41));
    EXPECT_GE(pattern.Capacity(), 48u);
    EXPECT_EQ(pattern.Capacity() % 8u, 0u);

    EXPECT_TRUE(pattern.Resize(12));
    EXPECT_TRUE(pattern.ShrinkToFit());
    EXPECT_EQ(pattern.Capacity(), 16u);
    EXPECT_EQ(pattern.StepCount(), 12u);

    pattern.Release();
    EXPECT_FALSE(pattern.IsValid());
    EXPECT_EQ(pattern.Capacity(), 0u);
    EXPECT_FALSE(pattern.OwnsStorage());
}

TEST(RhythmPatternTests, ReservesWithoutChangingThePattern) {
    RhythmPattern pattern = RhythmPattern::FromString("x..x..x.");
    EXPECT_EQ(pattern.Capacity(), 8u);
    EXPECT_TRUE(pattern.Reserve(1000));
    EXPECT_EQ(pattern.Capacity(), 1000u);
    EXPECT_EQ(pattern, RhythmPattern::FromString("x..x..x."));
    EXPECT_TRUE(pattern.Reserve(10));
    EXPECT_EQ(pattern.Capacity(), 1000u);

    EXPECT_TRUE(pattern.Reserve(RhythmPattern::MaximumSteps));
    EXPECT_EQ(pattern.Capacity(), RhythmPattern::MaximumSteps);
    EXPECT_FALSE(pattern.Reserve(-1));
    EXPECT_FALSE(pattern.Reserve(65536));

    // Copies hold only what their steps need.
    const RhythmPattern copy(pattern);
    EXPECT_EQ(copy.Capacity(), 8u);
    EXPECT_EQ(copy, pattern);

    RhythmPattern invalid;
    EXPECT_TRUE(invalid.Reserve(100));
    EXPECT_FALSE(invalid.IsValid());
    EXPECT_EQ(invalid.Capacity(), 104u);
}

TEST(RhythmPatternTests, AppendsStepsGrowingGeometrically) {
    RhythmPattern pattern;
    const char* clave = "x..x..x...x.x...";
    for (const char* c = clave; *c != '\0'; ++c) {
        EXPECT_TRUE(pattern.Append(*c == 'x'));
    }
    EXPECT_EQ(pattern, RhythmPattern::FromString(clave));
    EXPECT_EQ(pattern.Capacity(), 16u);  // 8 -> 16

    int32_t reallocations = 0;
    uint16_t capacity = pattern.Capacity();
    while (pattern.StepCount() < 1000u) {
        EXPECT_TRUE(pattern.Append(pattern.StepCount() % 3u == 0u));
        if (pattern.Capacity() != capacity) {
            ++reallocations;
            EXPECT_EQ(pattern.Capacity(), static_cast<uint32_t>(capacity) * 2u);
            capacity = pattern.Capacity();
        }
    }
    EXPECT_EQ(reallocations, 6);  // 16 -> 32 -> ... -> 1024
    EXPECT_TRUE(pattern.IsOnset(999));
    EXPECT_TRUE(pattern.IsOnset(0));

    RhythmPattern longest(RhythmPattern::MaximumSteps);
    EXPECT_FALSE(longest.Append(true));
    EXPECT_EQ(longest.StepCount(), RhythmPattern::MaximumSteps);

    RhythmPattern almost(RhythmPattern::MaximumSteps - 1);
    EXPECT_TRUE(almost.Append(true));
    EXPECT_TRUE(almost.IsOnset(-1));
}

TEST(RhythmPatternTests, AppendsPatternsInPlace) {
    RhythmPattern pattern = RhythmPattern::FromString("x..x..x.");
    EXPECT_TRUE(pattern.Append(RhythmPattern::FromString("..x.x...")));
    EXPECT_EQ(pattern, RhythmPattern::FromString("x..x..x...x.x..."));

    RhythmPattern twice = RhythmPattern::FromString("x..");
    EXPECT_TRUE(twice.Append(twice));
    EXPECT_EQ(twice, RhythmPattern::FromString("x..x.."));

    RhythmPattern empty;
    EXPECT_TRUE(empty.Append(RhythmPattern::FromString("x.")));
    EXPECT_EQ(empty, RhythmPattern::FromString("x."));
    EXPECT_FALSE(empty.Append(RhythmPattern::Invalid()));
}

TEST(RhythmPatternTests, RotatesAndInvertsInPlace) {
    RhythmPattern son = RhythmPattern::FromString("x..x..x...x.x...");
    const RhythmPattern original(son);
    for (int32_t shift = -20; shift <= 20; ++shift) {
        RhythmPattern rotated(original);
        EXPECT_TRUE(rotated.Rotate(shift));
        EXPECT_EQ(rotated, original.Rotated(shift));
        // Reference: step i of the result is step i + shift of the source.
        for (int32_t i = 0; i < 16; ++i) {
            EXPECT_EQ(rotated.IsOnset(i), original.IsOnset(i + shift));
        }
    }
    EXPECT_TRUE(son.Rotate(8));
    EXPECT_EQ(son, RhythmPattern::FromString("..x.x...x..x..x."));

    RhythmPattern odd = RhythmPattern::FromString("x.xx.xx.x.x");
    EXPECT_TRUE(odd.Invert());
    EXPECT_EQ(odd, RhythmPattern::FromString(".x..x..x.x."));
    EXPECT_EQ(odd.OnsetCount(), 4u);

    RhythmPattern invalid;
    EXPECT_FALSE(invalid.Rotate(1));
    EXPECT_FALSE(invalid.Invert());
}

TEST(RhythmPatternTests, UsesAnAttachedBufferWithoutAllocating) {
    uint8_t buffer[RhythmPattern::BytesFor(64)];
    buffer[0] = 0xFFu;
    RhythmPattern pattern(buffer, sizeof buffer);
    EXPECT_FALSE(pattern.OwnsStorage());
    EXPECT_FALSE(pattern.IsValid());
    EXPECT_EQ(pattern.Capacity(), 64u);

    EXPECT_TRUE(pattern.Parse("x..x..x...x.x..."));
    EXPECT_EQ(pattern, RhythmPattern::FromString("x..x..x...x.x..."));
    EXPECT_EQ(buffer[0], 0x49u);  // steps 0, 3 and 6 overwrite the old 0xFF
    EXPECT_TRUE(pattern.ParseIntervals("3-3-2"));
    EXPECT_EQ(pattern, RhythmPattern::FromString("x..x..x."));

    // Everything stays inside the buffer.
    EXPECT_TRUE(pattern.Resize(64));
    EXPECT_TRUE(pattern.Rotate(3));
    EXPECT_TRUE(pattern.Invert());
    EXPECT_TRUE(pattern.Invert());
    EXPECT_TRUE(pattern.Resize(8));
    EXPECT_TRUE(pattern.Append(RhythmPattern::FromString("..x.x...")));
    EXPECT_EQ(pattern.StepCount(), 16u);
    EXPECT_TRUE(pattern.ShrinkToFit());
    EXPECT_EQ(pattern.Capacity(), 64u);
    EXPECT_FALSE(pattern.OwnsStorage());

    // The buffer never grows: anything larger fails and changes nothing.
    const RhythmPattern before(pattern);
    EXPECT_FALSE(pattern.Resize(65));
    EXPECT_FALSE(pattern.Reserve(65));
    EXPECT_FALSE(pattern.Parse(std::string(65, 'x').c_str()));
    EXPECT_FALSE(pattern.Append(RhythmPattern(49)));
    EXPECT_EQ(pattern, before);

    pattern.Resize(64);
    EXPECT_FALSE(pattern.Append(true));
    EXPECT_EQ(pattern.StepCount(), 64u);
}

TEST(RhythmPatternTests, AssignsIntoAnAttachedBuffer) {
    uint8_t buffer[2];
    RhythmPattern pattern(buffer, sizeof buffer);

    pattern = RhythmPattern::FromString("x..x..x...x.x...");  // move: copies in
    EXPECT_FALSE(pattern.OwnsStorage());
    EXPECT_EQ(buffer[0], 0x49u);

    const RhythmPattern tresillo = RhythmPattern::FromString("x..x..x.");
    pattern = tresillo;  // copy: copies in
    EXPECT_FALSE(pattern.OwnsStorage());
    EXPECT_EQ(pattern, tresillo);

    pattern = RhythmPattern(17);  // does not fit: unchanged
    EXPECT_EQ(pattern, tresillo);
    EXPECT_FALSE(pattern.OwnsStorage());

    // Moving an attached pattern hands over the buffer.
    RhythmPattern moved(std::move(pattern));
    EXPECT_FALSE(moved.OwnsStorage());
    EXPECT_EQ(moved, tresillo);
    EXPECT_EQ(pattern.Capacity(), 0u);

    // Copies of an attached pattern own their storage.
    RhythmPattern copy(moved);
    EXPECT_TRUE(copy.OwnsStorage());
    EXPECT_EQ(copy, moved);

    // Results of value-returning operations own their storage.
    EXPECT_TRUE(moved.Rotated(1).OwnsStorage());

    moved.Release();
    EXPECT_EQ(moved.Capacity(), 0u);
    EXPECT_EQ(buffer[0], 0x49u);  // releasing leaves the buffer as it is
}

TEST(RhythmPatternTests, UsesEveryNonNullBuffer) {
    uint8_t buffer[4];
    RhythmPattern pattern;
    EXPECT_TRUE(pattern.Attach(buffer, 0));  // a non-null buffer is used, even empty
    EXPECT_EQ(pattern.Capacity(), 0u);
    EXPECT_FALSE(pattern.Resize(1));
    EXPECT_TRUE(pattern.Attach(nullptr, 4));  // null: back to owned storage
    EXPECT_TRUE(pattern.Resize(4));
    EXPECT_TRUE(pattern.OwnsStorage());

    RhythmPattern owned(8);
    EXPECT_TRUE(owned.Attach(buffer, sizeof buffer));  // frees its heap storage
    EXPECT_FALSE(owned.OwnsStorage());
    EXPECT_EQ(owned.Capacity(), 32u);

    // A huge buffer is capped at the bytes MaximumSteps needs.
    static uint8_t huge[10000];
    RhythmPattern large(huge, sizeof huge);
    EXPECT_EQ(large.Capacity(), RhythmPattern::MaximumSteps);
    EXPECT_TRUE(large.Resize(RhythmPattern::MaximumSteps));
}
