#ifndef MCC_TUNING_TOP_LEVEL_H
#define MCC_TUNING_TOP_LEVEL_H

#include <MCC_BuildSettings.h>

#if __has_include(<MCC/Tuning.h>)
    #ifndef MCC_TUNING
        #define MCC_TUNING
    #endif

    #include <MCC/Tuning.h>
#endif

#endif // MCC_TUNING_TOP_LEVEL_H
