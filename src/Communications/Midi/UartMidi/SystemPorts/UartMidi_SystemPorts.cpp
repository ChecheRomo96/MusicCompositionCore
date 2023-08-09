#include "../UartMidi.h"

using namespace MusicCompositionCore::Communications::Midi;
using namespace MusicCompositionCore::Communications;

UartMidi::Port UartMidi::DummyPort;
UartMidi::SystemPortHandler UartMidi::SystemPorts;

UartMidi::SystemPortHandler::SystemPortHandler()
{

}

const uint8_t UartMidi::SystemPortHandler::PortCount() const
{
	return _PortVector.size();
}

const UartMidi::SystemPortHandler::PortID& UartMidi::SystemPortHandler::GetID(const UartMidi::Port& Port) const
{
	return UartMidi::SystemPortHandler::InvalidPortID;
}

UartMidi::Port& UartMidi::SystemPortHandler::Port(const UartMidi::SystemPortHandler::PortID& ID)
{

	if((uint8_t)ID < _PortVector.size())
	{
		return _PortVector[(uint8_t)ID];
	}
	return UartMidi::DummyPort;
}

UartMidi::Port& UartMidi::SystemPortHandler::operator[](unsigned int Index)
{
	if(Index < _PortVector.size())
	{
		return _PortVector[Index];
	}
	
	return UartMidi::DummyPort;
}

const UartMidi::Port& UartMidi::SystemPortHandler::operator[](unsigned int Index) const
{
	if (Index < _PortVector.size())
	{
		return _PortVector[Index];
	}

	return UartMidi::DummyPort;
}

