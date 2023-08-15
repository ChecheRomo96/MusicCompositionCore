#ifndef MCC_RTMIDI_H
#define MCC_RTMIDI_H

	#include <MCC_BuildSettings.h>
	
	namespace MusicCompositionCore::Communications::Midi::RtMidi
	{
		class SystemPort;
		class SystemPortHandler;

		class VirtualPort;
		class VirtualPortHandler;
	}

    //#include "../MCC_Midi.h"

	//#include "SystemPorts/UartMidi_SystemPorts.h"
	#if defined MCC_RTMIDI_VIRTUAL_PORT_ENABLED
		#include "Virtual/RtMidi_Virtual.h"
	#endif

#endif//MCC_RTMIDI_H
