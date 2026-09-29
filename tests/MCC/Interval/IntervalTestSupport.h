#ifndef MCC_TESTS_INTERVAL_TEST_SUPPORT_H
#define MCC_TESTS_INTERVAL_TEST_SUPPORT_H

#include <MCC.h>

#include <vector>

namespace MCCTests {

// A named simple ascending interval with its expected steps and semitones.
struct SimpleInterval {
    const char* name;
    MCC::IntervalQuality quality;
    int number;
    int steps;
    int semitones;
};

// Every common simple interval from P1 to A8 (SPEC-INT-1, SPEC-INT-4).
inline std::vector<SimpleInterval> CommonSimpleIntervals() {
    using Q = MCC::IntervalQuality;
    return {
        {"P1", Q::Perfect(), 1, 0, 0},     {"A1", Q::Augmented(), 1, 0, 1},
        {"d2", Q::Diminished(), 2, 1, 0},  {"m2", Q::Minor(), 2, 1, 1},
        {"M2", Q::Major(), 2, 1, 2},       {"A2", Q::Augmented(), 2, 1, 3},
        {"d3", Q::Diminished(), 3, 2, 2},  {"m3", Q::Minor(), 3, 2, 3},
        {"M3", Q::Major(), 3, 2, 4},       {"A3", Q::Augmented(), 3, 2, 5},
        {"d4", Q::Diminished(), 4, 3, 4},  {"P4", Q::Perfect(), 4, 3, 5},
        {"A4", Q::Augmented(), 4, 3, 6},   {"d5", Q::Diminished(), 5, 4, 6},
        {"P5", Q::Perfect(), 5, 4, 7},     {"A5", Q::Augmented(), 5, 4, 8},
        {"d6", Q::Diminished(), 6, 5, 7},  {"m6", Q::Minor(), 6, 5, 8},
        {"M6", Q::Major(), 6, 5, 9},       {"A6", Q::Augmented(), 6, 5, 10},
        {"d7", Q::Diminished(), 7, 6, 9},  {"m7", Q::Minor(), 7, 6, 10},
        {"M7", Q::Major(), 7, 6, 11},      {"A7", Q::Augmented(), 7, 6, 12},
        {"d8", Q::Diminished(), 8, 7, 11}, {"P8", Q::Perfect(), 8, 7, 12},
        {"A8", Q::Augmented(), 8, 7, 13},
    };
}

// Every valid quality: P, M, m and augmented/diminished 1-4 times.
inline std::vector<MCC::IntervalQuality> AllQualities() {
    std::vector<MCC::IntervalQuality> qualities = {
        MCC::IntervalQuality::Perfect(), MCC::IntervalQuality::Major(),
        MCC::IntervalQuality::Minor()};
    for (int count = 1; count <= 4; ++count) {
        qualities.push_back(MCC::IntervalQuality::Augmented(count));
        qualities.push_back(MCC::IntervalQuality::Diminished(count));
    }
    return qualities;
}

// Every valid interval with up to `maxSteps` steps, in both directions.
inline std::vector<MCC::Interval> AllIntervals(int maxSteps) {
    std::vector<MCC::Interval> intervals;
    for (int steps = -maxSteps; steps <= maxSteps; ++steps) {
        for (int semitones = -4 * maxSteps - 20; semitones <= 4 * maxSteps + 20;
             ++semitones) {
            const MCC::Interval interval = MCC::Interval::FromSteps(steps, semitones);
            if (interval.IsValid()) {
                intervals.push_back(interval);
            }
        }
    }
    return intervals;
}

// A spread of pitches: every spelling in octaves 2-5.
inline std::vector<MCC::Pitch> SamplePitches() {
    std::vector<MCC::Pitch> pitches;
    for (int octave = 2; octave <= 5; ++octave) {
        for (int letter = 0; letter < 7; ++letter) {
            for (int accidental = -4; accidental <= 4; ++accidental) {
                pitches.emplace_back(static_cast<MCC::Letter>(letter),
                    MCC::Accidental(accidental), octave);
            }
        }
    }
    return pitches;
}

inline std::vector<MCC::NoteName> AllNoteNames() {
    std::vector<MCC::NoteName> noteNames;
    for (int letter = 0; letter < 7; ++letter) {
        for (int accidental = -4; accidental <= 4; ++accidental) {
            noteNames.emplace_back(static_cast<MCC::Letter>(letter),
                MCC::Accidental(accidental));
        }
    }
    return noteNames;
}

} // namespace MCCTests

#endif // MCC_TESTS_INTERVAL_TEST_SUPPORT_H
