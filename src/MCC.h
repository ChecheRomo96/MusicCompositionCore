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

#endif // MCC_H
