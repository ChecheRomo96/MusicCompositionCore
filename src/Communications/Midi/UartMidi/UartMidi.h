#ifndef MCC_UART_MIDI_H
#define MCC_UART_MIDI_H

	#include <MCC_BuildSettings.h>
	
	namespace MusicCompositionCore
	{
		namespace Communications
		{
			namespace Midi
			{
				namespace Uart
				{

                	typedef uint8_t PortID;
                	typedef uint8_t PortType;

                	static constexpr PortID InvalidPortID = 0xFF;

                	class MidiPort;

					namespace PortTypes
					{
						static constexpr PortType InvalidType = 0u;
						static constexpr PortType DuplexPort = 1u;
						static constexpr PortType InputPort = 2u;
						static constexpr PortType OutputPort = 3u;
					}

					namespace PollingMode
					{
						static constexpr bool Automatic = 0;
						static constexpr bool Manual = 1;
					}

					static constexpr uint32_t SpecBaudRate = 31250;
				}
			}
		}
	}


	#include "InputPort/UartMidiIn.h"
	#include <CPVector.h>

	namespace MusicCompositionCore
	{
		namespace Communications
		{
			namespace Midi
			{
				namespace Uart
                {
                    class InputPort;
                
                    class MidiPort
                    {
	                    private:
							void* _PortPointer;
							PortType _PortType;
	                     
	                    public:

							///////////////////////////////////////////////////////////////////////
	                    	// Constructors

	                            MidiPort();


	                            MidiPort(const InputPort& Parent);
								//UartMidiPort(const Uart::OutputPort& Parent);
								//UartMidiPort(const Uart::DuplexPort& Parent);
							//
							///////////////////////////////////////////////////////////////////////
	                        // High Level API

								void LinkToPort(const InputPort& Parent);
								void UnlinkFromPort();

								const PortType& ParentType() const;
								const void* ParentPointer() const;
							//
							///////////////////////////////////////////////////////////////////////
							// Midi Port Generic API

								const CPString::string& Name() const;
								void SetName(const CPString::string& NewName);

							//
							///////////////////////////////////////////////////////////////////////
		                    // Midi In API

		                        void AppendCallback(void(*Callback)(CPVector::vector<uint8_t>&));
		                        void DetachCallback(void(*Callback)(CPVector::vector<uint8_t>&));

		                        void SetBufferSize(uint8_t size);

								void Service();
							//
							///////////////////////////////////////////////////////////////////////


                    };
                     
                    extern CPVector::vector<MidiPort> SystemPorts;
                     
                    bool BindPort(const InputPort& PortPointer); 
                    void ReleasePort(const InputPort& PortPointer); 
                    PortID GetSystemPortID(const InputPort& Port);
                
                }
			}
		}
	}

#endif//MCC_UART_MIDI_H
