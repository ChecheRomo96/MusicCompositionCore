#include "MidiPort.h"
#include <MCC.h>

using namespace MCC::Communications;

CPVector::vector<Midi::Port> Midi::SystemPorts;

bool Midi::BindPort(const Uart::MidiPort& Port)
{
	bool flag = 1;

	for(uint8_t i = 0; i < Midi::SystemPorts.size(); i++ )
	{
		if( Midi::SystemPorts[i].ParentType() == PortTypes::Uart)
		{
			if( (Uart::MidiPort*)Midi::SystemPorts[i].ParentPointer() == (&Port) ){ flag = 0; }
		}
	}

	if(flag) // Port is not already appended
	{
        if( Midi::SystemPorts.resize(Midi::SystemPorts.size() + 1) )
        {
            Midi::SystemPorts[Midi::SystemPorts.size()-1].LinkToPort(Port);
            return 1;
        }
	}

	return 0;
} 

void Midi::ReleasePort(const Uart::MidiPort& Port)
{
	for(uint8_t i = 0; i < SystemPorts.size(); i++)
	{
		if( Midi::SystemPorts[i].ParentType() == PortTypes::Uart )
		{
			if( (Uart::MidiPort*) SystemPorts[i].ParentPointer() == (&Port) )
			{
				Midi::SystemPorts.erase(i);
			}
		}
	}
} 

Midi::PortID Midi::GetSystemPortID(const Uart::MidiPort& Port)
{
	for(uint8_t i = 0; i < SystemPorts.size(); i++)
	{
		if( SystemPorts[i].ParentType() == PortTypes::Uart )
		{
			if( (Uart::MidiPort*) SystemPorts[i].ParentPointer() == (&Port) )
			{
				return (Midi::PortID)i;
			}
		}
	}

	return Midi::InvalidID;
}

///////////////////////////////////////////////////////////////////////
// Constructors

	Midi::Port::Port()
	{
		UnlinkFromPort();
	}

	Midi::Port::Port(const Uart::MidiPort& Parent)
	{
		UnlinkFromPort();
		LinkToPort(Parent);
	}


///////////////////////////////////////////////////////////////////////
// High Level API

	void Midi::Port::LinkToPort(const Uart::MidiPort& Parent)
	{
	    _PortPointer = (void*) &Parent;
	    _PortType = PortTypes::Uart;
	}

	void Midi::Port::UnlinkFromPort()
	{
	    _PortPointer = NULL;
	    _PortType = PortTypes::InvalidType;
	}


	const Midi::PortType& Midi::Port::ParentType() const
	{
	    return  _PortType;
	}

	const void* Midi::Port::ParentPointer() const
	{
	    return _PortPointer;
	}

//
///////////////////////////////////////////////////////////////////////
// Midi Port Generic API

	const CPString::string& Midi::Port::Name() const
	{
		switch(_PortType)
		{
	        case PortTypes::Uart: return ((Uart::MidiPort*) _PortPointer) -> Name();
			default: break;
		}

		return CPString::string("");
	}

	void Midi::Port::SetName(const CPString::string& NewName)
	{
		switch(_PortType)
		{
            case PortTypes::Uart: ((Uart::MidiPort*) _PortPointer) -> SetName(NewName);  break;
			default: break;
		} 
	}

//
///////////////////////////////////////////////////////////////////////
// Midi In API

    void Midi::Port::AppendCallback(void(*Callback)(CPVector::vector<uint8_t>&))
    {
		switch(_PortType)
		{
            case PortTypes::Uart: ((Uart::MidiPort*) _PortPointer) -> AppendCallback(Callback);  break;
			default: break;
		}
    }

    void Midi::Port::DetachCallback(void(*Callback)(CPVector::vector<uint8_t>&))
    {
		switch(_PortType)
		{
            case PortTypes::Uart: ((Uart::MidiPort*) _PortPointer) -> DetachCallback(Callback);  break;
			default: break;
		}
    }


    void Midi::Port::SetBufferSize(uint8_t size)
    {
		switch(_PortType)
		{
            case PortTypes::Uart: ((Uart::MidiPort*) _PortPointer) -> SetBufferSize(size);  break;
			default: break;
		}
    }


	void Midi::Port::Service()
	{
		switch(_PortType)
		{
            case PortTypes::Uart: ((Uart::MidiPort*) _PortPointer) -> Service();  break;
			default: break;
		}
	}

//
///////////////////////////////////////////////////////////////////////

