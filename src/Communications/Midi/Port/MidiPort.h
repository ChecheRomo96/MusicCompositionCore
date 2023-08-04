#ifndef MCC_MIDI_PORT_H
#define MCC_MIDI_PORT_H

	#include <MCC_BuildSettings.h>
	#include <Core/MidiCore/MidiCore.h>

	#include "../MCC_Midi.h"

	#if defined (MCC_UART_MIDI_ENABLED)
		#include "../UartMidi/UartMidi.h"
	#endif

	#include <CPVector.h>

	namespace MusicCompositionCore
	{
		namespace Communications
		{
			namespace Midi
			{

				class Port
				{
					private:

						void* _PortPointer;
						PortType _PortType;

					public:

						///////////////////////////////////////////////////////////////////////
	                    // Constructors

							Port();

							#if defined (MCC_UART_MIDI_ENABLED)
								Port(const UartMidi::Port& Parent);
							#endif
						//
						///////////////////////////////////////////////////////////////////////
	                    // High Level API

							#if defined (MCC_UART_MIDI_ENABLED)
								void LinkToPort(const UartMidi::Port& Parent);
							#endif
							void UnlinkFromPort();

							const void* ParentPointer() const;
							const Midi::PortType& ParentType() const;
						//
						///////////////////////////////////////////////////////////////////////
						// Midi Port Generic API

							const CPString::string& Name() const;
							void SetName(const CPString::string& NewName);
						//
						///////////////////////////////////////////////////////////////////////
	                    // Midi In API

	                        void AppendCallback(void(*Callback)(const CPVector::vector<uint8_t>&));
	                        void DetachCallback(void(*Callback)(const CPVector::vector<uint8_t>&));

	                        void SetBufferSize(uint8_t size);

							void Service();
						//
						//////////////////////////////////////////////////////////////////////
	                    // Midi Out API

							void Write(uint8_t Data);
							void WriteMessage(uint8_t* Data, uint8_t Size);
							void WriteMessage(const CPVector::vector<uint8_t>& Data);

							#if defined (MCC_MIDI_MESSAGE_ENABLED)
								void WriteMessage(const MCC_MidiCore::MidiMessage& Data);
							#endif

		                    //////////////////////////////////////////////////////////////////
	                        // Channel Voice Messages
		                        
		                        void NoteOn(uint8_t Note, uint8_t Velocity, uint8_t Channel = 0);
		                        void NoteOff(uint8_t Note, uint8_t Velocity, uint8_t Channel = 0);
		                        void ControlChange(uint8_t ControlNumber, uint8_t NewValue, uint8_t Channel = 0);
		                        void ChannelPressure(uint8_t Pressure, uint8_t Channel = 0);
		                        void PitchBend(uint8_t BendValue, uint8_t Channel = 0);
		                        void PitchBend(uint16_t BendValue, uint8_t Channel = 0);
		                        void PitchBend(int8_t BendValue, uint8_t Channel = 0);
		                        void PitchBend(int16_t BendValue, uint8_t Channel = 0);
		                        void AfterTouch(uint8_t Note, uint8_t Value, uint8_t Channel = 0);
	                        //
		                    //////////////////////////////////////////////////////////////////
	                        // Sysytem Common Messages

		                        void TimingTick();
		                        void Start();
		                        void Stop();
		                        void Continue();
		                        void ActiveSensing();
	                        //
		                    //////////////////////////////////////////////////////////////////
	                        // Sysytem Common Messages

		                        void SongPositionPointer(uint16_t Position);
		                        void MTC_QuarterFrame(uint8_t MessageType, uint8_t Values);
		                        void SongSelect(uint8_t SongID);

		                        void SysteExclusive(uint8_t ManufacturerID , uint8_t* Data, uint8_t size);
		                        void SysteExclusive(uint8_t ManufacturerID , const CPVector::vector<uint8_t>& Data);
		                        void SysteExclusive(uint32_t ManufacturerID , uint8_t* Data, uint8_t size);
		                        void SysteExclusive(uint32_t ManufacturerID , const CPVector::vector<uint8_t>& Data);
	                      
	                        //
		                    //////////////////////////////////////////////////////////////////
		                //
						///////////////////////////////////////////////////////////////////////
					private:

						///////////////////////////////////////////////////////////////////////
						// Helpers

						//						
						///////////////////////////////////////////////////////////////////////


				};

			}
		}
	}

#endif//MCC_MIDI_PORT_H
