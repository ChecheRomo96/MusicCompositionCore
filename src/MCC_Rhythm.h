#ifndef MCC_RHYTHM_TOP_LEVEL_H
#define MCC_RHYTHM_TOP_LEVEL_H

#include <MCC_BuildSettings.h>

#if __has_include(<MCC/Rhythm.h>)
    #ifndef MCC_RHYTHM
        #define MCC_RHYTHM
    #endif
    #include <MCC/Rhythm.h>
#endif

#endif // MCC_RHYTHM_TOP_LEVEL_H
