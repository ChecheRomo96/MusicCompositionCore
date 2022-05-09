#ifndef MCC_BUILD_SETTINGS_H
#define MCC_BUILD_SETTINGS_H

    #include "MCC_Setup.h"
    #include "MCC_GlobalDefinitions.h"
    #include <stdint.h>

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // MCC Version

        #ifndef MCC_VERSION
            #define MCC_VERSION "0.0.1"
        #endif

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Arduino IDE

        #if defined(ARDUINO)
            #include <Arduino.h>
        #endif
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // PSOC Creator

        #if defined(PSOC_CREATOR)

            /*#ifdef __cplusplus
                extern "C" {
                    #include "project.h"   
                }
            #else
                #include "project.h"
            #endif*/
            
            #define PROGMEM_MACRO
            #define constexpr const
        #endif
    //
    ///////////////////////////////////////////////////////////////////////////////////
    // Building as a target for a desktop system

        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(__APPLE__) || defined(linux)

            #include <iostream>
            #include <chrono>

            #define PROGMEM_MACRO
                
            //#include <RtMidi.h>
        #endif


    //
    ///////////////////////////////////////////////////////////////////////////////////

#endif//MCC_BUILD_SETTINGS_H
