
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	 _  _ _  _ ____ __ ___     ___ __  _  _ ____  __  ____ __ ____ __ __  __ _     ___ __ ____ ____   //
	//	( \/ / )( / ___(  / __)   / __/  \( \/ (  _ \/  \/ ___(  (_  _(  /  \(  ( \   / __/  (  _ (  __)  //
	//	/ \/ ) \/ \___ \)( (__   ( (_(  O / \/ \) __(  O \___ \)(  )(  )(  O /    /  ( (_(  O )   /) _)   //
	//	\_)(_\____(____(__\___)   \___\__/\_)(_(__)  \__/(____(__)(__)(__\__/\_)__)   \___\__(__\_(____)  //
	//																									  //
	////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MUSIC_COMPOSITION_CORE_H
#define MUSIC_COMPOSITION_CORE_H

	#include "MCC_BuildSettings.h"

	namespace MusicCompositionCore
	{
		void Start();
	
		#if defined(ARDUINO)
			void Arduino_Start();
		#elif defined(PSOC_CREATOR)
			void PSOC_Start();
		#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(__APPLE__) || defined(linux)
		    extern std::chrono::high_resolution_clock::time_point StartTime;
			void CPP_Start();
		#endif

        void Service();

	}

    namespace MCC = MusicCompositionCore;

	#if defined (MCC_MUSICAL_NOTE_ENABLED)
		#include "MusicalNote/MusicalNote.h"
	#endif

	#if defined (MCC_MUSICAL_INTERVAL_ENABLED)
		#include "MusicalInterval/MusicalInterval.h"
	#endif

	#if defined (MCC_MUSICAL_SCALE_ENABLED)
	    #include "MusicalScale/MusicalScale.h"
	#endif

	#include "MidiProtocol/MCC_MidiProtocol.h"
	
    #if defined(MCC_MIDI_NOTE_ENABLED)
        #include "MidiNote/MidiNote.h"
    #endif

    #if defined(MCC_MIDI_MESSAGE_ENABLED)
        #include "MidiMessage/MidiMessage.h"
    #endif

	
	//#include "MidiDevices/MidiDevices.h"
    //#include "ServiceHandler/ServiceHandler.h"


#endif//MUSIC_COMPOSITION_CORE_H
