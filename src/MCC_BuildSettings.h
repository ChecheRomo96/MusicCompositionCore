#ifndef MCC_BUILD_SETTINGS_H
#define MCC_BUILD_SETTINGS_H

#ifndef MCC_VERSION
    #define MCC_VERSION "0.1.0"
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

#if !defined(DOXYGEN) && (MCC_CPLUSPLUS < 201703L)
    #error "MCC requires C++17 or newer"
#endif

#endif // MCC_BUILD_SETTINGS_H
