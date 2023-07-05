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
					namespace ChannelVoice
					{
						static constexpr uint8_t NoteOff = 0x80;
						static constexpr uint8_t NoteOn = 0x90;
						static constexpr uint8_t AfterTouch = 0xA0;
						static constexpr uint8_t ControlChange = 0xB0;
						static constexpr uint8_t ProgramChange = 0xC0;
						static constexpr uint8_t ChannelPressure = 0xD0;
						static constexpr uint8_t PitchBend = 0xE0;
					}
					
					namespace System
					{
						namespace Common
						{
							static constexpr uint8_t MTC_QuarterFrame = 0xF1;
							static constexpr uint8_t SongPositionPointer = 0xF2;
							static constexpr uint8_t SongSelect = 0xF3;
							static constexpr uint8_t TuningRequest = 0xF6;
						}

						namespace RealTime
						{
							static constexpr uint8_t TimingTick = 0xF8;
							static constexpr uint8_t Start = 0xFA;
							static constexpr uint8_t Continue = 0xFB;
							static constexpr uint8_t Stop= 0xFC;
							static constexpr uint8_t ActiveSensing = 0xFE;
							static constexpr uint8_t SystemReset = 0xFF;
						}

						namespace Exclusive
						{
							static constexpr uint8_t Start = 0xF0;
							static constexpr uint8_t End = 0xF7;

							namespace Manufacterers
							{
								// Finish this Table VIIa Midi 1.0 spec
							}

							namespace NonCommercial
							{
								static constexpr uint8_t ID = 0x7D;
							}

							namespace NonRealTime
							{
								static constexpr uint8_t ID = 0x7E;

								static constexpr uint8_t SampleDumpHeader = 0x01;
								static constexpr uint8_t SampleDataPacket = 0x02;
								static constexpr uint8_t SampleDumpRequest = 0x03;

								namespace MidiTimecode
								{
									// Finish this Table VIIa Midi 1.0 spec
									static constexpr uint16_t Special = 0x0400;
									static constexpr uint16_t PunchInPoints = 0x0401;
									static constexpr uint16_t PunchOutPoints = 0x0402;
									static constexpr uint16_t DeletePunchInPoints = 0x0403;
									static constexpr uint16_t DeletePunchOutPoints = 0x0404;
								}
							}

							namespace RealTime
							{
								static constexpr uint8_t ID = 0x7F;
							}
						}
					}
				}
				
				static constexpr uint8_t MidiNoteRange = 128u;
				static constexpr uint8_t InvalidMidiNote = 128u;
				static constexpr uint8_t MidiVelocityRange = 128u;
				static constexpr uint8_t InvalidMidiVelocity = 128u;
				static constexpr uint8_t MidiChannelRange = 16u;
				static constexpr uint8_t InvalidMidiChannel = 16u;

				static constexpr uint32_t BaudRate = 31250;
			}
		}
	}
    
    namespace MCC_MidiCore = MusicCompositionCore::Core::MidiCore;
    namespace MCC_MidiProtocol = MusicCompositionCore::Core::MidiCore::Protocol;

#endif//MCC_MIDI_DEFINITIONS_H