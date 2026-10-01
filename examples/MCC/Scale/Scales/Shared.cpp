#include "Shared.h"

#include <MCC_Scale.h>

namespace MCCExamples::Scale::Scales {

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

void PrintScale(PrintFunction print, MCC::NoteName root, MCC::Scales::Id id) noexcept {
    char name[MCC::Scales::NameCapacity];
    MCC::Scales::CopyName(id, name, sizeof(name));
    const MCC::Scale scale = MCC::Scales::Make(root, id);
    print("  ");
    PrintNoteName(print, root);
    print(" ");
    print(name);
    print(": ");
    for (int degree = 1; degree <= scale.DegreeCount(); ++degree) {
        PrintNoteName(print, scale.NoteAt(degree));
        print(degree == scale.DegreeCount() ? "\n" : " ");
    }
}

} // namespace

void Run(PrintFunction print) noexcept {
    using MCC::Accidental;
    using MCC::Letter;
    using MCC::NoteName;
    namespace Scales = MCC::Scales;

    print("============================================================\n");
    print(" MCC :: Scale / Scales\n");
    print("============================================================\n\n");
    print("PURPOSE\n");
    print("  Spell catalog scales from any root; the catalog lives in\n");
    print("  program memory on AVR.\n\n");

    print("[1] SPELLING FOLLOWS THE PATTERN\n");
    print("------------------------------------------------------------\n");
    PrintScale(print, NoteName(Letter::E), Scales::Id::Major);
    PrintScale(print, NoteName(Letter::D), Scales::Id::Minor);
    PrintScale(print, NoteName(Letter::B, Accidental::Flat()), Scales::Id::Dorian);
    PrintScale(print, NoteName(Letter::A), Scales::Id::MinorBlues);
    print("\n");

    print("[2] WRITTEN VERSUS ENHARMONIC MEMBERSHIP\n");
    print("------------------------------------------------------------\n");
    const MCC::Scale eMajor = Scales::Make(NoteName(Letter::E), Scales::Id::Major);
    const NoteName aFlat(Letter::A, Accidental::Flat());
    print("  E Major contains Ab ........ ");
    print(eMajor.Contains(aFlat) ? "yes\n" : "no\n");
    print("  E Major sounds Ab .......... ");
    print(eMajor.ContainsPitchClass(aFlat.PitchClass()) ? "yes\n\n" : "no\n\n");

    print("[3] FIND BY NAME OR ALIAS\n");
    print("------------------------------------------------------------\n");
    const char* const queries[] = {"Aeolian", "Phrygian Dominant", "Bebop"};
    for (const char* query : queries) {
        char name[Scales::NameCapacity];
        const Scales::Id id = Scales::Find(query);
        Scales::CopyName(id, name, sizeof(name));
        print("  ");
        print(query);
        print(" -> ");
        print(id == Scales::Id::Invalid ? "(not in catalog)" : name);
        print("\n");
    }

    print("\n------------------------------------------------------------\n");
    print("TAKEAWAY\n");
    print("  Patterns store steps and semitones, so every root is spelled\n");
    print("  correctly; enharmonic checks are always explicit.\n");
    print("============================================================\n");
}

} // namespace MCCExamples::Scale::Scales
