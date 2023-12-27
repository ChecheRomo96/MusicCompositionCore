#ifndef SCALE_FLASH_DEFINITIONS
#define SCALE_FLASH_DEFINITIONS

#include <MCC_BuildSettings.h>

#include "../../MusicalNote/MusicalNote.h"
#include "../../MusicalInterval/MusicalInterval.h"
#include "../ScaleProperties/ScaleProperties.h"

namespace MusicCompositionCore
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
                   #include "ScaleDefinitions/ScaleDefinitions.h"
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////
            // Scale Arrays
            
                namespace ScaleArrays
                {
                    #include "ScaleArrays\ScaleArrays.h"
                }
            //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////
            
        }
    }
}

#endif//SCALE_FLASH_DEFINITIONS
