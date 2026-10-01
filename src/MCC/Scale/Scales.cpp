#include <MCC/Scale/Scales.h>

#include <Foundation/Utils/Flash.h>

namespace MCC {
namespace Scales {

namespace {

    using Foundation::Utils::Flash::CopyString;
    using Foundation::Utils::Flash::Read;

    struct Entry {
        ScalePattern pattern;
        Family family;
        char name[NameCapacity];
    };

    struct Alias {
        Id target;
        char name[NameCapacity];
    };

    // Reviewed definitions; provenance is recorded in Scale.dox. The encoded
    // patterns are precomputed from the formulas recorded beside each entry.
    constexpr Entry Catalog[Count] FOUNDATION_FLASH = {
        {Detail::ScalePatternStorage::Make(0x0FFFu, 0x00u, 0x11u, 0x32u, 0x43u, 0x54u, 0x65u), Family::Symmetric, "Chromatic"}, // 1 #1 2 #2 3 4 #4 5 #5 6 #6 7
        {Detail::ScalePatternStorage::Make(0x0FFFu, 0x10u, 0x21u, 0x32u, 0x44u, 0x55u, 0x66u), Family::Symmetric, "Chromatic (Flats)"}, // 1 b2 2 b3 3 4 b5 5 b6 6 b7 7
        {Detail::ScalePatternStorage::Make(0x0AB5u, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Western, "Major"}, // 1 2 3 4 5 6 7
        {Detail::ScalePatternStorage::Make(0x05ADu, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Western, "Minor"}, // 1 2 b3 4 5 b6 b7
        {Detail::ScalePatternStorage::Make(0x09ADu, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Western, "Harmonic Minor"}, // 1 2 b3 4 5 b6 7
        {Detail::ScalePatternStorage::Make(0x0AADu, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Western, "Melodic Minor"}, // 1 2 b3 4 5 6 7
        {Detail::ScalePatternStorage::Make(0x09B5u, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Western, "Harmonic Major"}, // 1 2 3 4 5 b6 7
        {Detail::ScalePatternStorage::Make(0x0295u, 0x10u, 0x42u, 0x05u, 0x00u, 0x00u, 0x00u), Family::Western, "Major Pentatonic"}, // 1 2 3 5 6
        {Detail::ScalePatternStorage::Make(0x04A9u, 0x20u, 0x43u, 0x06u, 0x00u, 0x00u, 0x00u), Family::Western, "Minor Pentatonic"}, // 1 b3 4 5 b7
        {Detail::ScalePatternStorage::Make(0x04E9u, 0x20u, 0x43u, 0x64u, 0x00u, 0x00u, 0x00u), Family::Western, "Minor Blues"}, // 1 b3 4 b5 5 b7
        {Detail::ScalePatternStorage::Make(0x029Du, 0x10u, 0x22u, 0x54u, 0x00u, 0x00u, 0x00u), Family::Western, "Major Blues"}, // 1 2 b3 3 5 6
        {Detail::ScalePatternStorage::Make(0x06ADu, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Modal, "Dorian"}, // 1 2 b3 4 5 6 b7
        {Detail::ScalePatternStorage::Make(0x05ABu, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Modal, "Phrygian"}, // 1 b2 b3 4 5 b6 b7
        {Detail::ScalePatternStorage::Make(0x0AD5u, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Modal, "Lydian"}, // 1 2 3 #4 5 6 7
        {Detail::ScalePatternStorage::Make(0x06B5u, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Modal, "Mixolydian"}, // 1 2 3 4 5 6 b7
        {Detail::ScalePatternStorage::Make(0x056Bu, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Modal, "Locrian"}, // 1 b2 b3 4 b5 b6 b7
        {Detail::ScalePatternStorage::Make(0x09EDu, 0x10u, 0x32u, 0x43u, 0x65u, 0x00u, 0x00u), Family::Exotic, "Algerian"}, // 1 2 b3 4 #4 5 b6 7
        {Detail::ScalePatternStorage::Make(0x0575u, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Exotic, "Arabic"}, // 1 2 3 4 b5 b6 b7
        {Detail::ScalePatternStorage::Make(0x0999u, 0x20u, 0x42u, 0x64u, 0x00u, 0x00u, 0x00u), Family::Symmetric, "Augmented"}, // 1 b3 3 5 #5 7
        {Detail::ScalePatternStorage::Make(0x018Bu, 0x10u, 0x42u, 0x05u, 0x00u, 0x00u, 0x00u), Family::Exotic, "Pelog"}, // 1 b2 b3 5 b6
        {Detail::ScalePatternStorage::Make(0x09B3u, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Exotic, "Byzantine"}, // 1 b2 3 4 5 b6 7
        {Detail::ScalePatternStorage::Make(0x08D1u, 0x20u, 0x43u, 0x06u, 0x00u, 0x00u, 0x00u), Family::Exotic, "Chinese"}, // 1 3 #4 5 7
        {Detail::ScalePatternStorage::Make(0x0B6Du, 0x10u, 0x32u, 0x43u, 0x65u, 0x00u, 0x00u), Family::Symmetric, "Diminished"}, // 1 2 b3 4 #4 #5 6 7
        {Detail::ScalePatternStorage::Make(0x04A5u, 0x10u, 0x43u, 0x06u, 0x00u, 0x00u, 0x00u), Family::Exotic, "Egyptian"}, // 1 2 4 5 b7
        {Detail::ScalePatternStorage::Make(0x057Bu, 0x10u, 0x21u, 0x43u, 0x65u, 0x00u, 0x00u), Family::Exotic, "Eight Tone Spanish"}, // 1 b2 #2 3 4 b5 b6 b7
        {Detail::ScalePatternStorage::Make(0x0D53u, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Exotic, "Enigmatic"}, // 1 b2 3 #4 #5 #6 7
        {Detail::ScalePatternStorage::Make(0x05B5u, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Exotic, "Hindu"}, // 1 2 3 4 5 b6 b7
        {Detail::ScalePatternStorage::Make(0x018Du, 0x10u, 0x42u, 0x05u, 0x00u, 0x00u, 0x00u), Family::Exotic, "Hirajoshi"}, // 1 2 b3 5 b6
        {Detail::ScalePatternStorage::Make(0x0463u, 0x10u, 0x43u, 0x06u, 0x00u, 0x00u, 0x00u), Family::Exotic, "Iwato"}, // 1 b2 4 b5 b7
        {Detail::ScalePatternStorage::Make(0x09CDu, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Exotic, "Hungarian Minor"}, // 1 2 b3 #4 5 b6 7
        {Detail::ScalePatternStorage::Make(0x04A3u, 0x10u, 0x43u, 0x06u, 0x00u, 0x00u, 0x00u), Family::Exotic, "Japanese"}, // 1 b2 4 5 b7
        {Detail::ScalePatternStorage::Make(0x0673u, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Exotic, "Oriental"}, // 1 b2 3 4 b5 6 b7
        {Detail::ScalePatternStorage::Make(0x0555u, 0x10u, 0x32u, 0x64u, 0x00u, 0x00u, 0x00u), Family::Symmetric, "Whole Tone"}, // 1 2 3 #4 #5 b7
        {Detail::ScalePatternStorage::Make(0x06CDu, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Exotic, "Romanian Minor"}, // 1 2 b3 #4 5 6 b7
        {Detail::ScalePatternStorage::Make(0x05B3u, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Exotic, "Spanish Gypsy"}, // 1 b2 3 4 5 b6 b7
        {Detail::ScalePatternStorage::Make(0x055Bu, 0x10u, 0x32u, 0x54u, 0x06u, 0x00u, 0x00u), Family::Exotic, "Super Locrian"}, // 1 b2 b3 b4 b5 b6 b7
    };

    constexpr Alias Aliases[] FOUNDATION_FLASH = {
        {Id::Major, "Ionian"},
        {Id::Minor, "Natural Minor"},
        {Id::Minor, "Aeolian"},
        {Id::Minor, "Ethiopian"},
        {Id::Byzantine, "Double Harmonic Major"},
        {Id::Japanese, "In Sen"},
        {Id::SpanishGypsy, "Phrygian Dominant"},
        {Id::SuperLocrian, "Altered"},
        {Id::Diminished, "Whole Half Diminished"},
    };

    constexpr bool IsCatalogId(Id id) noexcept {
        return static_cast<uint8_t>(id) < Count;
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

static_assert(sizeof(Aliases) / sizeof(Aliases[0]) == AliasCount,
    "AliasCount must match the alias table");

ScalePattern Pattern(Id id) noexcept {
    return IsCatalogId(id)
        ? Read(&Catalog[static_cast<uint8_t>(id)].pattern)
        : ScalePattern::Invalid();
}

Family FamilyOf(Id id) noexcept {
    return IsCatalogId(id)
        ? Read(&Catalog[static_cast<uint8_t>(id)].family)
        : Family::Invalid;
}

size_t CopyName(Id id, char* destination, size_t capacity) noexcept {
    if (!IsCatalogId(id)) {
        if (capacity != 0) {
            destination[0] = '\0';
        }
        return 0;
    }
    return CopyString(destination, capacity, Catalog[static_cast<uint8_t>(id)].name);
}

size_t CopyAlias(uint8_t index, char* destination, size_t capacity, Id& target) noexcept {
    if (index >= AliasCount) {
        target = Id::Invalid;
        if (capacity != 0) {
            destination[0] = '\0';
        }
        return 0;
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

} // namespace Scales
} // namespace MCC
