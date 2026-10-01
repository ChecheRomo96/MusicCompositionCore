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
    print("  Read text, compute, write text:\n");
    print("    ParsePitch(\"F#3\") + ParseInterval(\"m3\")\n");
    print("    -> ");
    PrintValue(print, MCC::Notation::ParsePitch("F#3") + MCC::Notation::ParseInterval("m3"));
    print("   (F#3 up a minor third)\n\n");

    print("  Write a chord symbol:\n");
    print("    Format(text, size, Bb, Chords::Id::MajorNinth)\n");
    print("    -> ");
    char symbol[16];
    MCC::Notation::Format(symbol, sizeof(symbol),
        NoteName(Letter::B, MCC::Accidental::Flat()), MCC::Chords::Id::MajorNinth);
    print(symbol);
    print("\n\n");

    print("  Choose the accidental symbols (input \"bb3\" is B-flat 3):\n");
    const MCC::Pitch bFlat = MCC::Notation::ParsePitch("bb3");
    MCC::NotationOptions unicode;
    unicode.symbols = MCC::NotationSymbols::Unicode;
    char text[16];
    print("    ASCII   -> ");
    PrintValue(print, bFlat);
    print("\n    Unicode -> ");
    MCC::Notation::Format(text, sizeof(text), bFlat, unicode);
    print(text);
    print("   (UTF-8 in a char buffer)\n\n");

    print("  Write without a buffer, one character at a time:\n");
    print("    Format(sink, context, ParsePitch(\"eb5\"))\n");
    print("    -> ");
    // A sink receives each code point; here every one is ASCII.
    MCC::Notation::Format(
        [](uint32_t codePoint, void* context) {
            const char character[2] = {static_cast<char>(codePoint), '\0'};
            (*static_cast<PrintFunction*>(context))(character);
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
