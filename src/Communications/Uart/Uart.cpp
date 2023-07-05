#include "Uart.h"

using namespace MCC::Communications;

#if defined(MCC_UART_IN_ENABLED)

	bool Uart::BindPort(const Uart::InputPort& PortPointer)
	{
		return 0;
	}

	void Uart::ReleasePort(const Uart::InputPort& PortPointer)
	{

	}

	Uart::PortID Uart::GetSystemPortID(const Uart::InputPort& Port)
	{
		return Uart::InvalidPortID;
	}
	
#endif