#include "UART_InputPort.h"
#include <Core/MidiCore/MidiCore.h>

#if defined(MCC_MIDI_PORT_ENABLED)
    #include <Communications/Midi/MCC_Midi.h>
	using namespace MusicCompositionCore::Communications::Midi;
#endif


	using namespace MusicCompositionCore::Communications::Uart;
	using namespace MusicCompositionCore::Communications;

namespace MusicCompositionCore
{
	namespace Communications
	{
		namespace Uart
		{
			namespace
			{
				static const CPString::string InputPortStr("Uart Input Port");
			}
		}
	}
}
	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors

	Input::Port::Port()
	{
		HLAPI_Unlink();

		_FlagRegister = 0;
		_Name = InputPortStr;
	}

	Input::Port::Port( const CPString::string& PortName )
	{
		HLAPI_Unlink();

		_FlagRegister = 0;
		_Name = PortName;
	}

	Input::Port::Port( uint8_t (&Available)(void), uint8_t (&Read)(void) )
	{
        HLAPI_Unlink();
		HLAPI_Link(Available,Read);

		_FlagRegister = 0;
		_Name = InputPortStr;

		Uart_BindPort();
	}

	Input::Port::Port( const CPString::string& PortName, uint8_t (&Available)(void), uint8_t (&Read)(void) )
	{
        HLAPI_Unlink();
		HLAPI_Link(Available,Read);

		_FlagRegister = 0;
		_Name = PortName;

		Uart_BindPort();
	}

	Input::Port::Port( uint8_t (&Available)(void), uint8_t (&Read)(void), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
        HLAPI_Unlink();
		HLAPI_Link(Available,Read,Initialize,SetBaudRate);

		_FlagRegister = 0;
		_Name = InputPortStr;

		Uart_BindPort();
	}

	Input::Port::Port( const CPString::string& PortName, uint8_t (&Available)(void), uint8_t (&Read)(void), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
        HLAPI_Unlink();
		HLAPI_Link(Available,Read,Initialize,SetBaudRate);

		_FlagRegister = 0;
		_Name = PortName;

		Uart_BindPort();
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hardware Link API
	 
	void Input::Port::HLAPI_Link( uint8_t (&Available)(void), uint8_t (&Read)(void), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
		_Initialize = Initialize;
		_SetBaudRate = SetBaudRate;
		_Available = Available;
		_Read = Read;

		Uart_BindPort();
	}

    void Input::Port::HLAPI_Link( uint8_t (&Available)(void), uint8_t (&Read)(void) )
    {
       _Available = Available;
       _Read = Read;

	   Uart_BindPort();
    }

	void Input::Port::HLAPI_Unlink()
	{
		_Available = NULL;
		_Read = NULL;
		_SetBaudRate = NULL;
		_Initialize = NULL;
		
		Uart_UnbindPort();
	}

	const bool Input::Port::HLAPI_Status() const
	{
		// Only checks id _Available and _Read are binded, because the other functionality is optional
		if( (_Available != NULL) && (_Read != NULL) )
		{
			return 1;
		}
		return 0;
	}

	const bool Input::Port::AvailableAPI_Status() const
	{
		if( _Available != NULL ){ return 1; }
		return 0;
	}

	const bool Input::Port::ReadAPI_Status() const
	{
		if( _Read != NULL ){ return 1; }
		return 0;
	}

	const bool Input::Port::InitializeAPI_Status() const
	{
		if( _Initialize != NULL ){ return 1; }
		return 0;
	}

	const bool Input::Port::SetBaudRateAPI_Status() const
	{
		if( _SetBaudRate != NULL ){ return 1; }
		return 0;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generic Uart Port API

	const CPString::string& Input::Port::Name() const
	{
		return _Name;
	}

	void Input::Port::SetName(const CPString::string& NewName)
	{
		_Name = NewName;
	}
	
	void Input::Port::Initialize()
	{
		if(_Initialize != NULL)
		{
			_Initialize();
		}
	}

	void Input::Port::SetBaudRate(uint32_t BaudRate)
	{
		if(_SetBaudRate != NULL)
		{
			_SetBaudRate(BaudRate);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UART In API


	uint8_t Input::Port::BytesAvailable()
	{
		if(AvailableAPI_Status()) 
		{
			return _Available();
		}
		return 0;
	}

	uint8_t Input::Port::ReadByte()
	{
		if(ReadAPI_Status())
		{
			return _Read();
		}
		return 0;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UART::Port API

	bool Input::Port::Uart_BindPort() const
	{
		if(HLAPI_Status())
		{
			return Uart::SystemPorts.BindPort( (*this) );
		}
		else
		{
			Uart_UnbindPort();
		}
		return 0;
	}

	void Input::Port::Uart_UnbindPort() const
	{
		Uart::SystemPorts.UnbindPort( (*this) );
	}

	Uart::SystemPortHandler::PortID Input::Port::Uart_PortID() const
	{
		return Uart::SystemPorts.GetID(*this);
	}

	Uart::Port& Input::Port::Uart_Port() const
	{
		uint8_t ID = Uart_PortID();

		if(ID != Uart::SystemPortHandler::InvalidPortID)
		{
			return Uart::SystemPorts[ID];
		}

		return Uart::DummyPort;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UartMidi::Port API

	#if defined(MCC_MIDI_PORT_ENABLED) & defined(MCC_UART_MIDI_ENABLED)

		bool Input::Port::UartMidi_BindPort() const
		{
			return Midi::UartMidi::SystemPorts.BindPort(*this);
		}

		void Input::Port::UartMidi_UnbindPort() const
		{
			Midi::UartMidi::SystemPorts.UnbindPort(*this);
		}

		Midi::UartMidi::SystemPortHandler::PortID Input::Port::UartMidi_PortID() const
		{
			return Midi::UartMidi::SystemPorts.GetID(*this);
		}

		
		Midi::UartMidi::Port& Input::Port::UartMidi_Port() const
		{
			return Midi::UartMidi::SystemPorts.GetPort(*this);
		}


	#endif
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Midi::Port API
	
	#if defined(MCC_MIDI_PORT_ENABLED) & defined(MCC_UART_MIDI_ENABLED)

		bool Input::Port::Midi_BindPort() const
		{
			return Midi::SystemPorts.BindPort(*this);
		}

		void Input::Port::Midi_UnbindPort() const
		{
			Midi::SystemPorts.UnbindPort( *this );
		}

		Midi::SystemPortHandler::PortID Input::Port::Midi_PortID() const
		{
			auto UartMiditID = UartMidi_PortID();
        
			if(UartMiditID != Midi::UartMidi::SystemPortHandler::InvalidPortID )
			{
				return Midi::SystemPorts.GetID( *this );
			}
        
			return Midi::SystemPortHandler::InvalidPortID;
		}


		Midi::Port& Input::Port::Midi_Port() const
		{
			auto MiditID = Midi_PortID();
        
			if(MiditID != Midi::SystemPortHandler::InvalidPortID )
			{
				return Midi::SystemPorts[MiditID];
			}
        
			return Midi::DummyPort;
		}
	#endif	
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers

	void Input::Port::SetSysExFlag(bool State)
	{
        _FlagRegister &= 0b11111101;
        _FlagRegister |= (State<<1u);
	}

	const bool Input::Port::SysExFlag() const
	{
        return (_FlagRegister >> 1u) & 1u;
	}

	void Input::Port::SetSOMF(bool State)
	{
        _FlagRegister &= 0b11111011;
        _FlagRegister |= (State<<2u);
	}

	const bool Input::Port::SOMF() const
	{
        return (_FlagRegister >> 2u) & 1u;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
