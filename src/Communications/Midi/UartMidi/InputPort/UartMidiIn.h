#ifndef MCC_UART_MIDI_IN_H
#define MCC_UART_MIDI_IN_H

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

					class InputPort
					{
						private:

							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// HW Link Function pointers

								uint8_t (*_Available)(void);
								uint8_t (*_Read)(void);

								void (*_SetBaudRate)(uint32_t BaudRate); // Optional
								void (*_Initialize)(void);				 // Optional
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Callback vector ans Message Buffer Vector

								CPVector::vector<void(*)(CPVector::vector<uint8_t>&)> _CallbackVector;
								CPVector::vector<uint8_t> _MessageBuffer;
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Port Name

								CPString::string _Name;
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// BaudRate, Polling Mode, and flags
								
								uint32_t _BaudRate;
								uint8_t _FlagRegister;
								uint8_t _BufferIndex;

			                    // bool _PollingMode  --> Bit 0
								// bool _SOMF         --> Bit 1
								// bool _SysExFlag    --> Bit 2
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						public:

							
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Constructors

								InputPort();
								InputPort( const CPString::string& PortName );							
								InputPort( uint8_t (&Available)(void), uint8_t (&Read)(void) );
								InputPort( const CPString::string& PortName, uint8_t (&Available)(void), uint8_t (&Read)(void) );
								InputPort( uint8_t (&Available)(void), uint8_t (&Read)(void), void (&Initialize)(void), void (&SetBaudRate)(uint32_t) );
								InputPort( const CPString::string& PortName, uint8_t (&Available)(void), uint8_t (&Read)(void), void (&Initialize)(void), void (&SetBaudRate)(uint32_t) );
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Hardware Link API
								
								void HLAPI_Attach( uint8_t (&Available)(void), uint8_t (&Read)(void), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) );
								void HLAPI_Attach( uint8_t (&Available)(void), uint8_t (&Read)(void));
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
		                    // Midi In API
		                        
		                        void AppendCallback(void(*Callback)(CPVector::vector<uint8_t>&));
		                        void DetachCallback(void(*Callback)(CPVector::vector<uint8_t>&));

		                        void SetBufferSize(uint8_t size);

								void Service();

							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						private:

							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Low Level Hardware API

								uint8_t BytesAvailable();
								uint8_t ReadByte();
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							// Helpers

								void SetSysExFlag(bool State);
								const bool SysExFlag() const;

								void SetSOMF(bool State);
								const bool SOMF() const;
							//
							//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					};
				}
			}
		}
	}

#endif//MCC_UART_MIDI_IN_H
