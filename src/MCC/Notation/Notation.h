#ifndef MCC_NOTATION_NOTATION_H
#define MCC_NOTATION_NOTATION_H

#include <stddef.h>
#include <stdint.h>

#include <MCC/Interval/Interval.h>
#include <MCC/Pitch/NoteName.h>
#include <MCC/Pitch/Pitch.h>

#if __has_include(<MCC/Scale/Scales.h>)
    #include <MCC/Scale/Scales.h>
#endif
#if __has_include(<MCC/Chord/Chords.h>)
    #include <MCC/Chord/Chords.h>
#endif
#if __has_include(<MCC/Key/Key.h>)
    #include <MCC/Key/Key.h>
#endif

namespace MCC {

/**
 * @brief Accidental symbols used in text output (SPEC-TXT-3).
 * @ingroup MCC_Notation
 */
enum class NotationSymbols : uint8_t {
    Ascii,      ///< `#`, `b` and `n`, repeated for multiples.
    Unicode     ///< U+266F ♯, U+266D ♭, U+266E ♮, U+1D12A 𝄪 and U+1D12B 𝄫.
};

/**
 * @brief Options for text output (SPEC-TXT-3).
 * @ingroup MCC_Notation
 */
struct NotationOptions {
    /** @brief Accidental symbols; ASCII by default. */
    NotationSymbols symbols = NotationSymbols::Ascii;
    /** @brief Write the natural sign explicitly (`Cn` or `C♮`). */
    bool explicitNatural = false;
};

/**
 * @brief Text formatting and parsing for note names, pitches and intervals.
 * @ingroup MCC_Notation
 *
 * The buffer's character type selects the encoding (SPEC-TXT-5):
 *
 * | Buffer | Encoding |
 * | ------ | -------- |
 * | `char` | ASCII with `NotationSymbols::Ascii`, otherwise UTF-8 |
 * | `char16_t` | UTF-16, with surrogate pairs for 𝄪 and 𝄫 |
 * | `char32_t` | UTF-32 |
 *
 * Every buffer `Format` function writes with `snprintf` semantics measured
 * in code units: it returns the number of code units the full text needs,
 * stores only whole characters that fit before the terminator, and
 * terminates whenever `capacity > 0`, so a truncated result never ends in a
 * partial UTF-8 or UTF-16 sequence (SPEC-TXT-1..2). The sink overloads pass
 * each Unicode code point to a callback instead, for output without a buffer
 * (for example straight to a serial port). Invalid values format as
 * `"(invalid)"`.
 *
 * Parsing reads the same three encodings and accepts both symbol sets: a
 * letter in either case, then `#`/`♯` (+1), `x`/`𝄪` (+2), `b`/`♭` (-1),
 * `𝄫` (-2), or a single `n`/`♮`. Malformed text returns the invalid value
 * (SPEC-TXT-4).
 */
namespace Notation {

    /** @brief Receives one Unicode code point of formatted text. */
    using CodePointSink = void (*)(uint32_t codePoint, void* context);

    /** @brief Writes `C`, `F#`, `Bbb` (or `F♯`, `B𝄫` with Unicode symbols). */
    template <typename CharT>
    size_t Format(CharT* destination, size_t capacity, NoteName noteName,
                  NotationOptions options = NotationOptions()) noexcept;

    /** @brief Writes `C4`, `F#-1`, `Bb10`. */
    template <typename CharT>
    size_t Format(CharT* destination, size_t capacity, Pitch pitch,
                  NotationOptions options = NotationOptions()) noexcept;

    /**
     * @brief Writes quality and number: `P5`, `M3`, `m7`, `AA4`, `d12`; a
     * descending interval is prefixed with `-` (`-m3`).
     */
    template <typename CharT>
    size_t Format(CharT* destination, size_t capacity, Interval interval,
                  NotationOptions options = NotationOptions()) noexcept;

    /** @brief Sends a note name to `sink`; returns the number of code points. */
    size_t Format(CodePointSink sink, void* context, NoteName noteName,
                  NotationOptions options = NotationOptions()) noexcept;

    /** @brief Sends a pitch to `sink`; returns the number of code points. */
    size_t Format(CodePointSink sink, void* context, Pitch pitch,
                  NotationOptions options = NotationOptions()) noexcept;

    /** @brief Sends an interval to `sink`; returns the number of code points. */
    size_t Format(CodePointSink sink, void* context, Interval interval,
                  NotationOptions options = NotationOptions()) noexcept;

    /** @brief Parses `C`, `f#`, `Ebb`, `Gx`, `B♭`, `Bn`; up to four accidentals. */
    template <typename CharT>
    NoteName ParseNoteName(const CharT* text) noexcept;

    /** @brief Parses a note name followed by a signed octave: `C4`, `bb-1`, `F♯3`. */
    template <typename CharT>
    Pitch ParsePitch(const CharT* text) noexcept;

    /**
     * @brief Parses an optional `+` or `-`, a quality (`P M m A d`, A/d
     * repeated) and a number: `M3`, `-P8`, `+AA4`.
     */
    template <typename CharT>
    Interval ParseInterval(const CharT* text) noexcept;

#if __has_include(<MCC/Scale/Scales.h>)
    /** @brief Writes a catalog scale on a root: `D Dorian`, `F# Minor Blues`. */
    template <typename CharT>
    size_t Format(CharT* destination, size_t capacity, NoteName root, Scales::Id id,
                  NotationOptions options = NotationOptions()) noexcept;

    /** @brief Sends a catalog scale on a root to `sink`. */
    size_t Format(CodePointSink sink, void* context, NoteName root, Scales::Id id,
                  NotationOptions options = NotationOptions()) noexcept;
#endif

#if __has_include(<MCC/Chord/Chords.h>)
    /** @brief Writes a chord symbol: `C`, `C#m7b5`, `Bbmaj9`. */
    template <typename CharT>
    size_t Format(CharT* destination, size_t capacity, NoteName root, Chords::Id id,
                  NotationOptions options = NotationOptions()) noexcept;

    /** @brief Sends a chord symbol to `sink`. */
    size_t Format(CodePointSink sink, void* context, NoteName root, Chords::Id id,
                  NotationOptions options = NotationOptions()) noexcept;
#endif

#if __has_include(<MCC/Key/Key.h>)
    /** @brief Writes a key: `C major`, `F# minor`, `D Dorian`. */
    template <typename CharT>
    size_t Format(CharT* destination, size_t capacity, Key key,
                  NotationOptions options = NotationOptions()) noexcept;

    /** @brief Sends a key to `sink`. */
    size_t Format(CodePointSink sink, void* context, Key key,
                  NotationOptions options = NotationOptions()) noexcept;
#endif

} // namespace Notation

} // namespace MCC

#endif // MCC_NOTATION_NOTATION_H
