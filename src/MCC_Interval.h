#ifndef MCC_INTERVAL_TOP_LEVEL_H
#define MCC_INTERVAL_TOP_LEVEL_H

#include <MCC_BuildSettings.h>

#if __has_include(<MCC/Interval.h>)
    #ifndef MCC_INTERVAL
        #define MCC_INTERVAL
    #endif

    #include <MCC/Interval.h>
#endif

#endif // MCC_INTERVAL_TOP_LEVEL_H
