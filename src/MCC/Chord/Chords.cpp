#include <MCC/Chord/Chords.h>

#include <Foundation/Utils/Flash.h>

namespace MCC {
namespace Chords {

namespace {

    using Foundation::Utils::Flash::CopyString;
    using Foundation::Utils::Flash::Read;

    struct Entry {
        ChordPattern pattern;
        char symbol[SymbolCapacity];
        char name[NameCapacity];
    };

    struct Alias {
        Id target;
        char name[NameCapacity];
    };

    // Reviewed definitions; provenance is recorded in Chord.dox. Chord
    // formulas are evaluated at compile time into eight-byte patterns.
    constexpr Entry Catalog[Count] FOUNDATION_FLASH = {
        {ChordPattern::FromFormula("1 3 5"), "", "Major"},
        {ChordPattern::FromFormula("1 b3 5"), "m", "Minor"},
        {ChordPattern::FromFormula("1 3 #5"), "aug", "Augmented"},
        {ChordPattern::FromFormula("1 b3 b5"), "dim", "Diminished"},
        {ChordPattern::FromFormula("1 3 5 6"), "6", "Sixth"},
        {ChordPattern::FromFormula("1 b3 5 6"), "m6", "Minor Sixth"},
        {ChordPattern::FromFormula("1 3 5 b7"), "7", "Dominant Seventh"},
        {ChordPattern::FromFormula("1 3 5 7"), "maj7", "Major Seventh"},
        {ChordPattern::FromFormula("1 b3 5 b7"), "m7", "Minor Seventh"},
        {ChordPattern::FromFormula("1 b3 b5 b7"), "m7b5", "Half Diminished Seventh"},
        {ChordPattern::FromFormula("1 b3 b5 bb7"), "dim7", "Diminished Seventh"},
        {ChordPattern::FromFormula("1 3 5 b7 9"), "9", "Dominant Ninth"},
        {ChordPattern::FromFormula("1 3 5 b7 b9"), "7b9", "Dominant Minor Ninth"},
        {ChordPattern::FromFormula("1 3 5 7 9"), "maj9", "Major Ninth"},
        {ChordPattern::FromFormula("1 b3 5 b7 9"), "m9", "Minor Ninth"},
        {ChordPattern::FromFormula("1 3 5 b7 9 11"), "11", "Dominant Eleventh"},
        {ChordPattern::FromFormula("1 3 5 7 9 11"), "maj11", "Major Eleventh"},
        {ChordPattern::FromFormula("1 b3 5 b7 9 11"), "m11", "Minor Eleventh"},
        {ChordPattern::FromFormula("1 3 5 b7 9 13"), "13", "Dominant Thirteenth"},
        {ChordPattern::FromFormula("1 3 5 7 9 13"), "maj13", "Major Thirteenth"},
        {ChordPattern::FromFormula("1 b3 5 b7 9 11 13"), "m13", "Minor Thirteenth"},
        {ChordPattern::FromFormula("1 2 5"), "sus2", "Suspended Second"},
        {ChordPattern::FromFormula("1 4 5"), "sus4", "Suspended Fourth"},
        {ChordPattern::FromFormula("1 b3 5 7"), "mMaj7", "Minor Major Seventh"},
        {ChordPattern::FromFormula("1 3 #5 b7"), "aug7", "Augmented Seventh"},
        {ChordPattern::FromFormula("1 3 5 9"), "add9", "Added Ninth"},
        {ChordPattern::FromFormula("1 4 5 b7"), "7sus4", "Seventh Suspended Fourth"},
        {ChordPattern::FromFormula("1 5"), "5", "Power"},
    };

    constexpr Alias Aliases[AliasCount] FOUNDATION_FLASH = {
        {Id::HalfDiminishedSeventh, "Half Diminished"},
        {Id::HalfDiminishedSeventh, "Minor Seventh Flat Five"},
        {Id::SuspendedSecond, "Sus2"},
        {Id::SuspendedFourth, "Sus4"},
        {Id::DominantMinorNinth, "Seventh Flat Ninth"},
        {Id::AugmentedSeventh, "Seventh Sharp Five"},
        {Id::Power, "Fifth"},
    };

    constexpr bool IsCatalogId(Id id) noexcept {
        return static_cast<uint8_t>(id) < Count;
    }

    size_t WriteEmpty(char* destination, size_t capacity) noexcept {
        if (capacity != 0) {
            destination[0] = '\0';
        }
        return 0;
    }

    bool NameEquals(const char* flashName, const char* name) noexcept {
        for (size_t i = 0; i < NameCapacity; ++i) {
            const char expected = Read(&flashName[i]);
            if (expected != name[i]) {
                return false;
            }
            if (expected == '\0') {
                return true;
            }
        }
        return false;
    }

} // namespace

ChordPattern Pattern(Id id) noexcept {
    return IsCatalogId(id)
        ? Read(&Catalog[static_cast<uint8_t>(id)].pattern)
        : ChordPattern::Invalid();
}

size_t CopyName(Id id, char* destination, size_t capacity) noexcept {
    return IsCatalogId(id)
        ? CopyString(destination, capacity, Catalog[static_cast<uint8_t>(id)].name)
        : WriteEmpty(destination, capacity);
}

size_t CopySymbol(Id id, char* destination, size_t capacity) noexcept {
    return IsCatalogId(id)
        ? CopyString(destination, capacity, Catalog[static_cast<uint8_t>(id)].symbol)
        : WriteEmpty(destination, capacity);
}

size_t CopyAlias(uint8_t index, char* destination, size_t capacity, Id& target) noexcept {
    if (index >= AliasCount) {
        target = Id::Invalid;
        return WriteEmpty(destination, capacity);
    }
    target = Read(&Aliases[index].target);
    return CopyString(destination, capacity, Aliases[index].name);
}

Id Find(const char* name) noexcept {
    if (name == nullptr) {
        return Id::Invalid;
    }
    for (uint8_t i = 0; i < Count; ++i) {
        if (NameEquals(Catalog[i].name, name)) {
            return static_cast<Id>(i);
        }
    }
    for (uint8_t i = 0; i < AliasCount; ++i) {
        if (NameEquals(Aliases[i].name, name)) {
            return Read(&Aliases[i].target);
        }
    }
    return Id::Invalid;
}

size_t FromScale(const Scale& scale, ScaleChord* chords, size_t capacity) noexcept {
    size_t found = 0;
    const uint8_t degrees = scale.DegreeCount();
    for (uint8_t degree = 1; degree <= degrees; ++degree) {
        const NoteName root = scale.NoteAt(degree);
        for (uint8_t i = 0; i < Count && root.IsValid(); ++i) {
            const Chord chord(root, Pattern(static_cast<Id>(i)));
            bool inScale = true;
            for (uint8_t tone = 1; tone <= chord.ToneCount() && inScale; ++tone) {
                inScale = scale.Contains(chord.ToneAt(tone));
            }
            if (inScale) {
                if (found < capacity) {
                    chords[found] = ScaleChord{degree, static_cast<Id>(i)};
                }
                ++found;
            }
        }
    }
    return found;
}

} // namespace Chords
} // namespace MCC
