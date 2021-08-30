#ifndef MCC_BUILD_SETTINGS_H
#define MCC_BUILD_SETTINGS_H

    #include "MCC_Setup.h"
    #include "MCC_GlobalDefinitions.h"

    ///////////////////////////////////////////////////////////////////////////////////
    // Arduino IDE

        #if defined(ARDUINO)
            
            #include <CPVector.h>
            #include <CPString.h>
            
            #define PROGMEM_MACRO PROGMEM
            
            #define MCC_VERSION "0.0.1"

            #define MCC_CORE_ENABLED
    //
    ///////////////////////////////////////////////////////////////////////////////////
    // PSOC Creator

        #elif defined(PSOC_CREATOR)

            #ifdef __cplusplus
                extern "C" {
                    #include "project.h"   
                }
            #else
                #include "project.h"
            #endif
            
            #include <CPVector.h>
            #include <CPString.h>

            #define PROGMEM_MACRO
            #define constexpr const
    //
    ///////////////////////////////////////////////////////////////////////////////////
    // Building as a target for a desktop system

        #elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(__APPLE__) || defined(linux)

            #include <iostream>
            #include <chrono>

            #include <CPVector.h>
            #include <CPString.h>

            #define PROGMEM_MACRO
                
            //#include <RtMidi.h>


    //
    ///////////////////////////////////////////////////////////////////////////////////

    #else
    #   error "Unknown compiler"
    #endif

#endif//MCC_BUILD_SETTINGS_H
