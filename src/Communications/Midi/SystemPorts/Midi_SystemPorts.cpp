#include "../MCC_Midi.h"

using namespace MusicCompositionCore::Communications;

Midi::Port Midi::DummyPort;
Midi::SystemPortHandler Midi::SystemPorts;


Midi::SystemPortHandler::SystemPortHandler()
{

}

const uint8_t Midi::SystemPortHandler::PortCount() const
{
	return _PortVector.size();
}

const Midi::SystemPortHandler::PortID& Midi::SystemPortHandler::GetID(const Midi::Port& Port) const
{
	return Midi::SystemPortHandler::InvalidPortID;
}

Midi::Port& Midi::SystemPortHandler::Port(const Midi::SystemPortHandler::PortID& ID)
{
	if((uint8_t)ID < _PortVector.size())
	{
		return _PortVector[(uint8_t)ID];
	}
	return Midi::DummyPort;
}

Midi::Port& Midi::SystemPortHandler::operator[](unsigned int Index)
{
	if(Index < _PortVector.size())
	{
		return _PortVector[Index];
	}
	
	return Midi::DummyPort;
}

const Midi::Port& Midi::SystemPortHandler::operator[](unsigned int Index) const
{
	if (Index < _PortVector.size())
	{
		return _PortVector[Index];
	}

	return Midi::DummyPort;
}


