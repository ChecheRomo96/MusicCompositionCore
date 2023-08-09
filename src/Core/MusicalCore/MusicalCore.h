#ifndef MCC_MUSICAL_CORE_H
#define MCC_MUSICAL_CORE_H

	#include <MCC_BuildSettings.h>

	namespace MusicCompositionCore
	{
		namespace Core
		{
			namespace MusicalCore
			{
			}
		}
	}

	namespace MCC_MusicalCore = MusicCompositionCore::Core::MusicalCore;

	#if defined (MCC_MUSICAL_NOTE_ENABLED)
		#include "MusicalNote/MusicalNote.h"
	#endif

	#if defined (MCC_MUSICAL_INTERVAL_ENABLED)
		#include "MusicalInterval/MusicalInterval.h"
	#endif

	#if defined (MCC_MUSICAL_SCALE_ENABLED)
	    #include "MusicalScale/MusicalScale.h"
	#endif

	//#include "MusicalChord/MusicalChord.h"


#endif//MCC_MUSICAL_CORE_H
