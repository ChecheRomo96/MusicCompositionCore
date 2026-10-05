#ifndef MCC_SCALE_TOP_LEVEL_H
#define MCC_SCALE_TOP_LEVEL_H

#include <MCC_BuildSettings.h>

#if __has_include(<MCC/Scale.h>)
    #ifndef MCC_SCALE
        #define MCC_SCALE
    #endif

    #include <MCC/Scale.h>
#endif

#endif // MCC_SCALE_TOP_LEVEL_H
