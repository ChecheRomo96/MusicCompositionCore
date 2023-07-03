#include "UartMidiOut.h"

#include "UartMidiIn.h"
#include "../../MidiPort.h"
#include "../../../../Core/MidiCore/MidiCore.h"

using namespace MusicCompositionCore::Communications::Midi::Uart;
using namespace MusicCompositionCore::Communications::Midi;
using namespace MusicCompositionCore::Communications;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors

	OutputPort::OutputPort()
	{
		HLAPI_Dettach();

		_Name = "Uart MIDI Out Port";
	}

	OutputPort::OutputPort( const CPString::string& PortName )
	{
		HLAPI_Dettach();

		_Name = PortName;
	}

	OutputPort::OutputPort( void (&Write)(uint8_t) )
	{
        HLAPI_Dettach();
		HLAPI_Attach(Write);

		_Name = "Uart MIDI In Port";
	}

	OutputPort::OutputPort( const CPString::string& PortName, void (&Write)(uint8_t) )
	{
        HLAPI_Dettach();
		HLAPI_Attach(Write);

		_Name = PortName;
	}

	OutputPort::OutputPort( void (&Write)(uint8_t), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
        HLAPI_Dettach();
		HLAPI_Attach(Write,Initialize,SetBaudRate);

		_Name = "Uart MIDI In Port";
	}

	OutputPort::OutputPort( const CPString::string& PortName, void (&Write)(uint8_t), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
        HLAPI_Dettach();
		HLAPI_Attach(Write,Initialize,SetBaudRate);

		_Name = PortName;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hardware Link API
	 
	void OutputPort::HLAPI_Attach( void (&Write)(uint8_t), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
		_Initialize = Initialize;
		_SetBaudRate = SetBaudRate;
		_Write = Write;
	}

    void OutputPort::HLAPI_Attach( void (&Write)(uint8_t) )
    {
		_Write = Write;
	}

	void OutputPort::HLAPI_Dettach()
	{
		_Write = NULL;
		_SetBaudRate = NULL;
		_Initialize = NULL;
	}

	bool OutputPort::HLAPI_Status()
	{
		// Only checks id _Available and _Read are binded, because the other functionality is optional
		if(_Write != NULL)
		{
			return 1;
		}
		return 0;
	}

	bool OutputPort::WriteAPI_Status()
	{
		if( _Write != NULL ){ return 1; }
		return 0;
	}

	bool OutputPort::InitializeAPI_Status()
	{
		if( _Initialize != NULL ){ return 1; }
		return 0;
	}

	bool OutputPort::SetBaudRateAPI_Status()
	{
		if( _SetBaudRate != NULL ){ return 1; }
		return 0;
	}

//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Low Level Hardware API

	void OutputPort::Initialize()
	{
		if(_Initialize != NULL)
		{
			_Initialize();
		}
	}

	void OutputPort::SetBaudRate(uint32_t BaudRate)
	{
		if(_SetBaudRate != NULL)
		{
			_SetBaudRate(BaudRate);
		}
	}

	void OutputPort::Write(uint8_t Data)
	{
		if(_Write != NULL)
		{
			return _Write(Data);
		}
		return 0;
	}

//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Midi Port Generic API

	const CPString::string& OutputPort::Name() const
	{
		return _Name;
	}

	void OutputPort::SetName(const CPString::string& NewName)
	{
		_Name = NewName;
	}

//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Midi Out API

	void OutputPort::NoteOn(uint8_t Note, uint8_t Velocity, uint8_t Channel)
	{
		Write(MCC_MidiCore::Protocol::ChannelVoice::NoteOn | (Channel & 0x0F) );
		Write( Note & 0b01111111 );
		Write( Velocity & 0b01111111 );
	}

    void OutputPort::NoteOff(uint8_t Note, uint8_t Velocity, uint8_t Channel)
    {
		Write(MCC_MidiCore::Protocol::ChannelVoice::NoteOff | (Channel & 0x0F) );
		Write( Note & 0b01111111 );
		Write( Velocity );
    }

    void OutputPort::ControlChange(uint8_t ControlNumber, uint8_t NewValue uint8_t Channel)
    {
		Write(MCC_MidiCore::Protocol::ChannelVoice::ControlChange | (Channel & 0x0F) );
		Write( Note & 0b01111111 );
		Write( Velocity );
    }

    void OutputPort::ChannelPressure(uint8_t Pressure, uint8_t Channel)
    {

    }

    void OutputPort::PitchBend(uint16_t BendValue, uint8_t Channel)
    {

    }

    void OutputPort::AfterTouch(uint8_t Note, uint8_t Value, uint8_t Channel)
    {

    }


    // Sysytem Common Messages
    void OutputPort::TimingTick()
    {

    }

    void OutputPort::Start()
    {

    }

    void OutputPort::Stop()
    {

    }

    void OutputPort::Continue()
    {

    }

    void OutputPort::SongPositionPointer(uint16_t Position)
    {

    }

    void OutputPort::MTC_QuarterFrame(uint8_t MessageType, uint8_t Values)
    {

    }

    void OutputPort::SongSelect(uint8_t SongID)
    {

    }

    void OutputPort::ActiveSensing()
    {

    }


    void OutputPort::SysteExclusive(uint8_t ManufacturerID , uint8_t* Data, uint8_t size)
    {

    }

    void OutputPort::SysteExclusive(uint8_t ManufacturerID , const CPVector::vector<uint8_t>& Data)
    {

    }

    void OutputPort::SysteExclusive(uint32_t ManufacturerID , uint8_t* Data, uint8_t size)
    {

    }

    void OutputPort::SysteExclusive(uint32_t ManufacturerID , const CPVector::vector<uint8_t>& Data)
    {

    }

//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers

	void OutputPort::SetSysExFlag(bool State)
	{
        _FlagRegister &= 0b11111101;
        _FlagRegister |= (State<<1u);
	}

	const bool OutputPort::SysExFlag() const
	{
        return (_FlagRegister >> 1u) & 1u;
	}

	void OutputPort::SetSOMF(bool State)
	{
        _FlagRegister &= 0b11111011;
        _FlagRegister |= (State<<2u);
	}

	const bool OutputPort::SOMF() const
	{
        return (_FlagRegister >> 2u) & 1u;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
