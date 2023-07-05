#ifndef MCC_UART_H
#define MCC_UART_H


	#include <MCC_BuildSettings.h>
	
	namespace MusicCompositionCore
	{
		namespace Communications
		{
			namespace Uart
			{

            	typedef uint8_t PortID;
            	typedef uint8_t PortType;

            	static constexpr PortID InvalidPortID = 0xFF;

            	class Port;

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
			}
		}
	}

	#include "UartPort.h"


#endif//MCC_UART_H