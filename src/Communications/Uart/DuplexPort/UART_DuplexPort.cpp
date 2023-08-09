#include "UART_DuplexPort.h"
#include <Core/MidiCore/MidiCore.h>

#if defined(MCC_MIDI_PORT_ENABLED)
    #include <Communications/Midi/MCC_Midi.h>
	using namespace MusicCompositionCore::Communications::Midi;
#endif


	using namespace MusicCompositionCore::Communications::Uart;
	using namespace MusicCompositionCore::Communications;

namespace MusicCompositionCore::Communications::Uart
{
	namespace
	{
		static const CPString::string DuplexPortStr("Uart Duplex Port");
	}
}
	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors

	Duplex::Port::Port()
	{
		HLAPI_Unlink();

		_Name = DuplexPortStr;
	}

	Duplex::Port::Port( const CPString::string& PortName )
	{
		HLAPI_Unlink();

		_Name = PortName;
	}

	Duplex::Port::Port(uint8_t(&Available)(void), uint8_t(&Read)(void), void(&Write)(uint8_t))
	{
        HLAPI_Unlink();
		HLAPI_Link(Available, Read, Write);

		_Name = DuplexPortStr;

		Uart_BindPort();
	}

	Duplex::Port::Port( const CPString::string& PortName, uint8_t(&Available)(void), uint8_t(&Read)(void), void(&Write)(uint8_t))
	{
        HLAPI_Unlink();
		HLAPI_Link(Available, Read, Write);

		_Name = PortName;

		Uart_BindPort();
	}

	Duplex::Port::Port(uint8_t(&Available)(void), uint8_t(&Read)(void), void(&Write)(uint8_t), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
        HLAPI_Unlink();
		HLAPI_Link(Available, Read, Write, Initialize, SetBaudRate);

		_Name = DuplexPortStr;

		Uart_BindPort();
	}

	Duplex::Port::Port( const CPString::string& PortName, uint8_t(&Available)(void), uint8_t(&Read)(void), void(&Write)(uint8_t), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
        HLAPI_Unlink();
		HLAPI_Link(Available, Read, Write, Initialize, SetBaudRate);

		_Name = PortName;

		Uart_BindPort();
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hardware Link API

	const bool Duplex::Port::HLAPI_Status() const
	{
		// Only checks if _Write() is binded, because the other functionality is optional
		if( WriteAPI_Status() && AvailableAPI_Status() && ReadAPI_Status() ){ return 1; }
		return 0;
	}
	 
	void Duplex::Port::HLAPI_Link(uint8_t (&Available)(void), uint8_t (&Read)(void), void(&Write)(uint8_t), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
		AvailableAPI_Link(Available);
		ReadAPI_Link(Read);
		WriteAPI_Link(Write);

		InitializeAPI_Link(Initialize);
		SetBaudRateAPI_Link(SetBaudRate);

		Uart_BindPort();
	}

    void Duplex::Port::HLAPI_Link(uint8_t (&Available)(void), uint8_t (&Read)(void), void(&Write)(uint8_t) )
    {
		AvailableAPI_Link(Available);
		ReadAPI_Link(Read);
		WriteAPI_Link(Write);

		Uart_BindPort();
    }

	void Duplex::Port::HLAPI_Unlink()
	{
		Uart_UnbindPort();

		AvailableAPI_Unlink();
		ReadAPI_Unlink();
		WriteAPI_Unlink();
		
		SetBaudRateAPI_Unlink();
		InitializeAPI_Unlink();
	}

	const bool Duplex::Port::AvailableAPI_Status() const
	{
		if( _Available != NULL ){ return 1; }
		return 0;
	}

	void Duplex::Port::AvailableAPI_Link(uint8_t (&Available)(void))
	{
		_Available = Available;
	}

	void Duplex::Port::AvailableAPI_Unlink()
	{
		_Available = NULL;
	}

	const bool Duplex::Port::ReadAPI_Status() const
	{
		if( _Read != NULL ){ return 1; }
		return 0;
	}

	void Duplex::Port::ReadAPI_Link(uint8_t (&Read)(void))
	{
		_Read = Read;
	}

	void Duplex::Port::ReadAPI_Unlink()
	{
		_Read = NULL;
	}

	const bool Duplex::Port::WriteAPI_Status() const
	{
		if( _Write != NULL ){ return 1; }
		return 0;
	}
	
	void Duplex::Port::WriteAPI_Link(void (&Write)(uint8_t))
	{
		_Write = Write;
	}
	
	void Duplex::Port::WriteAPI_Unlink()
	{
		_Write = NULL;
	}

	const bool Duplex::Port::InitializeAPI_Status() const
	{
		if( _Initialize != NULL ){ return 1; }
		return 0;
	}
	
	void Duplex::Port::InitializeAPI_Link(void (&Initialize)(void))
	{
		_Initialize = Initialize;
	}
	
	void Duplex::Port::InitializeAPI_Unlink()
	{
		_Initialize = NULL;
	}

	const bool Duplex::Port::SetBaudRateAPI_Status() const
	{
		if( _SetBaudRate != NULL ){ return 1; }
		return 0;
	}
	
	void Duplex::Port::SetBaudRateAPI_Link(void (&SetBaudRate)(uint32_t))
	{
		_SetBaudRate = SetBaudRate;
	}
	
	void Duplex::Port::SetBaudRateAPI_Unlink()
	{
		_SetBaudRate = NULL;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generic Uart Port API

	const CPString::string& Duplex::Port::Name() const
	{
		return _Name;
	}

	void Duplex::Port::SetName(const CPString::string& NewName)
	{
		_Name = NewName;
	}
	
	void Duplex::Port::Initialize()
	{
		if(_Initialize != NULL)
		{
			_Initialize();
		}
	}

	void Duplex::Port::SetBaudRate(uint32_t BaudRate)
	{
		if(_SetBaudRate != NULL)
		{
			_SetBaudRate(BaudRate);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UART In API
    
	uint8_t Duplex::Port::BytesAvailable()
	{
		if(AvailableAPI_Status()) 
		{
			return _Available();
		}
		return 0;
	}

	uint8_t Duplex::Port::ReadByte()
	{
		if(ReadAPI_Status())
		{
			return _Read();
		}
		return 0;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UART Out API

	void Duplex::Port::WriteByte(uint8_t Data)
	{
		if (WriteAPI_Status())
		{
			_Write(Data);
		}
	}

	void Duplex::Port::WriteBuffer(uint8_t* Data, uint8_t size)
	{
		if (WriteAPI_Status())
		{
			if( (sizeof(*Data)/sizeof(uint8_t)) >= size )
			{
				for( uint8_t i = 0; i < size; i++ )
				{
					_Write(Data[i]);
				}
			}
		}
	}

	void Duplex::Port::WriteBuffer(const CPVector::vector<uint8_t>& Data)
	{
		if (WriteAPI_Status())
		{
			for( uint8_t i = 0; i < Data.size(); i++ )
			{
				_Write(Data[i]);
			}
		}
	}

//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UART::Port API

	bool Duplex::Port::Uart_BindPort() const
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

	void Duplex::Port::Uart_UnbindPort() const
	{
		Uart::SystemPorts.UnbindPort( (*this) );
	}

	Uart::SystemPortHandler::PortID Duplex::Port::Uart_PortID() const
	{
		return Uart::SystemPorts.GetID(*this);
	}

	Uart::Port& Duplex::Port::Uart_Port() const
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

		bool Duplex::Port::UartMidi_BindPort() const
		{
			return Midi::UartMidi::SystemPorts.BindPort(*this);
		}

		void Duplex::Port::UartMidi_UnbindPort() const
		{
			Midi::UartMidi::SystemPorts.UnbindPort(*this);
		}

		Midi::UartMidi::SystemPortHandler::PortID Duplex::Port::UartMidi_PortID() const
		{
			return Midi::UartMidi::SystemPorts.GetID(*this);
		}

		
		Midi::UartMidi::Port& Duplex::Port::UartMidi_Port() const
		{
			return Midi::UartMidi::SystemPorts.GetPort(*this);
		}
	#endif
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Midi::Port API
	
	#if defined(MCC_MIDI_PORT_ENABLED) & defined(MCC_UART_MIDI_ENABLED)

		bool Duplex::Port::Midi_BindPort() const
		{
			return Midi::SystemPorts.BindPort(*this);
		}

		void Duplex::Port::Midi_UnbindPort() const
		{
			Midi::SystemPorts.UnbindPort( *this );
		}

		Midi::SystemPortHandler::PortID Duplex::Port::Midi_PortID() const
		{
			auto UartMidiID = UartMidi_PortID();
        
			if(UartMidiID != Midi::UartMidi::SystemPortHandler::InvalidPortID )
			{
				return Midi::SystemPorts.GetID( *this );
			}
        
			return Midi::SystemPortHandler::InvalidPortID;
		}

		Midi::Port& Duplex::Port::Midi_Port() const
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

	void Duplex::Port::SetSysExFlag(bool State)
	{
        _FlagRegister &= 0b11111101;
        _FlagRegister |= (State<<1u);
	}

	const bool Duplex::Port::SysExFlag() const
	{
        return (_FlagRegister >> 1u) & 1u;
	}

	void Duplex::Port::SetSOMF(bool State)
	{
        _FlagRegister &= 0b11111011;
        _FlagRegister |= (State<<2u);
	}

	const bool Duplex::Port::SOMF() const
	{
        return (_FlagRegister >> 2u) & 1u;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
