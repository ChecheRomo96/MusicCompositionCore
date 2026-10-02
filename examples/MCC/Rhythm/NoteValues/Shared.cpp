#include "Shared.h"

#include <MCC_Rhythm.h>

namespace MCCExamples {
namespace Rhythm {
namespace NoteValues {

namespace {

void Unsigned(uint16_t value, char* buffer) noexcept {
    char digits[6];
    int count = 0;
    do {
        digits[count++] = static_cast<char>('0' + value % 10u);
        value = static_cast<uint16_t>(value / 10u);
    } while (value != 0u);

    int length = 0;
    while (count > 0) {
        buffer[length++] = digits[--count];
    }
    buffer[length] = '\0';
}

void Padded(PrintFunction print, const char* text, int width) noexcept {
    int length = 0;
    while (text[length] != '\0') {
        ++length;
    }
    print(text);
    for (int index = length; index < width; ++index) {
        print(" ");
    }
}

void Row(PrintFunction print, const char* expression, MCC::NoteValue value) noexcept {
    char number[6];
    print("   ");
    Padded(print, expression, 38);
    Unsigned(value.Numerator(), number);
    print(number);
    print("/");
    Unsigned(value.Denominator(), number);
    print(number);
    print("\n");
}

} // namespace

void Run(PrintFunction print) noexcept {
    print("========================================\n");
    print(" MCC :: Rhythm / Note Values\n");
    print("========================================\n");
    print("\nPURPOSE\n");
    print("Represent written note lengths exactly, without tempo or floating point.\n");

    print("\n[1] NAMED VALUES\n\n");
    Row(print, "NoteValue::Whole()", MCC::NoteValue::Whole());
    Row(print, "NoteValue::Half()", MCC::NoteValue::Half());
    Row(print, "NoteValue::Quarter()", MCC::NoteValue::Quarter());
    Row(print, "NoteValue::Eighth()", MCC::NoteValue::Eighth());
    Row(print, "NoteValue::Sixteenth()", MCC::NoteValue::Sixteenth());

    print("\n[2] AUGMENTATION DOTS\n\n");
    Row(print, "NoteValue::Quarter()", MCC::NoteValue::Quarter());
    Row(print, "NoteValue::Quarter(1)", MCC::NoteValue::Quarter(1));
    Row(print, "NoteValue::Quarter(2)", MCC::NoteValue::Quarter(2));
    Row(print, "NoteValue::Quarter(3)", MCC::NoteValue::Quarter(3));
    Row(print, "NoteValue::Quarter(4)", MCC::NoteValue::Quarter(4));

    print("\nTAKEAWAY\n");
    print("Dots remain part of the written value; duration stays an exact\n");
    print("fraction of a whole note.\n");
    print("========================================\n");
}

} // namespace NoteValues
} // namespace Rhythm
} // namespace MCCExamples
