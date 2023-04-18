#ifndef MCC_MIDI_PORT_H
#define MCC_MIDI_PORT_H

	#include <MCC_BuildSettings.h>

	namespace MusicCompositionCore
	{
		namespace Communications
		{
			namespace Midi
			{
				
			}
		}
	}

	#if defined (MCC_UART_MIDI_ENABLED)
		#include "UartMidi/UartMidi.h"
	#endif

#endif//MCC_MIDI_PORT_H