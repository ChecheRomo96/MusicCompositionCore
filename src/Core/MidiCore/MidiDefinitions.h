#ifndef MCC_MIDI_DEFINITIONS_H
#define MCC_MIDI_DEFINITIONS_H

	// MIDI MESSAGE STATUS ID
	#include <MCC_BuildSettings.h>

	namespace MusicCompositionCore
	{
		namespace Core
		{
			namespace MidiCore
			{
				namespace Protocol
				{
					// Channel Voice Messages
					static constexpr uint8_t NoteOff = 0x80;
					static constexpr uint8_t NoteOn = 0x90;
					static constexpr uint8_t AfterTouch = 0xA0;
					static constexpr uint8_t ControlChange = 0xB0;
					static constexpr uint8_t ProgramChange = 0xC0;
					static constexpr uint8_t ChannelPressure = 0xD0;
					static constexpr uint8_t PitchBend = 0xE0;

					//System Messages
					static constexpr uint8_t SystemMessage = 0xF0;
					static constexpr uint8_t SystemExclusive = 0x0;
					static constexpr uint8_t MTC_QuarterFrame = 0x1;
					static constexpr uint8_t SongPosition = 0x2;
					static constexpr uint8_t SongSelect = 0x3;
					static constexpr uint8_t TuningRequest = 0x6;
					static constexpr uint8_t SystemExclusiveEnd = 0x7;

					// Real Time Messages
					static constexpr uint8_t TimingTick = 0x8;
					static constexpr uint8_t Start = 0xA;
					static constexpr uint8_t Continue = 0xB;
					static constexpr uint8_t Stop= 0xC;
					static constexpr uint8_t ActiveSensing = 0xE;
					static constexpr uint8_t SystemReset = 0xF;
				}

				
				static constexpr uint8_t MidiNoteRange = 128u;
				static constexpr uint8_t InvalidMidiNote = 128u;
				static constexpr uint8_t MidiVelocityRange = 128u;
				static constexpr uint8_t InvalidMidiVelocity = 128u;
				static constexpr uint8_t MidiChannelRange = 16u;
				static constexpr uint8_t InvalidMidiChannel = 16u;
				
			}
		}
	}
    
    namespace MCC_MidiCore = MusicCompositionCore::Core::MidiCore;
    namespace MCC_MidiProtocol = MusicCompositionCore::Core::MidiCore::Protocol;

#endif//MCC_MIDI_DEFINITIONS_H