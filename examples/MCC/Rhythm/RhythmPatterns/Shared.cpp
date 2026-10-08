#include "Shared.h"

#include <MCC_Rhythm.h>

namespace MCCExamples {
namespace Rhythm {
namespace RhythmPatterns {

namespace {

void Unsigned(uint16_t value, char* buffer) noexcept {
    char digits[6];
    int count = 0;
    do {
        digits[count++] = static_cast<char>('0' + value % 10u);
        value = static_cast<uint16_t>(value / 10u);
    } while (value != 0u);

    int length = 0;
    while (count > 0) {
        buffer[length++] = digits[--count];
    }
    buffer[length] = '\0';
}

// Box notation: `x` for an onset, `.` for a rest.
void Box(PrintFunction print, const MCC::RhythmPattern& pattern) noexcept {
    for (uint16_t i = 0u; i < pattern.StepCount(); ++i) {
        print(pattern.IsOnset(i) ? "x" : ".");
    }
}

// Interonset intervals: `3-3-4-2-4`.
void Intervals(PrintFunction print, const MCC::RhythmPattern& pattern) noexcept {
    char text[6];
    for (int32_t i = 0; i < pattern.OnsetCount(); ++i) {
        if (i != 0) {
            print("-");
        }
        Unsigned(static_cast<uint16_t>(pattern.InteronsetInterval(i)), text);
        print(text);
    }
}

void Row(PrintFunction print, const char* expression, const MCC::RhythmPattern& pattern) noexcept {
    char text[6];
    print("   ");
    print(expression);
    print("\n      ");
    if (!pattern.IsValid()) {
        print("invalid\n");
        return;
    }
    Box(print, pattern);
    print(" | steps: ");
    Unsigned(pattern.StepCount(), text);
    print(text);
    print(" | onsets: ");
    Unsigned(pattern.OnsetCount(), text);
    print(text);
    print(" | intervals: ");
    Intervals(print, pattern);
    print("\n");
}

} // namespace

void Run(PrintFunction print) noexcept {
    print("========================================\n");
    print(" MCC :: Rhythm / RhythmPatterns\n");
    print("========================================\n");
    print("\nPURPOSE\n");
    print("Describe cyclic onset patterns on a step grid, without timing.\n");

    const MCC::RhythmPattern son = MCC::RhythmPattern::FromString("x..x..x...x.x...");

    print("\n[1] BOX AND INTERVAL NOTATION\n\n");
    Row(print, "FromString(\"x..x..x...x.x...\")  // son clave", son);
    Row(print, "FromIntervals(\"3-3-2\")  // tresillo",
        MCC::RhythmPattern::FromIntervals("3-3-2"));
    Row(print, "FromIntervals(\"2-2-1-2-2-2-1\")  // bembe",
        MCC::RhythmPattern::FromIntervals("2-2-1-2-2-2-1"));

    print("\n[2] ROTATION AND NECKLACES\n\n");
    Row(print, "son.Rotated(8)  // 2-3 clave", son.Rotated(8));
    print("   son.Rotated(8).IsRotationOf(son): ");
    print(son.Rotated(8).IsRotationOf(son) ? "true\n" : "false\n");
    print("   rumba.IsRotationOf(son): ");
    print(MCC::RhythmPattern::FromIntervals("3-4-3-2-4").IsRotationOf(son)
        ? "true\n" : "false\n");

    print("\n[3] STEP COUNT CHOSEN AT RUNTIME\n\n");
    MCC::RhythmPattern pattern(12);
    pattern.SetOnset(0);
    pattern.SetOnset(5);
    Row(print, "RhythmPattern(12) + SetOnset(0), SetOnset(5)", pattern);
    pattern.Resize(48);
    pattern.SetOnset(40);
    Row(print, "Resize(48) + SetOnset(40)", pattern);
    pattern.Resize(20);
    pattern.Append(true);
    Row(print, "Resize(20) + Append(true)  // within capacity: no reallocation", pattern);
    char text[6];
    print("   Capacity(): ");
    Unsigned(pattern.Capacity(), text);
    print(text);
    print(" steps\n");

    print("\n[4] MEMORY HANDED IN BY THE CALLER\n\n");
    static uint8_t buffer[MCC::RhythmPattern::BytesFor(32)];
    MCC::RhythmPattern attached(buffer, sizeof buffer);
    attached.Parse("x..x...x..x.x...");
    attached.Rotate(8);
    Row(print, "RhythmPattern(buffer, 4) + Parse(rumba) + Rotate(8)", attached);
    print("   OwnsStorage(): ");
    print(attached.OwnsStorage() ? "true\n" : "false\n");
    print("   Resize(33): ");
    print(attached.Resize(33) ? "true\n" : "false (the buffer never grows)\n");

    print("\n[5] COMPLEMENT AND CONCATENATION\n\n");
    Row(print, "tresillo.Complement()",
        MCC::RhythmPattern::FromIntervals("3-3-2").Complement());
    Row(print, "tresillo.Concatenated(FromString(\"..x.x...\"))",
        MCC::RhythmPattern::FromIntervals("3-3-2").Concatenated(
            MCC::RhythmPattern::FromString("..x.x...")));

    print("\nTAKEAWAY\n");
    print("A pattern is structure only; MIDILAR decides when each step plays.\n");
    print("========================================\n");
}

} // namespace RhythmPatterns
} // namespace Rhythm
} // namespace MCCExamples
