#include "UartMidi.h"
#include "../MidiPort.h"
#include <MCC.h>


using namespace MCC::Communications::Midi;

CPVector::vector<Uart::Port> Uart::SystemPorts;

bool Uart::BindPort(const InputPort& Port)
{
	bool flag = 1;

	for(uint8_t i = 0; i < SystemPorts.size(); i++ )
	{
		if( SystemPorts[i].ParentType() == PortTypes::InputPort)
		{
			if( (InputPort*)SystemPorts[i].ParentPointer() == (&Port) ){ flag = 0; }
		}
	}

	if(flag) // Port is not already appended
	{
        if( SystemPorts.resize(SystemPorts.size() + 1) )
        {
            SystemPorts[SystemPorts.size()-1].LinkToPort(Port);
            return 1;
        }
        else{ return  0; }
	}
}

void Uart::ReleasePort(const InputPort& Port)
{
	for(uint8_t i = 0; i < SystemPorts.size(); i++)
	{
		if( SystemPorts[i].ParentType() == PortTypes::InputPort )
		{
			if( (InputPort*) SystemPorts[i].ParentPointer() == (&Port) )
			{
				SystemPorts.erase(i);
			}
		}
	}
}

Uart::PortID Uart::GetSystemPortID(const InputPort& Port)
{
	for(uint8_t i = 0; i < SystemPorts.size(); i++)
	{
		if( SystemPorts[i].ParentType() == PortTypes::InputPort )
		{
			if( (InputPort*) SystemPorts[i].ParentPointer() == (&Port) )
			{
				return (PortID)i;
			}
		}
	}

	return InvalidPortID;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors

	Uart::Port::Port()
	{
		UnlinkFromPort();
	}



	Uart::Port::Port(const InputPort& Parent)
	{
		UnlinkFromPort();
		LinkToPort(Parent);
	}

	//UartPort(const Uart::OutputPort& Parent);
	//UartPort(const Uart::DuplexPort& Parent);
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// High Level API

	void Uart::Port::LinkToPort(const InputPort& Parent)
	{
	    _PortPointer = (void*) &Parent;
	    _PortType = PortTypes::InputPort;
	    Midi::BindPort(*this);
	}

	void Uart::Port::UnlinkFromPort()
	{
	    _PortPointer = NULL;
	    _PortType = PortTypes::InvalidType;
	    Midi::ReleasePort(*this);
	}

	const Uart::PortType& Uart::Port::ParentType() const
	{
	    return  _PortType;
	}

	const void* Uart::Port::ParentPointer() const
	{
	    return _PortPointer;
	}
//
///////////////////////////////////////////////////////////////////////
// Midi Port Generic API

	const CPString::string& Uart::Port::Name() const
	{
		switch(_PortType)
		{
            case PortTypes::InputPort: return ((InputPort*) _PortPointer) -> Name();
			default: break;
		} 

		return CPString::string("");
	}

	void Uart::Port::SetName(const CPString::string& NewName)
	{
		switch(_PortType)
		{
            case PortTypes::InputPort: ((InputPort*) _PortPointer) -> SetName(NewName);  break;
			default: break;
		} 
	}
//
///////////////////////////////////////////////////////////////////////
// Midi In API

	void Uart::Port::AppendCallback(void(*Callback)(CPVector::vector<uint8_t>&))
	{
		switch(_PortType)
		{
            case PortTypes::InputPort: ((InputPort*) _PortPointer) -> AppendCallback(Callback);  break;
			default: break;
		}
	}

	void Uart::Port::DetachCallback(void(*Callback)(CPVector::vector<uint8_t>&))
	{
		switch(_PortType)
		{
            case PortTypes::InputPort: ((InputPort*) _PortPointer) -> DetachCallback(Callback);  break;
			default: break;
		}
	}

	void Uart::Port::SetBufferSize(uint8_t size)
	{
		switch(_PortType)
		{
            case PortTypes::InputPort: ((InputPort*) _PortPointer) -> SetBufferSize(size);  break;
			default: break;
		}
	}

	void Uart::Port::Service()
	{
		switch(_PortType)
		{
            case PortTypes::InputPort: ((InputPort*) _PortPointer) -> Service();  break;
			default: break;
		}
	}
//
///////////////////////////////////////////////////////////////////////
