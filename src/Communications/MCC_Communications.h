#ifndef MCC_COMMUNICATIONS_H
#define MCC_COMMUNICATIONS_H

	#include <MCC_BuildSettings.h>

	namespace MusicCompositionCore::Communications{}
	namespace MCC_Communications = MusicCompositionCore::Communications;

	#if defined(MCC_UART_PORT_ENABLED)
		#include "Uart/Uart.h"
	#endif
	
	#if defined(MCC_MIDI_PORT_ENABLED)
		#include "Midi/MCC_Midi.h"
	#endif


#endif//MCC_COMMUNICATIONS_H
