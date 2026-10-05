#ifndef MCC_CHORD_TOP_LEVEL_H
#define MCC_CHORD_TOP_LEVEL_H

#include <MCC_BuildSettings.h>

#if __has_include(<MCC/Chord.h>)
    #ifndef MCC_CHORD
        #define MCC_CHORD
    #endif

    #include <MCC/Chord.h>
#endif

#endif // MCC_CHORD_TOP_LEVEL_H
