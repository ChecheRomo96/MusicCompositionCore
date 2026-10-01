#ifndef MCC_SCALE_SCALES_H
#define MCC_SCALE_SCALES_H

#include <stddef.h>
#include <stdint.h>

#include <MCC/Pitch/NoteName.h>
#include <MCC/Scale/Scale.h>
#include <MCC/Scale/ScalePattern.h>

namespace MCC {

/**
 * @brief Reviewed catalog of named scales stored in program memory.
 * @ingroup MCC_Scale
 *
 * Every entry is read from flash on AVR through `Foundation::Utils::Flash`
 * (SPEC-EMB-5); identifiers are stable and never reused (SPEC-SCL-4).
 */
namespace Scales {

    /** @brief Stable catalog identifier. */
    enum class Id : uint8_t {
        Chromatic = 0,
        ChromaticFlats,
        Major,
        Minor,
        HarmonicMinor,
        MelodicMinor,
        HarmonicMajor,
        MajorPentatonic,
        MinorPentatonic,
        MinorBlues,
        MajorBlues,
        Dorian,
        Phrygian,
        Lydian,
        Mixolydian,
        Locrian,
        Algerian,
        Arabic,
        Augmented,
        Pelog,
        Byzantine,
        Chinese,
        Diminished,
        Egyptian,
        EightToneSpanish,
        Enigmatic,
        Hindu,
        Hirajoshi,
        Iwato,
        HungarianMinor,
        Japanese,
        Oriental,
        WholeTone,
        RomanianMinor,
        SpanishGypsy,
        SuperLocrian,
        Invalid = 0xFF
    };

    /** @brief Grouping inherited from the historical catalog arrays. */
    enum class Family : uint8_t {
        Western,
        Modal,
        Symmetric,
        Exotic,
        Invalid = 0xFF
    };

    /** @brief Number of catalog entries. */
    constexpr uint8_t Count = static_cast<uint8_t>(Id::SuperLocrian) + 1;

    /** @brief Number of aliases. */
    constexpr uint8_t AliasCount = 9;

    /** @brief Buffer size that fits every name and alias with its terminator. */
    constexpr size_t NameCapacity = 24;

    /** @brief Returns the pattern of `id`, or the invalid pattern. */
    ScalePattern Pattern(Id id) noexcept;

    /** @brief Returns the family of `id`, or `Family::Invalid`. */
    Family FamilyOf(Id id) noexcept;

    /**
     * @brief Copies the canonical name of `id` with `snprintf` semantics and
     * returns its length; an invalid `id` writes an empty string.
     */
    size_t CopyName(Id id, char* destination, size_t capacity) noexcept;

    /**
     * @brief Copies alias `index` (0-based, below `AliasCount`) and returns its
     * length, also reporting the scale it names; out of range writes an empty
     * string and reports `Id::Invalid`.
     */
    size_t CopyAlias(uint8_t index, char* destination, size_t capacity, Id& target) noexcept;

    /**
     * @brief Finds a scale by exact canonical name or alias; returns
     * `Id::Invalid` when nothing matches.
     */
    Id Find(const char* name) noexcept;

    /** @brief Spells catalog entry `id` from `root`. */
    inline Scale Make(NoteName root, Id id) noexcept {
        return Scale(root, Pattern(id));
    }

} // namespace Scales

} // namespace MCC

#endif // MCC_SCALE_SCALES_H
