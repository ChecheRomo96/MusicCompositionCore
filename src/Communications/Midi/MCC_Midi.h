#ifndef MCC_MIDI_H
#define MCC_MIDI_H

	#include <MCC_BuildSettings.h>

	namespace MusicCompositionCore::Communications::Midi
	{

		typedef uint8_t PortType;
		namespace PortTypes
		{
			static constexpr PortType InvalidType = 0xFF;
			static constexpr PortType UartMidi = 1u;
			static constexpr PortType RtMidi = 2u;
		}

		class Port;
		class SystemPortHandler;

    	#if defined(MCC_UART_IN_ENABLED)
			namespace UartMidi
			{
				class Port;
    		}
    	#endif
	}


	#include "SystemPorts/Midi_SystemPorts.h"

	#if defined(MCC_UART_MIDI_ENABLED)
		#include "UartMidi/UartMidi.h"
	#endif

	#if defined(MCC_RTMIDI_ENABLED)
		#include "RtMidi/MCC_RtMidi.h"
	#endif
	

	#include "Port/MidiPort.h"
	

#endif//MCC_MIDI_H
