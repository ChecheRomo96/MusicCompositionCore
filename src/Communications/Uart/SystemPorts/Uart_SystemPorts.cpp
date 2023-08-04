#include "../Uart.h"

using namespace MusicCompositionCore::Communications;

Uart::Port Uart::DummyPort;
Uart::SystemPortHandler Uart::SystemPorts;

Uart::SystemPortHandler::SystemPortHandler()
{

}

const uint8_t Uart::SystemPortHandler::PortCount() const
{
	return _PortVector.size();
}

const Uart::SystemPortHandler::PortID& Uart::SystemPortHandler::GetID(const Uart::Port& Port) const
{
	return Uart::SystemPortHandler::InvalidPortID;
}

Uart::Port& Uart::SystemPortHandler::Port(const Uart::SystemPortHandler::PortID& ID)
{

	if((uint8_t)ID < _PortVector.size())
	{
		return _PortVector[(uint8_t)ID];
	}
	return Uart::DummyPort;
}

Uart::Port& Uart::SystemPortHandler::operator[](unsigned int Index)
{
	if(Index < _PortVector.size())
	{
		return _PortVector[Index];
	}
	
	return Uart::DummyPort;
}

const Uart::Port& Uart::SystemPortHandler::operator[](unsigned int Index) const
{
	if (Index < _PortVector.size())
	{
		return _PortVector[Index];
	}

	return Uart::DummyPort;
}

#if defined(MCC_UART_IN_ENABLED)

	bool Uart::SystemPortHandler::BindPort(const Uart::Input::Port& Port)
	{
		if(GetID(Port) == Uart::SystemPortHandler::InvalidPortID)
		{
			if(_PortVector.resize(_PortVector.size()+1))
			{
				_PortVector[_PortVector.size() - 1] = Uart::Port(Port);
				return 1;
			}
			return 0;
		}
		return 1;
	}
	

	void Uart::SystemPortHandler::UnbindPort(const Uart::Input::Port& Port)
	{
		for(uint8_t i = 0; i < _PortVector.size(); i++)
		{
			if(_PortVector[i].ParentPointer() == &Port)
			{
				_PortVector.erase(i);
				return;
			} 
		}
	}

	Uart::Port& Uart::SystemPortHandler::GetPort(const Uart::Input::Port& Port)
	{
		uint8_t ID = GetID(Port);

		if(ID != Uart::SystemPortHandler::InvalidPortID)
		{
			return _PortVector[ID];
		}

		return Uart::DummyPort;
	}

	const Uart::SystemPortHandler::PortID& Uart::SystemPortHandler::GetID(const Uart::Input::Port& Port) const
	{
		for(uint8_t i = 0; i < _PortVector.size(); i++)
		{
			if(_PortVector[i].ParentPointer() == &Port)
			{
				return (Uart::SystemPortHandler::PortID) i;
			} 
		}

		return Uart::SystemPortHandler::InvalidPortID;
	}
#endif


#if defined(MCC_UART_OUT_ENABLED)

	bool Uart::SystemPortHandler::BindPort(const Uart::Output::Port& Port)
	{
		if(GetID(Port) == Uart::SystemPortHandler::InvalidPortID)
		{
			if(_PortVector.resize(_PortVector.size()+1))
			{
				_PortVector[_PortVector.size() - 1] = Uart::Port(Port);
				return 1;
			}
			return 0;
		}
		return 1;
	}
	

	void Uart::SystemPortHandler::UnbindPort(const Uart::Output::Port& Port)
	{
		for(uint8_t i = 0; i < _PortVector.size(); i++)
		{
			if(_PortVector[i].ParentPointer() == &Port)
			{
				_PortVector.erase(i);
				return;
			} 
		}
	}

	Uart::Port& Uart::SystemPortHandler::GetPort(const Uart::Output::Port& Port)
	{
		uint8_t ID = GetID(Port);

		if(ID != Uart::SystemPortHandler::InvalidPortID)
		{
			return _PortVector[ID];
		}

		return Uart::DummyPort;
	}

	const Uart::SystemPortHandler::PortID& Uart::SystemPortHandler::GetID(const Uart::Output::Port& Port) const
	{
		for(uint8_t i = 0; i < _PortVector.size(); i++)
		{
			if(_PortVector[i].ParentPointer() == &Port)
			{
				return (Uart::SystemPortHandler::PortID) i;
			} 
		}

		return Uart::SystemPortHandler::InvalidPortID;
	}
#endif