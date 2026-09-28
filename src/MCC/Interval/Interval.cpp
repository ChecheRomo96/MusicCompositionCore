#include <MCC/Interval.h>

// Compile-time checks evaluated by every target, including embedded
// toolchains whose unit tests do not run (SPEC-EMB-2, SPEC-INT-7).
namespace {

static_assert(sizeof(MCC::Interval) <= 4, "Interval must fit in 4 bytes");
static_assert(sizeof(MCC::IntervalQuality) == 1,
    "IntervalQuality must fit in 1 byte");

constexpr MCC::Interval kMajorThird(
    MCC::IntervalQuality::Major(), MCC::IntervalNumber(3));
static_assert(kMajorThird.Semitones() == 4, "A major third is 4 semitones");
static_assert(MCC::Pitch(MCC::Letter::E, 4) + kMajorThird
    == MCC::Pitch(MCC::Letter::G, MCC::Accidental::Sharp(), 4),
    "E4 + M3 must be G#4");

} // namespace
