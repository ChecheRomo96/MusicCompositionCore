#include <MCC/Tuning.h>

// Compile-time checks evaluated by every target, including embedded
// toolchains whose unit tests do not run (SPEC-OCT-2, SPEC-EMB-3).
namespace {

static_assert(MCC::EqualTemperament::Standard()
    .Frequency(MCC::Pitch(MCC::Letter::A, 4)) == 440.0f, "A4 must be 440 Hz");
static_assert(MCC::EqualTemperament::Standard()
    .Frequency(MCC::Pitch(MCC::Letter::A, 5)) == 880.0f, "A5 must be 880 Hz");

} // namespace
