#include "Uart.h"
#include <MCC.h>

#if defined(MCC_MIDI_PORT_ENABLED)
	#include <Communications/Midi/Midi.h>
	using namespace MCC::Communications::Midi;
#endif

using namespace MCC::Communications;

CPVector::vector<Uart::Port> Uart::SystemPorts;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors

	Uart::Port::Port()
	{
		UnlinkFromPort();
	}


	#if defined (MCC_UART_MIDI_IN_ENABLED)
		
		Uart::Port::Port(const InputPort& Parent)
		{
			UnlinkFromPort();
			LinkToPort(Parent);
		}

	#endif

	//UartPort(const Uart::OutputPort& Parent);
	//UartPort(const Uart::DuplexPort& Parent);
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// High Level API


	#if defined (MCC_UART_MIDI_IN_ENABLED)

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

	#endif

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
// Port Generic API

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
// Uart In API

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
// Uart Out API

	void Uart::Port::Write(uint8_t Data)
	{
		switch(_PortType)
		{	
			#if defined (MCC_UART_OUT_PORT_ENABLED)
            	case PortTypes::OutputPort: ((OutputPort*) _PortPointer) -> Service();  break;
            #endif

			#if defined (MCC_UART_DUPLEX_PORT_ENABLED)
            	case PortTypes::DuplexPort: ((DuplexPort*) _PortPointer) -> Service();  break;
            #endif

			default: break;
		}
	}
//
///////////////////////////////////////////////////////////////////////