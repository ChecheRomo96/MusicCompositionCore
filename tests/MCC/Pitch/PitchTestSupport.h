#ifndef MCC_TESTS_PITCH_TEST_SUPPORT_H
#define MCC_TESTS_PITCH_TEST_SUPPORT_H

#include <MCC.h>

#include <array>

namespace MCCTests {

constexpr std::array<MCC::Letter, 7> AllLetters = {
    MCC::Letter::C, MCC::Letter::D, MCC::Letter::E, MCC::Letter::F,
    MCC::Letter::G, MCC::Letter::A, MCC::Letter::B};

constexpr std::array<int, 7> NaturalSemitones = {0, 2, 4, 5, 7, 9, 11};

// Every supported accidental in ascending order (SPEC-ACC-1).
inline std::array<MCC::Accidental, 9> AllAccidentals() {
    std::array<MCC::Accidental, 9> accidentals{};
    for (int i = 0; i < 9; ++i) {
        accidentals[i] = MCC::Accidental(i - 4);
    }
    return accidentals;
}

// The 63 supported spellings in written order: letter, then accidental.
inline std::array<MCC::NoteName, 63> AllNoteNames() {
    std::array<MCC::NoteName, 63> noteNames{};
    int i = 0;
    for (const MCC::Letter letter : AllLetters) {
        for (const MCC::Accidental accidental : AllAccidentals()) {
            noteNames[i++] = MCC::NoteName(letter, accidental);
        }
    }
    return noteNames;
}

inline int ExpectedPitchClass(MCC::NoteName noteName) {
    const int semitones =
        NaturalSemitones[MCC::DiatonicIndex(noteName.Letter())] +
        noteName.Accidental().Semitones();
    return ((semitones % 12) + 12) % 12;
}

// Calls `visit(pitch)` for every writable pitch: 7 letters x 9 accidentals x
// 256 octaves, in written order.
template <typename Visitor>
void ForEachPitch(Visitor visit) {
    for (int octave = -128; octave <= 127; ++octave) {
        for (const MCC::NoteName noteName : AllNoteNames()) {
            visit(MCC::Pitch(noteName, octave));
        }
    }
}

inline int ExpectedChromaticIndex(MCC::Pitch pitch) {
    return (pitch.Octave() + 1) * 12 +
        NaturalSemitones[MCC::DiatonicIndex(pitch.Letter())] +
        pitch.Accidental().Semitones();
}

} // namespace MCCTests

#endif // MCC_TESTS_PITCH_TEST_SUPPORT_H
