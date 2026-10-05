#ifndef MCC_CORE_TOP_LEVEL_H
#define MCC_CORE_TOP_LEVEL_H

#include <MCC_BuildSettings.h>

#if __has_include(<MCC/Core.h>)
    #ifndef MCC_CORE
        #define MCC_CORE
    #endif

    #include <MCC/Core.h>
#endif

#endif // MCC_CORE_TOP_LEVEL_H