#if defined(MCC_UART_MIDI_ENABLED)

	bool Midi::SystemPortHandler::BindPort(const UartMidi::Port& Port)
	{
		if(GetID(Port) == Midi::SystemPortHandler::InvalidPortID)
		{
			if(_PortVector.resize(_PortVector.size()+1))
			{
				_PortVector[_PortVector.size() - 1] = Midi::Port(Port);
				return 1;
			}
			return 0;
		}
		return 1;
	}

	void Midi::SystemPortHandler::UnbindPort(const UartMidi::Port& Port)
	{
    	if(&Port.Midi_Port() != &Midi::DummyPort)
    	{
    		auto ID = GetID(Port);

    		if( ID != SystemPortHandler::InvalidPortID )
    		{
    			_PortVector.erase(ID);
    		}            		
    	}
	}

	Midi::Port& Midi::SystemPortHandler::GetPort(const UartMidi::Port& Port)
	{
		auto ID = Midi::SystemPortHandler::GetID(Port);

		if(ID != Midi::SystemPortHandler::InvalidPortID)
		{
			return _PortVector[ID];
		}

		return Midi::DummyPort;
	}

	const Midi::SystemPortHandler::PortID& Midi::SystemPortHandler::GetID(const UartMidi::Port& Port) const
	{
		for(uint8_t i = 0; i < _PortVector.size(); i++)
		{
			if(_PortVector[i].ParentPointer() == &Port)
			{
				return (Midi::SystemPortHandler::PortID) i;
			} 
		}

		return Midi::SystemPortHandler::InvalidPortID;
	}


	#if defined(MCC_UART_PORT_ENABLED)
		bool Midi::SystemPortHandler::BindPort(const Uart::Port& Port)
		{
			if(&Port.UartMidi_Port() == &UartMidi::DummyPort)
			{
				if(!Port.UartMidi_BindPort()){return 0;}
			}

			if(GetID(Port) == Midi::SystemPortHandler::InvalidPortID)
			{
				return BindPort(Port.UartMidi_Port());
			}
			return 1;
		}

		void Midi::SystemPortHandler::UnbindPort(const Uart::Port& Port)
		{
        	if(&Port.Midi_Port() != &Midi::DummyPort)
        	{
        		auto ID = GetID(Port);

        		if( ID != SystemPortHandler::InvalidPortID )
        		{
        			_PortVector.erase(ID);
        		}            		
        	}
		}

		Midi::Port& Midi::SystemPortHandler::GetPort(const Uart::Port& Port)
		{
			auto ID = GetID(Port);

			if(ID != Midi::SystemPortHandler::InvalidPortID)
			{
				return _PortVector[ID];
			}

			return Midi::DummyPort;
		}

		const Midi::SystemPortHandler::PortID& Midi::SystemPortHandler::GetID(const Uart::Port& Port) const
		{
			for(uint8_t i = 0; i < _PortVector.size(); i++)
			{
				if(_PortVector[i].ParentType() == Midi::PortTypes::UartMidi)
				{
					auto UartMidiPortPtr = (Midi::UartMidi::Port*) _PortVector[i].ParentPointer();

					if( UartMidiPortPtr -> Uart_PortPointer() == &Port )
					{
						return (Midi::SystemPortHandler::PortID) i;
					}
				}

			}

			return Midi::SystemPortHandler::InvalidPortID;
		}


        #if defined(MCC_UART_IN_ENABLED)
            bool Midi::SystemPortHandler::BindPort(const Uart::Input::Port& Port)
            {
				if(&Port.UartMidi_Port() == &UartMidi::DummyPort)
				{
					if(!Midi::UartMidi::SystemPorts.BindPort(Port)){return 0;}
				}

				if(GetID(Port) == Midi::SystemPortHandler::InvalidPortID)
				{
					return BindPort(Port.UartMidi_Port());
				}
				return 1;
            }

            void Midi::SystemPortHandler::UnbindPort(const Uart::Input::Port& Port)
            {
            	if(&Port.Midi_Port() != &Midi::DummyPort)
            	{
            		auto ID = GetID(Port);

            		if( ID != SystemPortHandler::InvalidPortID )
            		{
            			_PortVector.erase(ID);
            		}            		
            	}
            }

			Midi::SystemPortHandler::PortID Midi::SystemPortHandler::GetID(const Uart::Input::Port& Port)
			{
				for(uint8_t i = 0; i < _PortVector.size(); i++)
				{
					if(_PortVector[i].ParentType() == Midi::PortTypes::UartMidi)
					{
						auto UartMidiPortPtr = (Midi::UartMidi::Port*) _PortVector[i].ParentPointer();
						if( UartMidiPortPtr -> Uart_PortPointer() == &Port.Uart_Port() )
						{
							return (Midi::SystemPortHandler::PortID) i;
						}
					} 
				}

				return Midi::SystemPortHandler::InvalidPortID;
			}

            Midi::Port& Midi::SystemPortHandler::GetPort(const Uart::Input::Port& Port)
            {
				auto ID = GetID(Port);

				if(ID != Midi::SystemPortHandler::InvalidPortID)
				{
					return _PortVector[ID];
				}

				return Midi::DummyPort;
            }

        #endif


        #if defined(MCC_UART_OUT_ENABLED)
            bool Midi::SystemPortHandler::BindPort(const Uart::Output::Port& Port)
            {
				if(&Port.UartMidi_Port() == &UartMidi::DummyPort)
				{
					if(!Midi::UartMidi::SystemPorts.BindPort(Port)){return 0;}
				}

				if(GetID(Port) == Midi::SystemPortHandler::InvalidPortID)
				{
					return BindPort(Port.UartMidi_Port());
				}
				return 1;
            }

            void Midi::SystemPortHandler::UnbindPort(const Uart::Output::Port& Port)
            {
            	if(&Port.Midi_Port() != &Midi::DummyPort)
            	{
            		auto ID = GetID(Port);

            		if( ID != SystemPortHandler::InvalidPortID )
            		{
            			_PortVector.erase(ID);
            		}            		
            	}
            }

			Midi::SystemPortHandler::PortID Midi::SystemPortHandler::GetID(const Uart::Output::Port& Port)
			{
				for(uint8_t i = 0; i < _PortVector.size(); i++)
				{
					if(_PortVector[i].ParentType() == Midi::PortTypes::UartMidi)
					{
						auto UartMidiPortPtr = (Midi::UartMidi::Port*) _PortVector[i].ParentPointer();
						if( UartMidiPortPtr -> Uart_PortPointer() == &Port.Uart_Port() )
						{
							return (Midi::SystemPortHandler::PortID) i;
						}
					} 
				}

				return Midi::SystemPortHandler::InvalidPortID;
			}

            Midi::Port& Midi::SystemPortHandler::GetPort(const Uart::Output::Port& Port)
            {
				auto ID = GetID(Port);

				if(ID != Midi::SystemPortHandler::InvalidPortID)
				{
					return _PortVector[ID];
				}

				return Midi::DummyPort;
            }

        #endif

	#endif
#endif