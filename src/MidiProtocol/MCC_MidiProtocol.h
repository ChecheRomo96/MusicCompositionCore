#ifndef MCC_MIDI_CORE_H
#define MCC_MIDI_CORE_H

	#include <MCC_BuildSettings.h>

	namespace MusicCompositionCore::MidiProtocol{

		namespace ChannelVoice{

			static constexpr uint8_t NoteOff = 0x80;
			static constexpr uint8_t NoteOn = 0x90;
			static constexpr uint8_t AfterTouch = 0xA0;
			static constexpr uint8_t ControlChange = 0xB0;
			static constexpr uint8_t ProgramChange = 0xC0;
			static constexpr uint8_t ChannelPressure = 0xD0;
			static constexpr uint8_t PitchBend = 0xE0;
		}

		namespace ChannelMode{
			static constexpr uint8_t BankSelect = 0;
			static constexpr uint8_t Modulation = 1;
			static constexpr uint8_t BreathControl = 2;
			static constexpr uint8_t FootPedal = 4;
			static constexpr uint8_t Portamento = 5;
			static constexpr uint8_t DataEntryMsb = 6;
			static constexpr uint8_t Volume = 7;
			static constexpr uint8_t Balance = 8;
			static constexpr uint8_t Pan = 10;
			static constexpr uint8_t Expression = 11;

			static constexpr uint8_t DataEntryLsb = 6;

			static constexpr uint8_t NrpnDataIncrement = 96;
			static constexpr uint8_t NrpnDataDecrement = 97;
			static constexpr uint8_t NrpnLsb = 98;
			static constexpr uint8_t NrpnMsb = 99;
			static constexpr uint8_t RpnLsb = 100;
			static constexpr uint8_t RpnMsb = 101;
			
			static constexpr uint8_t AllSoundOff = 120;
			static constexpr uint8_t ResetAllControllers = 121;
			static constexpr uint8_t LocalControl = 122;
			static constexpr uint8_t AllNotesOff = 123;
			static constexpr uint8_t OmniModeOff = 124;
			static constexpr uint8_t OmniModeOn = 125;
			static constexpr uint8_t MonoModeOn = 126;
			static constexpr uint8_t PolyModeOn = 127;

			static constexpr uint8_t LocalControlOff = 0;
			static constexpr uint8_t LocalControlOn = 127;
		}
		
		namespace System{

			namespace Common{

				static constexpr uint8_t SongPositionPointer = 0xF2;
				static constexpr uint8_t SongSelect = 0xF3;
				static constexpr uint8_t TuningRequest = 0xF6;

				namespace MTC{	

					static constexpr uint8_t QuarterFrame = 0xF1;

					static constexpr uint8_t Frames_Lsb = 0x00;
					static constexpr uint8_t Frames_Msb = 0x10;

					static constexpr uint8_t Seconds_Lsb = 0x20;
					static constexpr uint8_t Seconds_Msb = 0x30;

					static constexpr uint8_t Minutes_Lsb = 0x40;
					static constexpr uint8_t Minutes_Msb = 0x50;

					static constexpr uint8_t Hours_Lsb = 0x60;
					static constexpr uint8_t Hours_Msb = 0x70;

					constexpr uint8_t FrameRate_24FPS = 0b000;
					constexpr uint8_t FrameRate_25FPS = 0b010;
					constexpr uint8_t FrameRate_30FPS_DropFrame = 0b100;
					constexpr uint8_t FrameRate_30FPS = 0b110;
				}
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

		static constexpr uint8_t MidiNoteRange = 128u;
		static constexpr uint8_t InvalidMidiNote = 128u;

		static constexpr uint8_t MidiVelocityRange = 128u;
		static constexpr uint8_t InvalidMidiVelocity = 128u;
		
		static constexpr uint8_t MidiChannelRange = 16u;
		static constexpr uint8_t InvalidMidiChannel = 16u;

		static constexpr uint32_t BaudRate = 31250;
	}

    namespace MCC_MidiProtocol = MusicCompositionCore::MidiProtocol;

	#if defined MCC_MIDI_NOTE_ENABLED
		#include "MidiNote/MidiNote.h"
	#endif

	#if defined MCC_MIDI_MESSAGE_ENABLED
		#include "MidiMessage/MidiMessage.h"
	#endif

#endif//MCC_MIDI_CORE_H