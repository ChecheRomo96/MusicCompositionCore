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

    #include "UtilityCore/UtilityCore.h"
    #include "MusicalCore/MusicalCore.h"
    //#include "MidiCore/MidiCore.h"
    //#include "MusicalUtilityCore/MusicalUtilityCore.h"

#endif//MCC_CORE_H
