#include <MCC/Pitch.h>

// Compile-time checks evaluated by every target, including embedded
// toolchains whose unit tests do not run (SPEC-EMB-2, SPEC-EMB-3).
namespace {

static_assert(sizeof(MCC::Letter) == 1, "Letter must fit in 1 byte");
static_assert(sizeof(MCC::Accidental) == 1, "Accidental must fit in 1 byte");
static_assert(sizeof(MCC::ChromaticClass) == 1,
    "ChromaticClass must fit in 1 byte");
static_assert(sizeof(MCC::PitchClass) <= 2,
    "PitchClass must fit in 2 bytes");

static_assert(MCC::PitchClass(MCC::Letter::B, MCC::Accidental::Sharp())
    .ChromaticClass() == MCC::ChromaticClass(0), "B# must be class 0");
static_assert(MCC::PitchClass(MCC::Letter::C, MCC::Accidental::Flat())
    .ChromaticClass() == MCC::ChromaticClass(11), "Cb must be class 11");
static_assert(!MCC::PitchClass(MCC::Letter::C, MCC::Accidental::QuadrupleSharp())
    .Altered(1).IsValid(), "Accidental overflow must be invalid");

} // namespace
