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

    // Reviewed definitions; provenance is recorded in Scale.dox. Degree
    // formulas are evaluated at compile time into eight-byte patterns.
    constexpr Entry Catalog[Count] FOUNDATION_FLASH = {
        {ScalePattern::FromFormula("1 #1 2 #2 3 4 #4 5 #5 6 #6 7"), Family::Symmetric, "Chromatic"},
        {ScalePattern::FromFormula("1 b2 2 b3 3 4 b5 5 b6 6 b7 7"), Family::Symmetric, "Chromatic (Flats)"},
        {ScalePattern::FromFormula("1 2 3 4 5 6 7"), Family::Western, "Major"},
        {ScalePattern::FromFormula("1 2 b3 4 5 b6 b7"), Family::Western, "Minor"},
        {ScalePattern::FromFormula("1 2 b3 4 5 b6 7"), Family::Western, "Harmonic Minor"},
        {ScalePattern::FromFormula("1 2 b3 4 5 6 7"), Family::Western, "Melodic Minor"},
        {ScalePattern::FromFormula("1 2 3 4 5 b6 7"), Family::Western, "Harmonic Major"},
        {ScalePattern::FromFormula("1 2 3 5 6"), Family::Western, "Major Pentatonic"},
        {ScalePattern::FromFormula("1 b3 4 5 b7"), Family::Western, "Minor Pentatonic"},
        {ScalePattern::FromFormula("1 b3 4 b5 5 b7"), Family::Western, "Minor Blues"},
        {ScalePattern::FromFormula("1 2 b3 3 5 6"), Family::Western, "Major Blues"},
        {ScalePattern::FromFormula("1 2 b3 4 5 6 b7"), Family::Modal, "Dorian"},
        {ScalePattern::FromFormula("1 b2 b3 4 5 b6 b7"), Family::Modal, "Phrygian"},
        {ScalePattern::FromFormula("1 2 3 #4 5 6 7"), Family::Modal, "Lydian"},
        {ScalePattern::FromFormula("1 2 3 4 5 6 b7"), Family::Modal, "Mixolydian"},
        {ScalePattern::FromFormula("1 b2 b3 4 b5 b6 b7"), Family::Modal, "Locrian"},
        {ScalePattern::FromFormula("1 2 b3 4 #4 5 b6 7"), Family::Exotic, "Algerian"},
        {ScalePattern::FromFormula("1 2 3 4 b5 b6 b7"), Family::Exotic, "Arabic"},
        {ScalePattern::FromFormula("1 b3 3 5 #5 7"), Family::Symmetric, "Augmented"},
        {ScalePattern::FromFormula("1 b2 b3 5 b6"), Family::Exotic, "Pelog"},
        {ScalePattern::FromFormula("1 b2 3 4 5 b6 7"), Family::Exotic, "Byzantine"},
        {ScalePattern::FromFormula("1 3 #4 5 7"), Family::Exotic, "Chinese"},
        {ScalePattern::FromFormula("1 2 b3 4 #4 #5 6 7"), Family::Symmetric, "Diminished"},
        {ScalePattern::FromFormula("1 2 4 5 b7"), Family::Exotic, "Egyptian"},
        {ScalePattern::FromFormula("1 b2 #2 3 4 b5 b6 b7"), Family::Exotic, "Eight Tone Spanish"},
        {ScalePattern::FromFormula("1 b2 3 #4 #5 #6 7"), Family::Exotic, "Enigmatic"},
        {ScalePattern::FromFormula("1 2 3 4 5 b6 b7"), Family::Exotic, "Hindu"},
        {ScalePattern::FromFormula("1 2 b3 5 b6"), Family::Exotic, "Hirajoshi"},
        {ScalePattern::FromFormula("1 b2 4 b5 b7"), Family::Exotic, "Iwato"},
        {ScalePattern::FromFormula("1 2 b3 #4 5 b6 7"), Family::Exotic, "Hungarian Minor"},
        {ScalePattern::FromFormula("1 b2 4 5 b7"), Family::Exotic, "Japanese"},
        {ScalePattern::FromFormula("1 b2 3 4 b5 6 b7"), Family::Exotic, "Oriental"},
        {ScalePattern::FromFormula("1 2 3 #4 #5 b7"), Family::Symmetric, "Whole Tone"},
        {ScalePattern::FromFormula("1 2 b3 #4 5 6 b7"), Family::Exotic, "Romanian Minor"},
        {ScalePattern::FromFormula("1 b2 3 4 5 b6 b7"), Family::Exotic, "Spanish Gypsy"},
        {ScalePattern::FromFormula("1 b2 b3 b4 b5 b6 b7"), Family::Exotic, "Super Locrian"},
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
