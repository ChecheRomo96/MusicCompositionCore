#include "UART_OutputPort.h"
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
				static const CPString::string OutputPortStr("Uart Output Port");
			}
		}
	}
}
	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors

	Output::Port::Port()
	{
		HLAPI_Unlink();

		_Name = OutputPortStr;
	}

	Output::Port::Port( const CPString::string& PortName )
	{
		HLAPI_Unlink();

		_Name = PortName;
	}

	Output::Port::Port(void(&Write)(uint8_t))
	{
        HLAPI_Unlink();
		HLAPI_Link(Write);

		_Name = OutputPortStr;

		Uart_BindPort();
	}

	Output::Port::Port( const CPString::string& PortName, void(&Write)(uint8_t))
	{
        HLAPI_Unlink();
		HLAPI_Link(Write);

		_Name = PortName;

		Uart_BindPort();
	}

	Output::Port::Port(void(&Write)(uint8_t), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
        HLAPI_Unlink();
		HLAPI_Link(Write,Initialize,SetBaudRate);

		_Name = OutputPortStr;

		Uart_BindPort();
	}

	Output::Port::Port( const CPString::string& PortName, void(&Write)(uint8_t), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
        HLAPI_Unlink();
		HLAPI_Link(Write,Initialize,SetBaudRate);

		_Name = PortName;

		Uart_BindPort();
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hardware Link API
	 
	void Output::Port::HLAPI_Link(void(&Write)(uint8_t), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
		_Initialize = Initialize;
		_SetBaudRate = SetBaudRate;
		_Write = Write;

		Uart_BindPort();
	}

    void Output::Port::HLAPI_Link(void(&Write)(uint8_t) )
    {
		_Write = Write;

	   Uart_BindPort();
    }

	void Output::Port::HLAPI_Unlink()
	{
		_Write = NULL;
		_SetBaudRate = NULL;
		_Initialize = NULL;
		
		Uart_UnbindPort();
	}

	const bool Output::Port::HLAPI_Status() const
	{
		// Only checks id _Available and _Read are binded, because the other functionality is optional
		if( (_Write != NULL)  )
		{
			return 1;
		}
		return 0;
	}

	const bool Output::Port::WriteAPI_Status() const
	{
		if( _Write != NULL ){ return 1; }
		return 0;
	}


	const bool Output::Port::InitializeAPI_Status() const
	{
		if( _Initialize != NULL ){ return 1; }
		return 0;
	}

	const bool Output::Port::SetBaudRateAPI_Status() const
	{
		if( _SetBaudRate != NULL ){ return 1; }
		return 0;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generic Uart Port API

	const CPString::string& Output::Port::Name() const
	{
		return _Name;
	}

	void Output::Port::SetName(const CPString::string& NewName)
	{
		_Name = NewName;
	}
	
	void Output::Port::Initialize()
	{
		if(_Initialize != NULL)
		{
			_Initialize();
		}
	}

	void Output::Port::SetBaudRate(uint32_t BaudRate)
	{
		if(_SetBaudRate != NULL)
		{
			_SetBaudRate(BaudRate);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UART Out API

	void Output::Port::WriteByte(uint8_t Data)
	{
		if (WriteAPI_Status())
		{
			_Write(Data);
		}
	}

	void Output::Port::WriteBuffer(uint8_t* Data, uint8_t size)
	{
		if (WriteAPI_Status())
		{
			if( (sizeof(Data)/sizeof(uint8_t)) >= size )
			{
				for( uint8_t i = 0; i < size; i++ )
				{
					_Write(Data[i]);
				}
			}
		}
	}

	void Output::Port::WriteBuffer(const CPVector::vector<uint8_t>& Data)
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

	bool Output::Port::Uart_BindPort() const
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

	void Output::Port::Uart_UnbindPort() const
	{
		Uart::SystemPorts.UnbindPort( (*this) );
	}

	Uart::SystemPortHandler::PortID Output::Port::Uart_PortID() const
	{
		return Uart::SystemPorts.GetID(*this);
	}

	Uart::Port& Output::Port::Uart_Port() const
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

		bool Output::Port::UartMidi_BindPort() const
		{
			return Midi::UartMidi::SystemPorts.BindPort(*this);
		}

		void Output::Port::UartMidi_UnbindPort() const
		{
			Midi::UartMidi::SystemPorts.UnbindPort(*this);
		}

		Midi::UartMidi::SystemPortHandler::PortID Output::Port::UartMidi_PortID() const
		{
			return Midi::UartMidi::SystemPorts.GetID(*this);
		}

		
		Midi::UartMidi::Port& Output::Port::UartMidi_Port() const
		{
			return Midi::UartMidi::SystemPorts.GetPort(*this);
		}


	#endif
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Midi::Port API
	
	#if defined(MCC_MIDI_PORT_ENABLED) & defined(MCC_UART_MIDI_ENABLED)

		bool Output::Port::Midi_BindPort() const
		{
			return Midi::SystemPorts.BindPort(*this);
		}

		void Output::Port::Midi_UnbindPort() const
		{
			Midi::SystemPorts.UnbindPort( *this );
		}

		Midi::SystemPortHandler::PortID Output::Port::Midi_PortID() const
		{
			auto UartMidiID = UartMidi_PortID();
        
			if(UartMidiID != Midi::UartMidi::SystemPortHandler::InvalidPortID )
			{
				return Midi::SystemPorts.GetID( *this );
			}
        
			return Midi::SystemPortHandler::InvalidPortID;
		}


		Midi::Port& Output::Port::Midi_Port() const
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