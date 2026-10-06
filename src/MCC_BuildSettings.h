#ifndef MCC_BUILD_SETTINGS_H
#define MCC_BUILD_SETTINGS_H

// The libraries this one depends on. Including them from their src root
// lets the Arduino builder find them from any header of this library.
#include <Foundation_BuildSettings.h>

#ifndef MCC_VERSION
    #define MCC_VERSION "0.6.0"
#endif

#ifndef MCC_CPLUSPLUS
    #if defined(_MSVC_LANG)
        #define MCC_CPLUSPLUS _MSVC_LANG
    #elif defined(__cplusplus)
        #define MCC_CPLUSPLUS __cplusplus
    #else
        #define MCC_CPLUSPLUS 0L
    #endif
#endif

#if !defined(DOXYGEN) && defined(ARDUINO) && (MCC_CPLUSPLUS < 201103L)
    #error "MCC requires C++11 or newer for Arduino source builds"
#elif !defined(DOXYGEN) && !defined(ARDUINO) && (MCC_CPLUSPLUS < 201703L)
    #error "MCC requires C++17 or newer"
#endif

// C++14 relaxed constexpr permits local variables, branches, and loops.
// Preserve constexpr evaluation on modern toolchains and expose the same API
// as ordinary inline functions to stock Arduino cores that compile as C++11.
#ifndef MCC_CONSTEXPR14
    #if MCC_CPLUSPLUS >= 201402L
        #define MCC_CONSTEXPR14 constexpr
    #else
        #define MCC_CONSTEXPR14 inline
    #endif
#endif

#endif // MCC_BUILD_SETTINGS_H
