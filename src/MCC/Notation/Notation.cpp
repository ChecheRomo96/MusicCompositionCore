#include <MCC/Notation/Notation.h>
#include "Writer.h"

#include <Foundation/Utils/Flash.h>

namespace MCC {
namespace Notation {

namespace {

    // Text constants live in program memory on AVR (SPEC-EMB-5).
    constexpr char Letters[] FOUNDATION_FLASH = "CDEFGAB";
    constexpr char InvalidText[] FOUNDATION_FLASH = "(invalid)";
    constexpr char ModeNames[7][12] FOUNDATION_FLASH = {
        " Lydian", " major", " Mixolydian", " Dorian", " minor", " Phrygian", " Locrian"};

    constexpr uint32_t NaturalSign = 0x266E;      // U+266E natural
    constexpr uint32_t SharpSign = 0x266F;        // U+266F sharp
    constexpr uint32_t FlatSign = 0x266D;         // U+266D flat
    constexpr uint32_t DoubleSharpSign = 0x1D12A; // U+1D12A double sharp
    constexpr uint32_t DoubleFlatSign = 0x1D12B;  // U+1D12B double flat

    ////////////////////////////////////////////////////////////////////////////
    // Writing: each function works on a buffer Writer or a SinkWriter.

    template <typename W>
    void WriteNoteName(W& out, NoteName noteName, NotationOptions options) noexcept {
        const bool unicode = options.symbols == NotationSymbols::Unicode;
        out.Put(static_cast<uint32_t>(Foundation::Utils::Flash::Read(
            &Letters[DiatonicIndex(noteName.Letter())])));
        const int32_t semitones = noteName.Accidental().Semitones();
        if (semitones == 0) {
            if (options.explicitNatural) {
                out.Put(unicode ? NaturalSign : static_cast<uint32_t>('n'));
            }
            return;
        }
        const bool sharp = semitones > 0;
        int32_t count = sharp ? semitones : -semitones;
        if (unicode) {
            // Pairs use the double sign; a remaining single uses the single sign.
            for (; count >= 2; count -= 2) {
                out.Put(sharp ? DoubleSharpSign : DoubleFlatSign);
            }
            if (count == 1) {
                out.Put(sharp ? SharpSign : FlatSign);
            }
            return;
        }
        for (; count > 0; --count) {
            out.Put(static_cast<uint32_t>(sharp ? '#' : 'b'));
        }
    }

    template <typename W>
    size_t Write(W& out, NoteName noteName, NotationOptions options) noexcept {
        if (noteName.IsValid()) {
            WriteNoteName(out, noteName, options);
        } else {
            out.PutFlash(InvalidText);
        }
        return out.Length();
    }

    template <typename W>
    size_t Write(W& out, Pitch pitch, NotationOptions options) noexcept {
        if (pitch.IsValid()) {
            WriteNoteName(out, pitch.NoteName(), options);
            out.PutInteger(pitch.Octave());
        } else {
            out.PutFlash(InvalidText);
        }
        return out.Length();
    }

    template <typename W>
    size_t Write(W& out, Interval interval, NotationOptions) noexcept {
        if (!interval.IsValid()) {
            out.PutFlash(InvalidText);
            return out.Length();
        }
        if (interval.Direction() == IntervalDirection::Descending) {
            out.Put(static_cast<uint32_t>('-'));
        }
        const IntervalQuality quality = interval.Quality();
        char symbol = 'P';
        uint8_t repeat = 1;
        switch (quality.Kind()) {
            case IntervalQualityKind::Perfect: symbol = 'P'; break;
            case IntervalQualityKind::Major: symbol = 'M'; break;
            case IntervalQualityKind::Minor: symbol = 'm'; break;
            case IntervalQualityKind::Augmented: symbol = 'A'; repeat = quality.Count(); break;
            case IntervalQualityKind::Diminished: symbol = 'd'; repeat = quality.Count(); break;
        }
        for (uint8_t i = 0; i < repeat; ++i) {
            out.Put(static_cast<uint32_t>(symbol));
        }
        out.PutInteger(interval.Number().Value());
        return out.Length();
    }

#if __has_include(<MCC/Scale/Scales.h>)
    template <typename W>
    size_t Write(W& out, NoteName root, Scales::Id id, NotationOptions options) noexcept {
        char name[Scales::NameCapacity];
        if (!root.IsValid() || Scales::CopyName(id, name, sizeof(name)) == 0) {
            out.PutFlash(InvalidText);
            return out.Length();
        }
        WriteNoteName(out, root, options);
        out.Put(static_cast<uint32_t>(' '));
        out.PutAscii(name);
        return out.Length();
    }
#endif

#if __has_include(<MCC/Chord/Chords.h>)
    template <typename W>
    size_t Write(W& out, NoteName root, Chords::Id id, NotationOptions options) noexcept {
        char symbol[Chords::SymbolCapacity];
        if (!root.IsValid() || !Chords::Pattern(id).IsValid()) {
            out.PutFlash(InvalidText);
            return out.Length();
        }
        Chords::CopySymbol(id, symbol, sizeof(symbol));
        WriteNoteName(out, root, options);
        out.PutAscii(symbol);
        return out.Length();
    }
#endif

#if __has_include(<MCC/Key/Key.h>)
    template <typename W>
    size_t Write(W& out, Key key, NotationOptions options) noexcept {
        if (!key.IsValid()) {
            out.PutFlash(InvalidText);
            return out.Length();
        }
        WriteNoteName(out, key.Tonic(), options);
        out.PutFlash(ModeNames[static_cast<uint8_t>(key.Mode())]);
        return out.Length();
    }
#endif

