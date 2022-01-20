#ifndef MCC_CORE_H
#define MCC_CORE_H
	
    #include <MCC_BuildSettings.h>
    #include <MCC.h>

	namespace MusicCompositionCore
    {
        namespace Core
        {
            void Start();
            uint32_t Micros();
        }
    }
    
    namespace MCC_Core = MusicCompositionCore::Core;

    #if defined(MCC_UTILITY_CORE_ENABLED)
        #include "UtilityCore/UtilityCore.h"
    #endif

    #if defined(MCC_MUSICAL_CORE_ENABLED)
        #include "MusicalCore/MusicalCore.h"
    #endif

    //#include "MidiCore/MidiCore.h"
    //#include "MusicalUtilityCore/MusicalUtilityCore.h"

#endif//MCC_CORE_H
