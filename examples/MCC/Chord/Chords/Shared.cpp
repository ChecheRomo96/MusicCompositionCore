#include "Shared.h"

#include <MCC_Chord.h>
#include <MCC_Scale.h>

namespace MCCExamples::Chord::Chords {

namespace {

// MCC has no text formatting yet (Phase 8), so the example spells note names
// ("G#", "Bb") itself.
constexpr char LetterNames[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};

void PrintNoteName(PrintFunction print, MCC::NoteName noteName) noexcept {
    char buffer[8];
    int length = 0;
    buffer[length++] = LetterNames[MCC::DiatonicIndex(noteName.Letter())];
    const int semitones = noteName.Accidental().Semitones();
    for (int i = 0; i < (semitones > 0 ? semitones : -semitones); ++i) {
        buffer[length++] = semitones > 0 ? '#' : 'b';
    }
    buffer[length] = '\0';
    print(buffer);
}

void PrintSymbol(PrintFunction print, MCC::NoteName root, MCC::Chords::Id id) noexcept {
    char symbol[MCC::Chords::SymbolCapacity];
    MCC::Chords::CopySymbol(id, symbol, sizeof(symbol));
    PrintNoteName(print, root);
    print(symbol);
}

void PrintChord(PrintFunction print, MCC::NoteName root, MCC::Chords::Id id) noexcept {
    const MCC::Chord chord = MCC::Chords::Make(root, id);
    print("  ");
    PrintSymbol(print, root, id);
    print(": ");
    for (int tone = 1; tone <= chord.ToneCount(); ++tone) {
        PrintNoteName(print, chord.ToneAt(tone));
        print(tone == chord.ToneCount() ? "\n" : " ");
    }
}

} // namespace

void Run(PrintFunction print) noexcept {
    using MCC::Letter;
    using MCC::NoteName;
    namespace Chords = MCC::Chords;

    print("============================================================\n");
    print(" MCC :: Chord / Chords\n");
    print("============================================================\n\n");
    print("PURPOSE\n");
    print("  Spell catalog chords, voice their inversions and list the\n");
    print("  chords that belong to a scale.\n\n");

    print("[1] SPELLING FOLLOWS THE PATTERN\n");
    print("------------------------------------------------------------\n");
    PrintChord(print, NoteName(Letter::E), Chords::Id::DominantNinth);
    PrintChord(print, NoteName(Letter::B), Chords::Id::HalfDiminishedSeventh);
    PrintChord(print, NoteName(Letter::C, MCC::Accidental::Sharp()), Chords::Id::DiminishedSeventh);
    print("\n");

    print("[2] INVERSIONS IN CLOSE POSITION\n");
    print("------------------------------------------------------------\n");
    const MCC::Chord cMajor = Chords::Make(NoteName(Letter::C), Chords::Id::Major);
    for (int inversion = 0; inversion < 3; ++inversion) {
        MCC::Pitch pitches[3];
        cMajor.Voicing(inversion, 4, pitches, 3);
        print(inversion == 0 ? "  Root position: " : (inversion == 1 ? "  First:         " : "  Second:        "));
        for (const MCC::Pitch& pitch : pitches) {
            PrintNoteName(print, pitch.NoteName());
            const char octave[] = {static_cast<char>('0' + pitch.Octave()), ' ', '\0'};
            print(octave);
        }
        print("\n");
    }
    print("\n");

    print("[3] SEVENTH CHORDS OF C MAJOR\n");
    print("------------------------------------------------------------\n");
    const MCC::Scale cMajorScale =
        MCC::Scales::Make(NoteName(Letter::C), MCC::Scales::Id::Major);
    Chords::ScaleChord pool[64];
    const size_t count = Chords::FromScale(cMajorScale, pool, 64);
    print(" ");
    for (size_t i = 0; i < count && i < 64; ++i) {
        const Chords::Id id = pool[i].id;
        if (id == Chords::Id::MajorSeventh || id == Chords::Id::MinorSeventh ||
            id == Chords::Id::DominantSeventh || id == Chords::Id::HalfDiminishedSeventh) {
            print(" ");
            PrintSymbol(print, cMajorScale.NoteAt(pool[i].degree), id);
        }
    }
    print("\n");

    print("\n------------------------------------------------------------\n");
    print("TAKEAWAY\n");
    print("  Chord patterns keep their written numbers, so every root and\n");
    print("  every extension is spelled correctly; FromScale rebuilds the\n");
    print("  historical chord pool without guessing.\n");
    print("============================================================\n");
}

} // namespace MCCExamples::Chord::Chords
