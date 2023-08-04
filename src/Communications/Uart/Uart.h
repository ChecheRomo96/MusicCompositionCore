#ifndef MCC_UART_H
#define MCC_UART_H

	#include <MCC_BuildSettings.h>
	
	namespace MusicCompositionCore::Communications::Uart
	{
    	typedef uint8_t PortType;
		namespace PortTypes
		{
			static constexpr PortType InvalidType = 0u;
			static constexpr PortType DuplexPort = 1u;
			static constexpr PortType InputPort = 2u;
			static constexpr PortType OutputPort = 3u;
		}
    
		class Port;
		class SystemPortHandler;

    	#if defined(MCC_UART_IN_ENABLED)
			namespace Input
			{
				class Port;
    		}
    	#endif

	}
	#include "SystemPorts/Uart_SystemPorts.h"
	
	#if defined (MCC_UART_IN_ENABLED)
		#include "InputPort/UART_InputPort.h"
	#endif

	#if defined (MCC_UART_OUT_ENABLED)
		#include "OutputPort/UART_OutputPort.h"
	#endif

	#include "Port/UartPort.h"

#endif//MCC_UART_H
