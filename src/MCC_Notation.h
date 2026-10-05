#ifndef MCC_NOTATION_TOP_LEVEL_H
#define MCC_NOTATION_TOP_LEVEL_H

#include <MCC_BuildSettings.h>

#if __has_include(<MCC/Notation.h>)
    #ifndef MCC_NOTATION
        #define MCC_NOTATION
    #endif

    #include <MCC/Notation.h>
#endif

#endif // MCC_NOTATION_TOP_LEVEL_H
