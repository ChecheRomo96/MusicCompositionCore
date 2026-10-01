#ifndef MCC_H
#define MCC_H

#include <MCC_BuildSettings.h>

#if __has_include(<MCC_Core.h>)
    #include <MCC_Core.h>
#endif

#if __has_include(<MCC_Pitch.h>)
    #include <MCC_Pitch.h>
#endif

#if __has_include(<MCC_Interval.h>)
    #include <MCC_Interval.h>
#endif

#if __has_include(<MCC_Tuning.h>)
    #include <MCC_Tuning.h>
#endif

#if __has_include(<MCC_Scale.h>)
    #include <MCC_Scale.h>
#endif

#if __has_include(<MCC_Chord.h>)
    #include <MCC_Chord.h>
#endif

#if __has_include(<MCC_Key.h>)
    #include <MCC_Key.h>
#endif

#if __has_include(<MCC_Notation.h>)
    #include <MCC_Notation.h>
#endif

#endif // MCC_H
