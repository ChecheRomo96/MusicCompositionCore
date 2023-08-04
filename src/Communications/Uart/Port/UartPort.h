#ifndef MCC_UART_PORT_H
#define MCC_UART_PORT_H

	#include <MCC_BuildSettings.h>


	#if defined (MCC_UART_IN_ENABLED)
		#include "../InputPort/UART_InputPort.h"
	#endif

	#if defined (MCC_UART_OUT_ENABLED)
		#include "../OutputPort/UART_OutputPort.h"
	#endif

	#if defined (MCC_MIDI_PORT_ENABLED)
		#if defined (MCC_UART_MIDI_ENABLED)
			#include <Communications/Midi/UartMidi/UartMidi.h>
		#endif
			#include <Communications/Midi/MCC_Midi.h>
	#endif

	#include <CPVector.h>

	namespace MusicCompositionCore::Communications::Uart
    {

		#if defined (MCC_UART_IN_ENABLED)
            class InputPort;
		#endif

		#if defined (MCC_UART_OUT_ENABLED)
            class OutputPort;
		#endif

		#if defined (MCC_UART_DUPLEX_ENABLED)
            class DuplexPort;
		#endif

    
        class Port
        {
            private:

				///////////////////////////////////////////////////////////////////////
				// Port Pointer and Port Type

					void* _PortPointer;
					PortType _PortType;
				//
				///////////////////////////////////////////////////////////////////////
					
            public:

				///////////////////////////////////////////////////////////////////////
            	// Constructors

                    Port();
                    Port& operator=(const Port& Rhs);
                    	
					#if defined (MCC_UART_IN_ENABLED)
	                    Port(const Uart::Input::Port& Parent);
					#endif
                    	
					#if defined (MCC_UART_OUT_ENABLED)
	                    Port(const Uart::Output::Port& Parent);
					#endif

					//UartPort(const Uart::OutputPort& Parent);
					//UartPort(const Uart::DuplexPort& Parent);

				//
				///////////////////////////////////////////////////////////////////////
                // High Level API
	                    
					const PortType& ParentType() const;
					const void* ParentPointer() const;
				//
				///////////////////////////////////////////////////////////////////////
				// Uart Port Generic API

					const CPString::string& Name() const;
					void SetName(const CPString::string& NewName);

					void Initialize();
					void SetBaudRate(uint32_t BaudRate);
				//
				///////////////////////////////////////////////////////////////////////
                // Uart In API

                    uint8_t BytesAvailable();
                    uint8_t ReadByte();
				//
				//////////////////////////////////////////////////////////////////////
                // Uart Out API

                    void Write(uint8_t Data);
                    void WriteBuffer(uint8_t* Data, uint8_t Len);
                    void WriteBuffer(const CPVector::vector<uint8_t>& Data);
				//
				///////////////////////////////////////////////////////////////////////
                // Midi::UartMidi API

                    #if defined(MCC_UART_MIDI_ENABLED)
                    	bool UartMidi_BindPort() const;
                    	void UartMidi_UnbindPort() const;
						Midi::UartMidi::SystemPortHandler::PortID UartMidi_PortID() const;
						Midi::UartMidi::Port& UartMidi_Port() const;
                    #endif
                //
				///////////////////////////////////////////////////////////////////////
                // Midi API

                    #if defined(MCC_UART_MIDI_ENABLED) & defined(MCC_UART_MIDI_ENABLED)
                    	bool Midi_BindPort() const;
                    	void Midi_UnbindPort() const;
						Midi::SystemPortHandler::PortID Midi_PortID() const;
						Midi::Port& Midi_Port() const;
                    #endif
                //
				///////////////////////////////////////////////////////////////////////
            
            private:

				//////////////////////////////////////////////////////////////////////
                // Uart Port Link Helpers

            		void UnlinkFromPort();

					#if defined (MCC_UART_IN_ENABLED)
	                    void LinkToPort(const Uart::Input::Port& Parent);
					#endif

					#if defined (MCC_UART_OUT_ENABLED)
	                    void LinkToPort(const Uart::Output::Port& Parent);
					#endif
				//
				///////////////////////////////////////////////////////////////////////
        };
    }

#endif//MCC_UART_PORT_H