    ////////////////////////////////////////////////////////////////////////////
    // Reading: code points from any supported encoding.

    // Reads a letter (either case) and its accidentals.
    template <typename CharT>
    NoteName ReadNoteName(Detail::Reader<CharT>& in) noexcept {
        uint32_t c = in.Peek();
        if (c >= 'a' && c <= 'g') {
            c = c - 'a' + 'A';
        }
        int32_t letter = -1;
        for (int32_t i = 0; i < 7; ++i) {
            if (c == static_cast<uint32_t>(Foundation::Utils::Flash::Read(&Letters[i]))) {
                letter = i;
            }
        }
        if (letter < 0) {
            return NoteName::Invalid();
        }
        in.Advance();
        if (in.Peek() == 'n' || in.Peek() == NaturalSign) {
            in.Advance();
            return NoteName(static_cast<Letter>(letter));
        }
        // Sharps (#, U+266F sharp, x, U+1D12A double sharp) and flats (b, U+266D flat, U+1D12B double flat) may be mixed within one
        // direction, but never with each other.
        int32_t accidental = 0;
        int32_t direction = 0;
        for (;;) {
            const uint32_t symbol = in.Peek();
            int32_t step = 0;
            if (symbol == '#' || symbol == SharpSign) { step = 1; }
            else if (symbol == 'x' || symbol == DoubleSharpSign) { step = 2; }
            else if (symbol == 'b' || symbol == FlatSign) { step = -1; }
            else if (symbol == DoubleFlatSign) { step = -2; }
            if (step == 0) {
                break;
            }
            const int32_t sign = step > 0 ? 1 : -1;
            if (direction != 0 && direction != sign) {
                return NoteName::Invalid();
            }
            direction = sign;
            accidental += step;
            if (accidental > 4 || accidental < -4) {
                return NoteName::Invalid();
            }
            in.Advance();
        }
        return NoteName(static_cast<Letter>(letter), Accidental(accidental));
    }

