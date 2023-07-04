#ifndef MCC_UART_MIDI_OUT_H
#define MCC_UART_MIDI_OUT_H

	#include <MCC_BuildSettings.h>
	#include <CPVector.h>
	#include <CPString.h>
	#include "../../MidiPort.h"
	#include "../UartMidi.h"

	namespace MusicCompositionCore
	{
		namespace Communications
		{
			namespace Midi
			{
				class Port;

				namespace Uart
				{
					class MidiPort;

					class OutputPort
					{
						private:
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// HW Link Function pointers

								uint8_t (*_Write)(uint8_t Data);

								void (*_SetBaudRate)(uint32_t BaudRate); // Optional
								void (*_Initialize)(void);				 // Optional
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Port Name

								CPString::string _Name;
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// BaudRate, Polling Mode, and flags
								
								uint32_t _BaudRate;
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						public:

							
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Constructors

								OutputPort();
								OutputPort( const CPString::string& PortName );							
								OutputPort( void (&Write)(uint8_t) );
								OutputPort( const CPString::string& PortName, void (&Write)(uint8_t) );
								OutputPort( void (&Write)(uint8_t), void (&Initialize)(void), void (&SetBaudRate)(uint32_t) );
								OutputPort( const CPString::string& PortName, void (&Write)(uint8_t), void (&Initialize)(void), void (&SetBaudRate)(uint32_t) );
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Hardware Link API
								
								void HLAPI_Attach( void (&Write)(uint8_t), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) );
								void HLAPI_Attach( void (&Write)(uint8_t));
								void HLAPI_Dettach();
								bool HLAPI_Status();

								bool AvailableAPI_Status();
								bool ReadAPI_Status();
								bool InitializeAPI_Status();
								bool SetBaudRateAPI_Status();
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Low Level Hardware API

								void Initialize();
								void SetBaudRate(uint32_t BaudRate);
								void Write(uint8_t Data);
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// High Level API

								bool EnablePort();
								void DisablePort();

								Uart::PortID UartMidiPortID();
								Midi::PortID MidiPortID();
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Midi Port Generic API

								const CPString::string& Name() const;
								void SetName(const CPString::string& NewName);

							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		                    // Midi Out API
		                        
		                        // Channel Voice Messages
		                        void NoteOn(uint8_t Note, uint8_t Velocity, uint8_t Channel);
		                        void NoteOff(uint8_t Note, uint8_t Velocity, uint8_t Channel);
		                        void ControlChange(uint8_t ControlNumber, uint8_t NewValue uint8_t Channel);
		                        void ChannelPressure(uint8_t Pressure, uint8_t Channel);
		                        void PitchBend(uint8_t BendValue, uint8_t Channel);
		                        void PitchBend(uint16_t BendValue, uint8_t Channel);
		                        void AfterTouch(uint8_t Note, uint8_t Value, uint8_t Channel);

		                        // Sysytem Common Messages
		                        void TimingTick();
		                        void Start();
		                        void Stop();
		                        void Continue();
		                        void SongPositionPointer(uint16_t Position);
		                        void MTC_QuarterFrame(uint8_t MessageType, uint8_t Values);
		                        void SongSelect(uint8_t SongID);
		                        void ActiveSensing();

		                        void SysteExclusive(uint8_t ManufacturerID , uint8_t* Data, uint8_t size);
		                        void SysteExclusive(uint8_t ManufacturerID , const CPVector::vector<uint8_t>& Data);
		                        void SysteExclusive(uint32_t ManufacturerID , uint8_t* Data, uint8_t size);
		                        void SysteExclusive(uint32_t ManufacturerID , const CPVector::vector<uint8_t>& Data);

							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						private:

							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Low Level Hardware API

								
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Helpers

							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					};
				}
			}
		}
	}

#endif//MCC_UART_MIDI_OUT_H