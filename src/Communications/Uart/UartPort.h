#ifndef MCC_UART_PORT_H
#define MCC_UART_PORT_H

	#include <MCC_BuildSettings.h>


	#if defined (MCC_UART_IN_ENABLED)
		#include "InputPort/UART_InputPort.h"
	#endif

	#if defined (MCC_UART_OUT_ENABLED)
		#include "OutputPort/UART_OutputPort.h"
	#endif

	#include <CPVector.h>

	namespace MusicCompositionCore
	{
		namespace Communications
		{
			namespace Uart
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
						void* _PortPointer;
						PortType _PortType;
                     
                    public:

						///////////////////////////////////////////////////////////////////////
                    	// Constructors

                            Port();
                            	
							#if defined (MCC_UART_MIDI_IN_ENABLED)
			                    Port(const InputPort& Parent);
							#endif

							//UartPort(const Uart::OutputPort& Parent);
							//UartPort(const Uart::DuplexPort& Parent);
						//
						///////////////////////////////////////////////////////////////////////
                        // High Level API

								

							#if defined (MCC_UART_MIDI_IN_ENABLED)
			                    void LinkToPort(const InputPort& Parent);
							#endif

							void UnlinkFromPort();

							const PortType& ParentType() const;
							const void* ParentPointer() const;
						//
						///////////////////////////////////////////////////////////////////////
						// Port Generic API

							const CPString::string& Name() const;
							void SetName(const CPString::string& NewName);

						//
						///////////////////////////////////////////////////////////////////////
	                    // Uart In API

	                        void AppendCallback(void(*Callback)(CPVector::vector<uint8_t>&));
	                        void DetachCallback(void(*Callback)(CPVector::vector<uint8_t>&));

	                        void SetBufferSize(uint8_t size);

							void Service();
						//
						//////////////////////////////////////////////////////////////////////
	                    // Uart Out API

	                        void Write(uint8_t Data);
						//
						///////////////////////////////////////////////////////////////////////


                };
                 
                extern CPVector::vector<Port> SystemPorts;
                 
				#if defined(MCC_UART_IN_ENABLED)
	                bool BindPort(const InputPort& PortPointer); 
	                void ReleasePort(const InputPort& PortPointer); 
	                PortID GetSystemPortID(const InputPort& Port);
				#endif
            
            }
		}
	}

#endif//MCC_UART_PORT_H