    // Reads an optionally signed decimal integer of one to four digits.
    template <typename CharT>
    bool ReadInteger(Detail::Reader<CharT>& in, int32_t& value, bool allowPlus) noexcept {
        const uint32_t sign = in.Peek();
        const bool negative = sign == '-';
        if (negative || (allowPlus && sign == '+')) {
            in.Advance();
        }
        int32_t digits = 0;
        value = 0;
        for (uint32_t c = in.Peek(); c >= '0' && c <= '9' && digits < 5; c = in.Peek()) {
            value = value * 10 + static_cast<int32_t>(c - '0');
            in.Advance();
            ++digits;
        }
        if (negative) {
            value = -value;
        }
        return digits > 0 && digits < 5;
    }

} // namespace

template <typename CharT>
NoteName ParseNoteName(const CharT* text) noexcept {
    if (text == nullptr) {
        return NoteName::Invalid();
    }
    Detail::Reader<CharT> in(text);
    const NoteName noteName = ReadNoteName(in);
    return in.Peek() == 0 ? noteName : NoteName::Invalid();
}

template <typename CharT>
Pitch ParsePitch(const CharT* text) noexcept {
    if (text == nullptr) {
        return Pitch::Invalid();
    }
    Detail::Reader<CharT> in(text);
    const NoteName noteName = ReadNoteName(in);
    int32_t octave = 0;
    if (!noteName.IsValid() || !ReadInteger(in, octave, false) || in.Peek() != 0) {
        return Pitch::Invalid();
    }
    return Pitch(noteName, octave);
}

template <typename CharT>
Interval ParseInterval(const CharT* text) noexcept {
    if (text == nullptr) {
        return Interval::Invalid();
    }
    Detail::Reader<CharT> in(text);
    const bool descending = in.Peek() == '-';
    if (descending || in.Peek() == '+') {
        in.Advance();
    }
    IntervalQuality quality;
    const uint32_t symbol = in.Peek();
    if (symbol == 'P' || symbol == 'M' || symbol == 'm') {
        quality = symbol == 'P' ? IntervalQuality::Perfect()
                : symbol == 'M' ? IntervalQuality::Major()
                                : IntervalQuality::Minor();
        in.Advance();
    } else if (symbol == 'A' || symbol == 'd') {
        int32_t count = 0;
        while (in.Peek() == symbol) {
            ++count;
            in.Advance();
        }
        quality = symbol == 'A' ? IntervalQuality::Augmented(count)
                                : IntervalQuality::Diminished(count);
    }
    int32_t number = 0;
    if (!quality.IsValid() || in.Peek() == '-' || in.Peek() == '+' ||
        !ReadInteger(in, number, false) || in.Peek() != 0) {
        return Interval::Invalid();
    }
    const Interval interval(quality, IntervalNumber(number),
        descending ? IntervalDirection::Descending : IntervalDirection::Ascending);
    // A quality that does not exist for the number (P3, M5) builds the
    // invalid interval; reject it rather than reinterpret it.
    return interval.IsValid() && interval.Quality() == quality ? interval : Interval::Invalid();
}

////////////////////////////////////////////////////////////////////////////////
// Public entry points.

#define MCC_NOTATION_FORMAT(ValueParameters, ValueArguments)                         \
    template <typename CharT>                                                          \
    size_t Format(CharT* destination, size_t capacity, ValueParameters,                \
                  NotationOptions options) noexcept {                                  \
        Detail::Writer<CharT> out(destination, capacity);                              \
        return Write(out, ValueArguments, options);                                    \
    }                                                                                  \
    size_t Format(CodePointSink sink, void* context, ValueParameters,                  \
                  NotationOptions options) noexcept {                                  \
        Detail::SinkWriter out(sink, context);                                         \
        return Write(out, ValueArguments, options);                                    \
    }

#define MCC_NOTATION_COMMA ,

MCC_NOTATION_FORMAT(NoteName noteName, noteName)
MCC_NOTATION_FORMAT(Pitch pitch, pitch)
MCC_NOTATION_FORMAT(Interval interval, interval)
#if __has_include(<MCC/Scale/Scales.h>)
MCC_NOTATION_FORMAT(NoteName root MCC_NOTATION_COMMA Scales::Id id, root MCC_NOTATION_COMMA id)
#endif
#if __has_include(<MCC/Chord/Chords.h>)
MCC_NOTATION_FORMAT(NoteName root MCC_NOTATION_COMMA Chords::Id id, root MCC_NOTATION_COMMA id)
#endif
#if __has_include(<MCC/Key/Key.h>)
MCC_NOTATION_FORMAT(Key key, key)
#endif

// The supported code units: UTF-8 (or ASCII), UTF-16 and UTF-32. Template
// arguments cannot be parenthesized, so the macro-parentheses check is off.
// NOLINTBEGIN(bugprone-macro-parentheses)
#if __has_include(<MCC/Scale/Scales.h>)
    #define MCC_NOTATION_INSTANTIATE_SCALE(CharT) \
        template size_t Format<CharT>(CharT*, size_t, NoteName, Scales::Id, NotationOptions) noexcept;
#else
    #define MCC_NOTATION_INSTANTIATE_SCALE(CharT)
#endif

#if __has_include(<MCC/Chord/Chords.h>)
    #define MCC_NOTATION_INSTANTIATE_CHORD(CharT) \
        template size_t Format<CharT>(CharT*, size_t, NoteName, Chords::Id, NotationOptions) noexcept;
#else
    #define MCC_NOTATION_INSTANTIATE_CHORD(CharT)
#endif

#if __has_include(<MCC/Key/Key.h>)
    #define MCC_NOTATION_INSTANTIATE_KEY(CharT) \
        template size_t Format<CharT>(CharT*, size_t, Key, NotationOptions) noexcept;
#else
    #define MCC_NOTATION_INSTANTIATE_KEY(CharT)
#endif

#define MCC_NOTATION_INSTANTIATE(CharT)                                                     \
    template size_t Format<CharT>(CharT*, size_t, NoteName, NotationOptions) noexcept;      \
    template size_t Format<CharT>(CharT*, size_t, Pitch, NotationOptions) noexcept;         \
    template size_t Format<CharT>(CharT*, size_t, Interval, NotationOptions) noexcept;      \
    template NoteName ParseNoteName<CharT>(const CharT*) noexcept;                          \
    template Pitch ParsePitch<CharT>(const CharT*) noexcept;                                \
    template Interval ParseInterval<CharT>(const CharT*) noexcept;                          \
    MCC_NOTATION_INSTANTIATE_SCALE(CharT)                                                   \
    MCC_NOTATION_INSTANTIATE_CHORD(CharT)                                                   \
    MCC_NOTATION_INSTANTIATE_KEY(CharT)

MCC_NOTATION_INSTANTIATE(char)
MCC_NOTATION_INSTANTIATE(char16_t)
MCC_NOTATION_INSTANTIATE(char32_t)
// NOLINTEND(bugprone-macro-parentheses)

} // namespace Notation
} // namespace MCC
