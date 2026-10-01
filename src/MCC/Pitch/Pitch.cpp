#include <MCC/Pitch.h>

// Compile-time checks evaluated by every target, including embedded
// toolchains whose unit tests do not run (SPEC-EMB-2, SPEC-EMB-3).
namespace {

static_assert(sizeof(MCC::Letter) == 1, "Letter must fit in 1 byte");
static_assert(sizeof(MCC::Accidental) == 1, "Accidental must fit in 1 byte");
static_assert(sizeof(MCC::PitchClass) == 1,
    "PitchClass must fit in 1 byte");
static_assert(sizeof(MCC::NoteName) <= 2,
    "NoteName must fit in 2 bytes");
static_assert(sizeof(MCC::ChromaticIndex) == 2,
    "ChromaticIndex must fit in 2 bytes");
static_assert(sizeof(MCC::Pitch) <= 4, "Pitch must fit in 4 bytes");

#if MCC_CPLUSPLUS >= 201402L
    static_assert(MCC::Pitch(MCC::Letter::C, 4).ChromaticIndex()
        == MCC::ChromaticIndex(60), "C4 must be 60");
    static_assert(MCC::Pitch(MCC::Letter::B, MCC::Accidental::Sharp(), 3)
        .ChromaticIndex() == MCC::ChromaticIndex(60), "B#3 must sound as C4");
    static_assert(MCC::Pitch(MCC::Letter::C, MCC::Accidental::QuadrupleFlat(), -128)
        .ChromaticIndex() == MCC::ChromaticIndex(MCC::ChromaticIndex::Minimum),
        "Cbbbb-128 must be the lowest index");
    static_assert(MCC::Pitch(MCC::Letter::B, MCC::Accidental::QuadrupleSharp(), 127)
        .ChromaticIndex() == MCC::ChromaticIndex(MCC::ChromaticIndex::Maximum),
        "B####127 must be the highest index");

    static_assert(MCC::NoteName(MCC::Letter::B, MCC::Accidental::Sharp())
        .PitchClass() == MCC::PitchClass(0), "B# must be class 0");
    static_assert(MCC::NoteName(MCC::Letter::C, MCC::Accidental::Flat())
        .PitchClass() == MCC::PitchClass(11), "Cb must be class 11");
    static_assert(!MCC::NoteName(MCC::Letter::C, MCC::Accidental::QuadrupleSharp())
        .Altered(1).IsValid(), "Accidental overflow must be invalid");
#endif

} // namespace
