#ifndef SCALE_FLASH_DEFINITIONS
#define SCALE_FLASH_DEFINITIONS

#include <MCC_BuildSettings.h>

#include "../../MusicalNote/MusicalNote.h"
#include "../../MusicalInterval/MusicalInterval.h"
#include "../ScaleProperties/ScaleProperties.h"

namespace MusicCompositionCore
{
    namespace Core
    {
        namespace MusicalCore
        {
            namespace MusicalScale
            {
                
                namespace Flash
                {

                    struct Container_Notes
                    {
                        const uint8_t ID;
                        const uint8_t Properties;
                        const char* Name;
                        const uint8_t* NoteTokens;
                    };
                    
                    struct Container_Mapping
                    {
                        const uint8_t ID;
                        const uint8_t Properties;
                        const char* Name;
                        const uint16_t Mapping;
                        const uint8_t* GenericInterval;
                    };

                    struct Container
                    {
                        const Container_Notes* NotesPointer;
                        const Container_Mapping* MappingPointer;
                    };
                    
                    typedef struct Container_Notes      Container_Notes;
                    typedef struct Container_Intervals  Container_Intervals;
                    typedef struct Container            Container;
                    typedef struct ContainerArray       ContainerArray;

                    //////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Scales

                        namespace Scales
                        {
                            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

                                #include "ScaleDefinitions\ScaleDefinitions.h"

                                #ifdef _WIN64
                                  //define something for Windows (64-bit only)
                                #else
                                  //define something for Windows (32-bit only)
                                #endif

                            #elif __APPLE__

                                #include <TargetConditionals.h>

                                #include "ScaleDefinitions/ScaleDefinitions.h"

                                #if TARGET_IPHONE_SIMULATOR
                                     // iOS Simulator
                                #elif TARGET_OS_IPHONE
                                    // iOS device
                                #elif TARGET_OS_MAC
                                    // Other kinds of Mac OS
                                #else
                                #   error "Unknown Apple platform"
                                #endif

                            #elif ARDUINO

                                #include "ScaleDefinitions/ScaleDefinitions.h"

                            #elif __linux__
                                // linux
                            #elif __unix__ // all unices not caught above
                                // Unix
                            #elif defined(_POSIX_VERSION)
                                // POSIX
                            #else
                            #   error "Unknown compiler"
                            #endif
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Scale Arrays
                    
                        namespace ScaleArrays
                        {

                            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

                                #include "ScaleArrays\ScaleArrays.h"

                                #ifdef _WIN64
                                  //define something for Windows (64-bit only)
                                #else
                                  //define something for Windows (32-bit only)
                                #endif

                            #elif __APPLE__

                                #include <TargetConditionals.h>

                                #include "ScaleArrays/ScaleArrays.h"

                                #if TARGET_IPHONE_SIMULATOR
                                     // iOS Simulator
                                #elif TARGET_OS_IPHONE
                                    // iOS device
                                #elif TARGET_OS_MAC
                                    // Other kinds of Mac OS
                                #else
                                #   error "Unknown Apple platform"
                                #endif

                            #elif ARDUINO

                                #include "ScaleArrays/ScaleArrays.h"

                            #elif __linux__
                                // linux
                            #elif __unix__ // all unices not caught above
                                // Unix
                            #elif defined(_POSIX_VERSION)
                                // POSIX
                            #else
                            #   error "Unknown compiler"
                            #endif
                        }
                    //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////
                    
                }
            }
        }
    }
}

#endif//SCALE_FLASH_DEFINITIONS
