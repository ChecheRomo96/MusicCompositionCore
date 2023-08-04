#include "../Uart.h"

#if defined(MCC_MIDI_PORT_ENABLED)
	using namespace MCC::Communications::Midi;
#endif

using namespace MCC::Communications;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors

	Uart::Port::Port()
	{
		UnlinkFromPort();
	}

	Uart::Port& Uart::Port::operator=(const Port& Rhs)
    {
    	if(this == &Rhs){return (*this);}

    	_PortPointer = (void*)Rhs.ParentPointer();
    	_PortType = Rhs.ParentType();

    	return (*this);
    }


	#if defined (MCC_UART_IN_ENABLED)
		
		Uart::Port::Port(const Uart::Input::Port& Parent)
		{
			UnlinkFromPort();
			LinkToPort(Parent);
		}
	#endif

	#if defined (MCC_UART_OUT_ENABLED)
		
		Uart::Port::Port(const Uart::Output::Port& Parent)
		{
			UnlinkFromPort();
			LinkToPort(Parent);
		}
	#endif

	//UartPort(const Uart::DuplexPort& Parent);
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// High Level API

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
			#if defined (MCC_UART_IN_ENABLED)
            	case PortTypes::InputPort: return ((Uart::Input::Port*) _PortPointer) -> Name();
            #endif

			#if defined (MCC_UART_OUT_ENABLED)
            	case PortTypes::OutputPort: return ((Uart::Output::Port*) _PortPointer) -> Name();
            #endif

			default: break;
		} 

		return CPString::string("");
	}

	void Uart::Port::SetName(const CPString::string& NewName)
	{
		switch(_PortType)
		{
			#if defined (MCC_UART_IN_ENABLED)
            	case PortTypes::InputPort: ((Uart::Input::Port*) _PortPointer) -> SetName(NewName);  break;
            #endif

			#if defined (MCC_UART_IN_ENABLED)
            	case PortTypes::OutputPort: ((Uart::Output::Port*) _PortPointer) -> SetName(NewName);  break;
            #endif

			default: break;
		} 
	}
//
///////////////////////////////////////////////////////////////////////
// Uart In API
	                        
	uint8_t Uart::Port::BytesAvailable()
	{
		switch(_PortType)
		{	
			#if defined (MCC_UART_IN_ENABLED)
            	case PortTypes::InputPort: return ((Uart::Input::Port*) _PortPointer) -> BytesAvailable();
            #endif

			#if defined (MCC_UART_DUPLEX_PORT_ENABLED)
            	case PortTypes::DuplexPort: return ((DuplexPort*) _PortPointer) -> BytesAvailable();
            #endif

			default: return 0;
		}
	}

	uint8_t Uart::Port::ReadByte()
	{
		switch(_PortType)
		{	
			#if defined (MCC_UART_IN_ENABLED)
            	case PortTypes::InputPort: return ((Uart::Input::Port*) _PortPointer) -> ReadByte();
            #endif

			#if defined (MCC_UART_DUPLEX_PORT_ENABLED)
            	case PortTypes::DuplexPort: return ((DuplexPort*) _PortPointer) -> ReadByte();
            #endif

			default: return 0;
		}
	}
//
///////////////////////////////////////////////////////////////////////
// Uart Out API

	void Uart::Port::Write(uint8_t Data)
	{
		switch(_PortType)
		{	
			#if defined (MCC_UART_OUT_ENABLED)
            	case PortTypes::OutputPort: ((Uart::Output::Port*) _PortPointer) -> WriteByte(Data);  break;
            #endif

			#if defined (MCC_UART_DUPLEX_PORT_ENABLED)
            	case PortTypes::DuplexPort: ((DuplexPort*) _PortPointer) -> Write(Data);  break;
            #endif

			default: break;
		}
	}

    void Uart::Port::WriteBuffer(uint8_t* Data, uint8_t Len)
    {
		switch(_PortType)
		{	
			#if defined (MCC_UART_OUT_ENABLED)
	        	case PortTypes::OutputPort: ((Uart::Output::Port*) _PortPointer) -> WriteBuffer(Data,Len);  break;
	        #endif

			#if defined (MCC_UART_DUPLEX_PORT_ENABLED)
	        	case PortTypes::DuplexPort: ((DuplexPort*) _PortPointer) -> WriteBuffer(Data,Len);  break;
	        #endif
    	}
    }

    void Uart::Port::WriteBuffer(const CPVector::vector<uint8_t>& Data)
    {
		switch(_PortType)
		{	
			#if defined (MCC_UART_OUT_ENABLED)
	        	case PortTypes::OutputPort: ((Uart::Output::Port*) _PortPointer) -> WriteBuffer(Data);  break;
	        #endif

			#if defined (MCC_UART_DUPLEX_PORT_ENABLED)
	        	case PortTypes::DuplexPort: ((DuplexPort*) _PortPointer) -> WriteBuffer(Data);  break;
	        #endif
    	}
    }
//
///////////////////////////////////////////////////////////////////////
// Midi::UartMidi API

    #if defined(MCC_UART_MIDI_ENABLED)
    	bool Uart::Port::UartMidi_BindPort() const
    	{
    		auto UartMidiID = UartMidi_PortID();
    		if(UartMidiID == Midi::UartMidi::SystemPortHandler::InvalidPortID)
    		{ 
    			if(Midi::UartMidi::SystemPorts.BindPort(*this)){ return 1; }
    			else{ return 0; }
    		}
    		return 0;
    	}

    	void Uart::Port::UartMidi_UnbindPort() const
    	{
    		Midi::UartMidi::SystemPorts.UnbindPort(*this);
    	}

		Midi::UartMidi::SystemPortHandler::PortID Uart::Port::UartMidi_PortID() const
		{
			return Midi::UartMidi::SystemPorts.GetID(*this);
		}

		Midi::UartMidi::Port& Uart::Port::UartMidi_Port() const
		{
			return Midi::UartMidi::DummyPort;
		}

    #endif
//
///////////////////////////////////////////////////////////////////////
// Midi API

    #if defined(MCC_UART_MIDI_ENABLED) & defined(MCC_UART_MIDI_ENABLED)

    	bool Uart::Port::Midi_BindPort() const
    	{
    		return 0;
    	}
    	
    	void Uart::Port::Midi_UnbindPort() const
    	{

    	}
    	
		Midi::SystemPortHandler::PortID Uart::Port::Midi_PortID() const
		{
			return Midi::SystemPortHandler::InvalidPortID;
		}
		
		Midi::Port& Uart::Port::Midi_Port() const
		{
			return Midi::DummyPort;
		}
		
    #endif
//
//////////////////////////////////////////////////////////////////////
// Uart Port Link Helpers

	void Uart::Port::UnlinkFromPort()
	{
		_PortPointer = NULL;
		_PortType = Uart::PortTypes::InvalidType;
	}

	//////////////////////////////////////////////////////////////////
    // Uart In Heplers

		#if defined (MCC_UART_IN_ENABLED)
            void Uart::Port::LinkToPort(const Uart::Input::Port& Parent)
            {
            	_PortPointer = (void*) &Parent;
            	_PortType = Uart::PortTypes::InputPort;
            }
		#endif

		#if defined (MCC_UART_OUT_ENABLED)
            void Uart::Port::LinkToPort(const Uart::Output::Port& Parent)
            {
            	_PortPointer = (void*) &Parent;
            	_PortType = Uart::PortTypes::OutputPort;
            }
		#endif
	//
	///////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////
