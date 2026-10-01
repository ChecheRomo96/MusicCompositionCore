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

    constexpr ChordPattern CatalogPattern(uint32_t semitones,
                                          uint8_t steps0, uint8_t steps1,
                                          uint8_t steps2, uint8_t steps3) noexcept {
        return Detail::ChordPatternStorage::Make(
            semitones, steps0, steps1, steps2, steps3);
    }

    // Reviewed definitions; provenance is recorded in Chord.dox. The encoded
    // patterns are precomputed from the formulas recorded beside each entry.
    constexpr Entry Catalog[Count] FOUNDATION_FLASH = {
        {CatalogPattern(0x00000091u, 0x20u, 0x04u, 0x00u, 0x00u), "", "Major"}, // 1 3 5
        {CatalogPattern(0x00000089u, 0x20u, 0x04u, 0x00u, 0x00u), "m", "Minor"}, // 1 b3 5
        {CatalogPattern(0x00000111u, 0x20u, 0x04u, 0x00u, 0x00u), "aug", "Augmented"}, // 1 3 #5
        {CatalogPattern(0x00000049u, 0x20u, 0x04u, 0x00u, 0x00u), "dim", "Diminished"}, // 1 b3 b5
        {CatalogPattern(0x00000291u, 0x20u, 0x54u, 0x00u, 0x00u), "6", "Sixth"}, // 1 3 5 6
        {CatalogPattern(0x00000289u, 0x20u, 0x54u, 0x00u, 0x00u), "m6", "Minor Sixth"}, // 1 b3 5 6
        {CatalogPattern(0x00000491u, 0x20u, 0x64u, 0x00u, 0x00u), "7", "Dominant Seventh"}, // 1 3 5 b7
        {CatalogPattern(0x00000891u, 0x20u, 0x64u, 0x00u, 0x00u), "maj7", "Major Seventh"}, // 1 3 5 7
        {CatalogPattern(0x00000489u, 0x20u, 0x64u, 0x00u, 0x00u), "m7", "Minor Seventh"}, // 1 b3 5 b7
        {CatalogPattern(0x00000449u, 0x20u, 0x64u, 0x00u, 0x00u), "m7b5", "Half Diminished Seventh"}, // 1 b3 b5 b7
        {CatalogPattern(0x00000249u, 0x20u, 0x64u, 0x00u, 0x00u), "dim7", "Diminished Seventh"}, // 1 b3 b5 bb7
        {CatalogPattern(0x00004491u, 0x20u, 0x64u, 0x08u, 0x00u), "9", "Dominant Ninth"}, // 1 3 5 b7 9
        {CatalogPattern(0x00002491u, 0x20u, 0x64u, 0x08u, 0x00u), "7b9", "Dominant Minor Ninth"}, // 1 3 5 b7 b9
        {CatalogPattern(0x00004891u, 0x20u, 0x64u, 0x08u, 0x00u), "maj9", "Major Ninth"}, // 1 3 5 7 9
        {CatalogPattern(0x00004489u, 0x20u, 0x64u, 0x08u, 0x00u), "m9", "Minor Ninth"}, // 1 b3 5 b7 9
        {CatalogPattern(0x00024491u, 0x20u, 0x64u, 0xA8u, 0x00u), "11", "Dominant Eleventh"}, // 1 3 5 b7 9 11
        {CatalogPattern(0x00024891u, 0x20u, 0x64u, 0xA8u, 0x00u), "maj11", "Major Eleventh"}, // 1 3 5 7 9 11
        {CatalogPattern(0x00024489u, 0x20u, 0x64u, 0xA8u, 0x00u), "m11", "Minor Eleventh"}, // 1 b3 5 b7 9 11
        {CatalogPattern(0x00204491u, 0x20u, 0x64u, 0xC8u, 0x00u), "13", "Dominant Thirteenth"}, // 1 3 5 b7 9 13
        {CatalogPattern(0x00204891u, 0x20u, 0x64u, 0xC8u, 0x00u), "maj13", "Major Thirteenth"}, // 1 3 5 7 9 13
        {CatalogPattern(0x00224489u, 0x20u, 0x64u, 0xA8u, 0x0Cu), "m13", "Minor Thirteenth"}, // 1 b3 5 b7 9 11 13
        {CatalogPattern(0x00000085u, 0x10u, 0x04u, 0x00u, 0x00u), "sus2", "Suspended Second"}, // 1 2 5
        {CatalogPattern(0x000000A1u, 0x30u, 0x04u, 0x00u, 0x00u), "sus4", "Suspended Fourth"}, // 1 4 5
        {CatalogPattern(0x00000889u, 0x20u, 0x64u, 0x00u, 0x00u), "mMaj7", "Minor Major Seventh"}, // 1 b3 5 7
        {CatalogPattern(0x00000511u, 0x20u, 0x64u, 0x00u, 0x00u), "aug7", "Augmented Seventh"}, // 1 3 #5 b7
        {CatalogPattern(0x00004091u, 0x20u, 0x84u, 0x00u, 0x00u), "add9", "Added Ninth"}, // 1 3 5 9
        {CatalogPattern(0x000004A1u, 0x30u, 0x64u, 0x00u, 0x00u), "7sus4", "Seventh Suspended Fourth"}, // 1 4 5 b7
        {CatalogPattern(0x00000081u, 0x40u, 0x00u, 0x00u, 0x00u), "5", "Power"}, // 1 5
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
