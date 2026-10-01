#include "Shared.h"

#include <MCC_Chord.h>
#include <MCC_Key.h>
#include <MCC_Notation.h>
#include <MCC_Scale.h>

namespace MCCExamples::Key::Keys {

namespace {

template <typename T>
void PrintValue(PrintFunction print, T value) noexcept {
    char text[32];
    MCC::Notation::Format(text, sizeof(text), value);
    print(text);
}

} // namespace

void Run(PrintFunction print) noexcept {
    using MCC::KeyMode;
    using MCC::Letter;
    using MCC::NoteName;

    print("============================================================\n");
    print(" MCC :: Key / Keys\n");
    print("============================================================\n\n");
    print("PURPOSE\n");
    print("  Derive key signatures, spell notes in a key and format\n");
    print("  music as text without allocating.\n\n");

    print("[1] KEY SIGNATURES\n");
    print("------------------------------------------------------------\n");
    const MCC::Key keys[] = {
        MCC::Key(NoteName(Letter::E), KeyMode::Minor),
        MCC::Key(NoteName(Letter::B, MCC::Accidental::Flat()), KeyMode::Major),
        MCC::Key(NoteName(Letter::F, MCC::Accidental::Sharp()), KeyMode::Dorian),
        MCC::Key::FromSignature(MCC::KeySignature(-4), KeyMode::Minor),
    };
    for (const MCC::Key& key : keys) {
        print("  ");
        PrintValue(print, key);
        const MCC::KeySignature signature = key.Signature();
        char count[2] = {static_cast<char>('0' + signature.Sharps() + signature.Flats()), '\0'};
        print(": ");
        print(count);
        const bool one = signature.Sharps() + signature.Flats() == 1;
        print(signature.Fifths() > 0 ? (one ? " sharp\n" : " sharps\n")
            : signature.Fifths() < 0 ? (one ? " flat\n" : " flats\n") : " accidentals\n");
    }
    print("\n");

    print("[2] THE SAME SOUNDS SPELLED IN TWO KEYS\n");
    print("------------------------------------------------------------\n");
    const MCC::Key eMajor(NoteName(Letter::E), KeyMode::Major);
    const MCC::Key aFlatMajor(NoteName(Letter::A, MCC::Accidental::Flat()), KeyMode::Major);
    print("  Chromatic 60-67 in E major:  ");
    for (int index = 60; index <= 67; ++index) {
        PrintValue(print, eMajor.Spell(MCC::ChromaticIndex(index)));
        print(" ");
    }
    print("\n  Chromatic 60-67 in Ab major: ");
    for (int index = 60; index <= 67; ++index) {
        PrintValue(print, aFlatMajor.Spell(MCC::ChromaticIndex(index)));
        print(" ");
    }
    print("\n\n");

    print("[3] TEXT IN, TEXT OUT\n");
    print("------------------------------------------------------------\n");
    const MCC::Pitch parsed = MCC::Notation::ParsePitch("F#3");
    const MCC::Interval third = MCC::Notation::ParseInterval("m3");
    print("  F#3 + m3 ............... ");
    PrintValue(print, parsed + third);
    print("\n  Chord on Bb ............ ");
    char symbol[16];
    MCC::Notation::Format(symbol, sizeof(symbol),
        NoteName(Letter::B, MCC::Accidental::Flat()), MCC::Chords::Id::MajorNinth);
    print(symbol);
    print("\n  Unicode ................ ");
    MCC::NotationOptions unicode;
    unicode.symbols = MCC::NotationSymbols::Unicode;
    char text[16];
    MCC::Notation::Format(text, sizeof(text), parsed + third, unicode);
    print(text);
    print("\n  Straight to the output .. ");
    // A sink writes code points without a buffer; here they are ASCII.
    MCC::Notation::Format(
        [](uint32_t codePoint, void* context) {
            const char text[2] = {static_cast<char>(codePoint), '\0'};
            (*static_cast<PrintFunction*>(context))(text);
        },
        &print, MCC::Notation::ParsePitch("eb5"));
    print("\n");

    print("\n------------------------------------------------------------\n");
    print("TAKEAWAY\n");
    print("  A key decides spelling: the same sounds read as sharps in\n");
    print("  E major and as flats in Ab major.\n");
    print("============================================================\n");
}

} // namespace MCCExamples::Key::Keys
