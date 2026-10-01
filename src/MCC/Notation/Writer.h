#ifndef MCC_NOTATION_WRITER_H
#define MCC_NOTATION_WRITER_H

#include <stddef.h>
#include <stdint.h>

#include <Foundation/Utils/Flash.h>

#include <MCC/Notation/Notation.h>

namespace MCC {
namespace Notation {
namespace Detail {

// Text helpers shared by every output: `Derived::Put(uint32_t)` appends one
// Unicode code point.
template <typename Derived>
class Output {
    friend Derived;
    Output() noexcept = default;

    Derived& Self() noexcept { return static_cast<Derived&>(*this); }

public:
    void PutAscii(const char* text) noexcept {
        while (*text != '\0') {
            Self().Put(static_cast<uint32_t>(static_cast<unsigned char>(*text++)));
        }
    }

    // Appends an ASCII string declared with FOUNDATION_FLASH.
    void PutFlash(const char* text) noexcept {
        for (char c = Foundation::Utils::Flash::Read(text); c != '\0';
             c = Foundation::Utils::Flash::Read(++text)) {
            Self().Put(static_cast<uint32_t>(static_cast<unsigned char>(c)));
        }
    }

    void PutInteger(int32_t value) noexcept {
        char digits[11];
        uint8_t count = 0;
        uint32_t magnitude = value < 0 ? 0u - static_cast<uint32_t>(value)
                                       : static_cast<uint32_t>(value);
        do {
            digits[count++] = static_cast<char>('0' + magnitude % 10);
            magnitude /= 10;
        } while (magnitude != 0);
        if (value < 0) {
            Self().Put(static_cast<uint32_t>('-'));
        }
        while (count != 0) {
            Self().Put(static_cast<uint32_t>(digits[--count]));
        }
    }
};

// Encodes code points for CharT (UTF-8, UTF-16 or UTF-32) into a buffer with
// snprintf semantics in code units: counts every unit, stores only whole
// characters that fit before the terminator, and stops storing after the
// first character that does not fit.
template <typename CharT>
class Writer : public Output<Writer<CharT>> {
    CharT* _destination;
    size_t _capacity;
    size_t _length;
    size_t _stored;
    bool _full;

    void Store(const CharT* units, size_t count) noexcept {
        _length += count;
        if (_full || _stored + count + 1 > _capacity) {
            _full = true;
            return;
        }
        for (size_t i = 0; i < count; ++i) {
            _destination[_stored++] = units[i];
        }
        _destination[_stored] = CharT(0);
    }

public:
    Writer(CharT* destination, size_t capacity) noexcept
        : _destination(destination), _capacity(capacity), _length(0), _stored(0), _full(false) {
        if (_capacity != 0) {
            _destination[0] = CharT(0);
        }
    }

    void Put(uint32_t codePoint) noexcept;

    size_t Length() const noexcept { return _length; }
};

template <>
inline void Writer<char>::Put(uint32_t codePoint) noexcept {
    char units[4];
    size_t count = 0;
    if (codePoint < 0x80) {
        units[count++] = static_cast<char>(codePoint);
    } else if (codePoint < 0x800) {
        units[count++] = static_cast<char>(0xC0 | (codePoint >> 6));
        units[count++] = static_cast<char>(0x80 | (codePoint & 0x3F));
    } else if (codePoint < 0x10000) {
        units[count++] = static_cast<char>(0xE0 | (codePoint >> 12));
        units[count++] = static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F));
        units[count++] = static_cast<char>(0x80 | (codePoint & 0x3F));
    } else {
        units[count++] = static_cast<char>(0xF0 | (codePoint >> 18));
        units[count++] = static_cast<char>(0x80 | ((codePoint >> 12) & 0x3F));
        units[count++] = static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F));
        units[count++] = static_cast<char>(0x80 | (codePoint & 0x3F));
    }
    Store(units, count);
}

template <>
inline void Writer<char16_t>::Put(uint32_t codePoint) noexcept {
    if (codePoint < 0x10000) {
        const char16_t unit = static_cast<char16_t>(codePoint);
        Store(&unit, 1);
        return;
    }
    const uint32_t offset = codePoint - 0x10000;
    const char16_t units[2] = {
        static_cast<char16_t>(0xD800 | (offset >> 10)),
        static_cast<char16_t>(0xDC00 | (offset & 0x3FF))};
    Store(units, 2);
}

template <>
inline void Writer<char32_t>::Put(uint32_t codePoint) noexcept {
    const char32_t unit = static_cast<char32_t>(codePoint);
    Store(&unit, 1);
}

// Passes each code point to a callback and counts them.
class SinkWriter : public Output<SinkWriter> {
    CodePointSink _sink;
    void* _context;
    size_t _length;

public:
    SinkWriter(CodePointSink sink, void* context) noexcept
        : _sink(sink), _context(context), _length(0) {}

    void Put(uint32_t codePoint) noexcept {
        if (_sink != nullptr) {
            _sink(codePoint, _context);
        }
        ++_length;
    }

    size_t Length() const noexcept { return _length; }
};

// Decodes code points from a null-terminated CharT string; malformed UTF-8
// or UTF-16 decodes as U+FFFD, which no parser accepts.
template <typename CharT>
class Reader {
    const CharT* _text;

public:
    explicit Reader(const CharT* text) noexcept : _text(text) {}

    // Returns the next code point without consuming it (0 at the end).
    uint32_t Peek() const noexcept {
        size_t units = 0;
        return Decode(units);
    }

    void Advance() noexcept {
        size_t units = 0;
        Decode(units);
        _text += units;
    }

    uint32_t Decode(size_t& units) const noexcept;
};

template <>
inline uint32_t Reader<char32_t>::Decode(size_t& units) const noexcept {
    units = _text[0] == 0 ? 0 : 1;
    return static_cast<uint32_t>(_text[0]);
}

template <>
inline uint32_t Reader<char16_t>::Decode(size_t& units) const noexcept {
    const uint32_t first = _text[0];
    units = first == 0 ? 0 : 1;
    if (first >= 0xD800 && first <= 0xDBFF) {
        const uint32_t second = _text[1];
        if (second >= 0xDC00 && second <= 0xDFFF) {
            units = 2;
            return 0x10000 + ((first - 0xD800) << 10) + (second - 0xDC00);
        }
        return 0xFFFD;
    }
    return (first >= 0xDC00 && first <= 0xDFFF) ? 0xFFFD : first;
}

template <>
inline uint32_t Reader<char>::Decode(size_t& units) const noexcept {
    const uint32_t lead = static_cast<unsigned char>(_text[0]);
    if (lead < 0x80) {
        units = lead == 0 ? 0 : 1;
        return lead;
    }
    const size_t length = lead >= 0xF0 ? 4 : lead >= 0xE0 ? 3 : lead >= 0xC0 ? 2 : 0;
    if (length == 0 || lead > 0xF4) {
        units = 1;
        return 0xFFFD;
    }
    uint32_t codePoint = lead & (0x7F >> length);
    for (size_t i = 1; i < length; ++i) {
        const uint32_t next = static_cast<unsigned char>(_text[i]);
        if ((next & 0xC0) != 0x80) {
            units = i;
            return 0xFFFD;
        }
        codePoint = (codePoint << 6) | (next & 0x3F);
    }
    units = length;
    return codePoint;
}

} // namespace Detail
} // namespace Notation
} // namespace MCC

#endif // MCC_NOTATION_WRITER_H
