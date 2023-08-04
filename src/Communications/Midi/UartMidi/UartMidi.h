#ifndef MCC_UART_MIDI_H
#define MCC_UART_MIDI_H

	#include <MCC_BuildSettings.h>
	
	namespace MusicCompositionCore::Communications::Midi::UartMidi
	{
		class Port;
		class SystemPortHandler;
	}

    #include "../MCC_Midi.h"

	#include "SystemPorts/UartMidi_SystemPorts.h"
	#include "Port/UartMidiPort.h"

#endif//MCC_UART_MIDI_H
