#ifndef MCC_UART_IN_H
#define MCC_UART_IN_H

	#include <MCC_BuildSettings.h>
	#include <CPVector.h>
	#include <CPString.h>


    namespace MusicCompositionCore::Communications::Uart::Input
	{
		class Port;
	}


    #include "../Uart.h"
    
	#if defined(MCC_MIDI_PORT_ENABLED)
		#include <Communications/Midi/MCC_Midi.h>
	#endif
	
	#if defined(MCC_UART_MIDI_ENABLED)
		#include <Communications/Midi/UartMidi/UartMidi.h>
	#endif
    

    namespace MusicCompositionCore::Communications::Uart::Input
	{
		class Port
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

					CPVector::vector<void(*)(const CPVector::vector<uint8_t>&)> _CallbackVector;
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

					Port();
					Port( const CPString::string& PortName );							
					Port( uint8_t (&Available)(void), uint8_t (&Read)(void) );
					Port( const CPString::string& PortName, uint8_t (&Available)(void), uint8_t (&Read)(void) );
					Port( uint8_t (&Available)(void), uint8_t (&Read)(void), void (&Initialize)(void), void (&SetBaudRate)(uint32_t) );
					Port( const CPString::string& PortName, uint8_t (&Available)(void), uint8_t (&Read)(void), void (&Initialize)(void), void (&SetBaudRate)(uint32_t) );
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// Hardware Link API
					
					void HLAPI_Link( uint8_t (&Available)(void), uint8_t (&Read)(void), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) );
					void HLAPI_Link( uint8_t (&Available)(void), uint8_t (&Read)(void));
					void HLAPI_Unlink();
					const bool HLAPI_Status() const;

					const bool AvailableAPI_Status() const;
					const bool ReadAPI_Status() const;
					const bool InitializeAPI_Status() const;
					const bool SetBaudRateAPI_Status() const;
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// Generic Uart Port API

					const CPString::string& Name() const;
					void SetName(const CPString::string& NewName);

					void Initialize();
					void SetBaudRate(uint32_t BaudRate);
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // UART In API
                    
					uint8_t BytesAvailable();
					uint8_t ReadByte();
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// UART::Port API

					bool Uart_BindPort() const;
					void Uart_UnbindPort() const;
					Uart::SystemPortHandler::PortID Uart_PortID() const;
					Uart::Port& Uart_Port() const;
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// UartMidi::Port API
					
					#if defined(MCC_MIDI_PORT_ENABLED) & defined(MCC_UART_MIDI_ENABLED)

						bool UartMidi_BindPort() const;
						void UartMidi_UnbindPort() const;
						Midi::UartMidi::SystemPortHandler::PortID UartMidi_PortID() const;
						Midi::UartMidi::Port& UartMidi_Port() const;
					#endif	
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// Midi::Port API
					
					#if defined(MCC_MIDI_PORT_ENABLED) & defined(MCC_UART_MIDI_ENABLED)

						bool Midi_BindPort() const;
						void Midi_UnbindPort() const;
						Midi::SystemPortHandler::PortID Midi_PortID() const;
						Midi::Port& Midi_Port() const;
					#endif	
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			private:

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

#endif//MCC_UART_IN_H