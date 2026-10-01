#ifndef MCC_CHORD_CHORDS_H
#define MCC_CHORD_CHORDS_H

#include <stddef.h>
#include <stdint.h>

#include <MCC/Chord/Chord.h>
#include <MCC/Chord/ChordPattern.h>
#include <MCC/Pitch/NoteName.h>
#include <MCC/Scale/Scale.h>

namespace MCC {

/**
 * @brief Reviewed catalog of named chords stored in program memory.
 * @ingroup MCC_Chord
 *
 * Every entry is read from flash on AVR through `Foundation::Utils::Flash`
 * (SPEC-EMB-5); identifiers are stable and never reused (SPEC-CHD-4).
 */
namespace Chords {

    /** @brief Stable catalog identifier. */
    enum class Id : uint8_t {
        Major = 0,
        Minor,
        Augmented,
        Diminished,
        Sixth,
        MinorSixth,
        DominantSeventh,
        MajorSeventh,
        MinorSeventh,
        HalfDiminishedSeventh,
        DiminishedSeventh,
        DominantNinth,
        DominantMinorNinth,
        MajorNinth,
        MinorNinth,
        DominantEleventh,
        MajorEleventh,
        MinorEleventh,
        DominantThirteenth,
        MajorThirteenth,
        MinorThirteenth,
        SuspendedSecond,
        SuspendedFourth,
        MinorMajorSeventh,
        AugmentedSeventh,
        AddedNinth,
        SeventhSuspendedFourth,
        Power,
        Invalid = 0xFF
    };

    /** @brief Number of catalog entries. */
    constexpr uint8_t Count = static_cast<uint8_t>(Id::Power) + 1;

    /** @brief Number of aliases. */
    constexpr uint8_t AliasCount = 7;

    /** @brief Buffer size that fits every name and alias with its terminator. */
    constexpr size_t NameCapacity = 28;

    /** @brief Buffer size that fits every symbol with its terminator. */
    constexpr size_t SymbolCapacity = 8;

    /** @brief Returns the pattern of `id`, or the invalid pattern. */
    ChordPattern Pattern(Id id) noexcept;

    /**
     * @brief Copies the canonical name of `id` with `snprintf` semantics and
     * returns its length; an invalid `id` writes an empty string.
     */
    size_t CopyName(Id id, char* destination, size_t capacity) noexcept;

    /**
     * @brief Copies the chord symbol of `id` (`""`, `"m"`, `"maj7"`, ...) with
     * `snprintf` semantics and returns its length.
     */
    size_t CopySymbol(Id id, char* destination, size_t capacity) noexcept;

    /**
     * @brief Copies alias `index` (0-based, below `AliasCount`) and returns its
     * length, also reporting the chord it names; out of range writes an empty
     * string and reports `Id::Invalid`.
     */
    size_t CopyAlias(uint8_t index, char* destination, size_t capacity, Id& target) noexcept;

    /**
     * @brief Finds a chord by exact canonical name or alias; returns
     * `Id::Invalid` when nothing matches.
     */
    Id Find(const char* name) noexcept;

    /** @brief Spells catalog entry `id` from `root`. */
    inline Chord Make(NoteName root, Id id) noexcept {
        return Chord(root, Pattern(id));
    }

    /** @brief One chord found on a scale degree. */
    struct ScaleChord {
        uint8_t degree;   ///< 1-based scale degree of the root.
        Id id;            ///< Catalog entry built on that degree.
    };

    /**
     * @brief Lists every catalog chord whose tones are all written in `scale`
     * (SPEC-CHD-5).
     *
     * Chords are ordered by scale degree, then by catalog identifier. Writes
     * at most `capacity` results and returns the number found, so a larger
     * result means the buffer was too small. Spell a result with
     * `Make(scale.NoteAt(degree), id)`.
     */
    size_t FromScale(const Scale& scale, ScaleChord* chords, size_t capacity) noexcept;

} // namespace Chords

} // namespace MCC

#endif // MCC_CHORD_CHORDS_H
