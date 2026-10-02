#include <MCC.h>

// SPEC-EMB-1..2: size budgets and trivial copyability of the value types,
// checked when the library is built for every target, AVR and Arm included,
// not only by the desktop unit tests. Uses compiler builtins so no standard
// library header is needed on embedded targets.
#define MCC_CHECK_VALUE_TYPE(Type, MaximumBytes)                                  \
    static_assert(sizeof(Type) <= (MaximumBytes), #Type " exceeds its size budget"); \
    static_assert(__is_trivially_copyable(Type), #Type " must be trivially copyable")

#if defined(MCC_PITCH)
MCC_CHECK_VALUE_TYPE(MCC::Accidental, 1);
MCC_CHECK_VALUE_TYPE(MCC::PitchClass, 1);
MCC_CHECK_VALUE_TYPE(MCC::NoteName, 2);
MCC_CHECK_VALUE_TYPE(MCC::ChromaticIndex, 2);
MCC_CHECK_VALUE_TYPE(MCC::Pitch, 4);
#endif

#if defined(MCC_INTERVAL)
MCC_CHECK_VALUE_TYPE(MCC::IntervalQuality, 1);
MCC_CHECK_VALUE_TYPE(MCC::IntervalNumber, 2);
MCC_CHECK_VALUE_TYPE(MCC::Interval, 4);
#endif

#if defined(MCC_TUNING)
MCC_CHECK_VALUE_TYPE(MCC::Tuning, 8);
MCC_CHECK_VALUE_TYPE(MCC::EqualTemperament, 8);
#endif

#if defined(MCC_SCALE)
MCC_CHECK_VALUE_TYPE(MCC::ScalePattern, 8);
MCC_CHECK_VALUE_TYPE(MCC::Scale, 12);
#endif

#if defined(MCC_CHORD)
MCC_CHECK_VALUE_TYPE(MCC::ChordPattern, 8);
MCC_CHECK_VALUE_TYPE(MCC::Chord, 12);
#endif

#if defined(MCC_KEY)
MCC_CHECK_VALUE_TYPE(MCC::KeySignature, 1);
MCC_CHECK_VALUE_TYPE(MCC::Key, 4);
#endif

#if defined(MCC_RHYTHM)
MCC_CHECK_VALUE_TYPE(MCC::NoteValue, 2);
MCC_CHECK_VALUE_TYPE(MCC::Note, 6);
MCC_CHECK_VALUE_TYPE(MCC::Meter, 3);
#endif

#undef MCC_CHECK_VALUE_TYPE
