#include "Shared.h"

#include <MCC_Rhythm.h>

namespace MCCExamples {
namespace Rhythm {
namespace Meters {

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

const char* Kind(MCC::Meter meter) noexcept {
    switch (meter.Kind()) {
        case MCC::MeterKind::Simple: return "simple";
        case MCC::MeterKind::Compound: return "compound";
        case MCC::MeterKind::Irregular: return "irregular";
        default: return "invalid";
    }
}

void Fraction(
    PrintFunction print, uint16_t numerator, uint16_t denominator) noexcept {
    char text[6];
    Unsigned(numerator, text);
    print(text);
    print("/");
    Unsigned(denominator, text);
    print(text);
}

void Row(PrintFunction print, const char* expression, MCC::Meter meter) noexcept {
    char text[6];
    print("   ");
    print(expression);
    print("\n      signature: ");
    Fraction(print, meter.Numerator(), meter.Denominator());
    print(" | ");
    print(Kind(meter));
    print(" | measure: ");
    Fraction(print, meter.MeasureNumerator(), meter.MeasureDenominator());
    if (meter.BeatCount() != 0u) {
        print(" | beats: ");
        Unsigned(meter.BeatCount(), text);
        print(text);
        print(" x ");
        Fraction(print,
            meter.BeatValue().Numerator(), meter.BeatValue().Denominator());
    } else {
        print(" | grouping: explicit");
    }
    print("\n");
}

} // namespace

void Run(PrintFunction print) noexcept {
    print("========================================\n");
    print(" MCC :: Rhythm / Meters\n");
    print("========================================\n");
    print("\nPURPOSE\n");
    print("Keep the written signature and derive beats without runtime timing.\n");

    print("\n[1] SIMPLE, COMPOUND AND IRREGULAR\n\n");
    Row(print, "Meter::CommonTime()", MCC::Meter::CommonTime());
    Row(print, "Meter::Simple(3, NoteValue::Quarter())",
        MCC::Meter::Simple(3, MCC::NoteValue::Quarter()));
    Row(print, "Meter(6, 8)", MCC::Meter(6, 8));
    Row(print, "Meter::Compound(4, NoteValue::Quarter(1))",
        MCC::Meter::Compound(4, MCC::NoteValue::Quarter(1)));
    Row(print, "Meter(5, 8)", MCC::Meter(5, 8));

    print("\n[2] WRITING VERSUS MEASURE LENGTH\n\n");
    print("   Meter(3, 4) == Meter(6, 8): false\n");
    print("   HasSameMeasureDuration(3/4, 6/8): true\n");

    print("\nTAKEAWAY\n");
    print("The signature stays written; irregular grouping is never guessed.\n");
    print("========================================\n");
}

} // namespace Meters
} // namespace Rhythm
} // namespace MCCExamples