#if defined(MCC_UART_PORT_ENABLED)

	bool UartMidi::SystemPortHandler::BindPort(const Uart::Port& Port)
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

	void UartMidi::SystemPortHandler::UnbindPort(const Uart::Port& Port)
	{
		for(uint8_t i = 0; i < _PortVector.size(); i++)
		{
			if(_PortVector[i].Uart_PortPointer() == &Port)
			{
				_PortVector.erase(i);
				return;
			} 
		}
	}

	UartMidi::Port& UartMidi::SystemPortHandler::GetPort(const Uart::Port& Port)
	{
		auto ID = GetID(Port);

		if(ID != UartMidi::SystemPortHandler::InvalidPortID)
		{
			return _PortVector[ID];
		}

		return UartMidi::DummyPort;
	}

	const UartMidi::SystemPortHandler::PortID& UartMidi::SystemPortHandler::GetID(const Uart::Port& Port) const
	{
		for(uint8_t i = 0; i < _PortVector.size(); i++)
		{
			if(_PortVector[i].Uart_PortPointer() == &Port)
			{
				return (UartMidi::SystemPortHandler::PortID) i;
			} 
		}

		return UartMidi::SystemPortHandler::InvalidPortID;
	}


    #if defined(MCC_UART_IN_ENABLED)

        bool UartMidi::SystemPortHandler::BindPort(const Uart::Input::Port& Port)
        {
			if(GetID(Port) == UartMidi::SystemPortHandler::InvalidPortID)
			{

				if (Uart::SystemPorts.GetID(Port) == Uart::SystemPortHandler::InvalidPortID)
				{
					if (!Uart::SystemPorts.BindPort(Port)) { return 0; }
				}

				if(_PortVector.resize(_PortVector.size()+1))
				{
					_PortVector[_PortVector.size() - 1] = UartMidi::Port(Uart::SystemPorts.GetPort(Port));
					return 1;
				}
				return 0;
			}
			return 1;
        }

        void UartMidi::SystemPortHandler::UnbindPort(const Uart::Input::Port& Port)
        {
			for(uint8_t i = 0; i < _PortVector.size(); i++)
			{
				if(_PortVector[i].ParentType() == Uart::PortTypes::InputPort)
				{
					if (_PortVector[i].Uart_PortPointer()->ParentPointer() == &Port)
					{
						_PortVector.erase(i);
					}
					return;
				} 
			}
        }

        UartMidi::Port& UartMidi::SystemPortHandler::GetPort(const Uart::Input::Port& Port)
        {
			auto ID = GetID(Port);

			if (ID != UartMidi::SystemPortHandler::InvalidPortID)
			{
				return _PortVector[ID];
			}

			return UartMidi::DummyPort;
        }

		const UartMidi::SystemPortHandler::PortID UartMidi::SystemPortHandler::GetID(const Uart::Input::Port& Port) const
		{
			for (uint8_t i = 0; i < _PortVector.size(); i++)
			{
				if (_PortVector[i].ParentType() == Uart::PortTypes::InputPort)
				{
					if (_PortVector[i].Uart_PortPointer()->ParentPointer() == &Port)
					{
						return (UartMidi::SystemPortHandler::PortID)i;
					}
				}
			}

			return UartMidi::SystemPortHandler::InvalidPortID;
		}

    #endif

    #if defined(MCC_UART_OUT_ENABLED)

        bool UartMidi::SystemPortHandler::BindPort(const Uart::Output::Port& Port)
        {
			if(GetID(Port) == UartMidi::SystemPortHandler::InvalidPortID)
			{

				if (Uart::SystemPorts.GetID(Port) == Uart::SystemPortHandler::InvalidPortID)
				{
					if (!Uart::SystemPorts.BindPort(Port)) { return 0; }
				}

				if(_PortVector.resize(_PortVector.size()+1))
				{
					_PortVector[_PortVector.size() - 1] = UartMidi::Port(Uart::SystemPorts.GetPort(Port));
					return 1;
				}
				return 0;
			}
			return 1;
        }

        void UartMidi::SystemPortHandler::UnbindPort(const Uart::Output::Port& Port)
        {
			for(uint8_t i = 0; i < _PortVector.size(); i++)
			{
				if(_PortVector[i].ParentType() == Uart::PortTypes::OutputPort)
				{
					if (_PortVector[i].Uart_PortPointer()->ParentPointer() == &Port)
					{
						_PortVector.erase(i);
					}
					return;
				} 
			}
        }

        UartMidi::Port& UartMidi::SystemPortHandler::GetPort(const Uart::Output::Port& Port)
        {
			auto ID = GetID(Port);

			if (ID != UartMidi::SystemPortHandler::InvalidPortID)
			{
				return _PortVector[ID];
			}

			return UartMidi::DummyPort;
        }

		const UartMidi::SystemPortHandler::PortID UartMidi::SystemPortHandler::GetID(const Uart::Output::Port& Port) const
		{
			for (uint8_t i = 0; i < _PortVector.size(); i++)
			{
				if (_PortVector[i].ParentType() == Uart::PortTypes::OutputPort)
				{
					if (_PortVector[i].Uart_PortPointer()->ParentPointer() == &Port)
					{
						return (UartMidi::SystemPortHandler::PortID)i;
					}
				}
			}

			return UartMidi::SystemPortHandler::InvalidPortID;
		}
    #endif

    #if defined(MCC_UART_DUPLEX_ENABLED)

        bool UartMidi::SystemPortHandler::BindPort(const Uart::Duplex::Port& Port)
        {
			if(GetID(Port) == UartMidi::SystemPortHandler::InvalidPortID)
			{

				if (Uart::SystemPorts.GetID(Port) == Uart::SystemPortHandler::InvalidPortID)
				{
					if (!Uart::SystemPorts.BindPort(Port)) { return 0; }
				}

				if(_PortVector.resize(_PortVector.size()+1))
				{
					_PortVector[_PortVector.size() - 1] = UartMidi::Port(Uart::SystemPorts.GetPort(Port));
					return 1;
				}
				return 0;
			}
			return 1;
        }

        void UartMidi::SystemPortHandler::UnbindPort(const Uart::Duplex::Port& Port)
        {
			for(uint8_t i = 0; i < _PortVector.size(); i++)
			{
				if(_PortVector[i].ParentType() == Uart::PortTypes::DuplexPort)
				{
					if (_PortVector[i].Uart_PortPointer()->ParentPointer() == &Port)
					{
						_PortVector.erase(i);
					}
					return;
				} 
			}
        }

        UartMidi::Port& UartMidi::SystemPortHandler::GetPort(const Uart::Duplex::Port& Port)
        {
			auto ID = GetID(Port);

			if (ID != UartMidi::SystemPortHandler::InvalidPortID)
			{
				return _PortVector[ID];
			}

			return UartMidi::DummyPort;
        }

		const UartMidi::SystemPortHandler::PortID UartMidi::SystemPortHandler::GetID(const Uart::Duplex::Port& Port) const
		{
			for (uint8_t i = 0; i < _PortVector.size(); i++)
			{
				if (_PortVector[i].ParentType() == Uart::PortTypes::DuplexPort)
				{
					if (_PortVector[i].Uart_PortPointer()->ParentPointer() == &Port)
					{
						return (UartMidi::SystemPortHandler::PortID)i;
					}
				}
			}

			return UartMidi::SystemPortHandler::InvalidPortID;
		}
    #endif
#endif