#ifndef MCC_COMMUNICATIONS_H
#define MCC_COMMUNICATIONS_H

	#include <MCC_BuildSettings.h>

	namespace MusicCompositionCore
	{
		namespace Communications
		{

		}
	}

	namespace MCC_Communications = MusicCompositionCore::Communications;

	#if defined(MCC_MIDI_PORT_ENABLED)
		#include "Midi/MidiPort.h"
	#endif

#endif//MCC_COMMUNICATIONS_H
