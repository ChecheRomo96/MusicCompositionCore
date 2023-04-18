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
					namespace PortID
					{
						static constexpr uint8_t InvalidMode = 0u;
						static constexpr uint8_t DuplexPort = 1u;
						static constexpr uint8_t InputPort = 2u;
						static constexpr uint8_t OutputPort = 3u;
					}

					namespace PollingMode
					{
						static constexpr bool Automatic = 0;
						static constexpr bool Manual = 1;
					}

					static constexpr uint32_t MidiBaudRate = 31250;
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
                
                    /*class UartMidiPort
                     {
                     private:
                     void* _PortPointer;
                     uint8_t _PortID;
                     
                     public:
                     UartMidiPort(const Uart::InputPort& Parent);
                     UartMidiPort(const Uart::OutputPort& Parent);
                     UartMidiPort(const Uart::DuplexPort& Parent);
                     
                     
                     };
                     
                     CPVector::vector<UartMidiPort> UartMidiPorts;
                     
                     uint8_t GetPortID();
                     */
                
                }
			}
		}
	}

#endif//MCC_UART_MIDI_H
