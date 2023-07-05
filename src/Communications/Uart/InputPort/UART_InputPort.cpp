#include "UART_InputPort.h"
#include <Core/MidiCore/MidiCore.h>

#if defined(MCC_MIDI_PORT_ENABLED)
	#include "../../MidiPort.h"
#endif 

using namespace MusicCompositionCore::Communications::Uart;
using namespace MusicCompositionCore::Communications::Midi;
using namespace MusicCompositionCore::Communications;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors

	InputPort::InputPort()
	{
		HLAPI_Dettach();

		_FlagRegister = 0;
		_FlagRegister |= PollingMode::Manual;
		_Name = "Uart MIDI In Port";

		SetBufferSize(3);
	}

	InputPort::InputPort( const CPString::string& PortName )
	{
		HLAPI_Dettach();

		_FlagRegister = 0;
		_FlagRegister |= PollingMode::Manual;
		_Name = PortName;

		SetBufferSize(3);
	}

	InputPort::InputPort( uint8_t (&Available)(void), uint8_t (&Read)(void) )
	{
        HLAPI_Dettach();
		HLAPI_Attach(Available,Read);

		_FlagRegister = 0;
		_FlagRegister |= PollingMode::Manual;
		_Name = "Uart MIDI In Port";

		SetBufferSize(3);
	}

	InputPort::InputPort( const CPString::string& PortName, uint8_t (&Available)(void), uint8_t (&Read)(void) )
	{
        HLAPI_Dettach();
		HLAPI_Attach(Available,Read);

		_FlagRegister = 0;
		_FlagRegister |= PollingMode::Manual;
		_Name = PortName;

		SetBufferSize(3);
	}

	InputPort::InputPort( uint8_t (&Available)(void), uint8_t (&Read)(void), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
        HLAPI_Dettach();
		HLAPI_Attach(Available,Read,Initialize,SetBaudRate);

		_FlagRegister = 0;
		_FlagRegister |= PollingMode::Manual;
		_Name = "Uart MIDI In Port";

		SetBufferSize(3);
	}

	InputPort::InputPort( const CPString::string& PortName, uint8_t (&Available)(void), uint8_t (&Read)(void), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
        HLAPI_Dettach();
		HLAPI_Attach(Available,Read,Initialize,SetBaudRate);

		_FlagRegister = 0;
		_FlagRegister |= PollingMode::Manual;
		_Name = PortName;

		SetBufferSize(3);
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hardware Link API
	 
	void InputPort::HLAPI_Attach( uint8_t (&Available)(void), uint8_t (&Read)(void), void (&Initialize)(void) , void (&SetBaudRate)(uint32_t) )
	{
		_Initialize = Initialize;
		_SetBaudRate = SetBaudRate;
		_Available = Available;
		_Read = Read;
	}

    void InputPort::HLAPI_Attach( uint8_t (&Available)(void), uint8_t (&Read)(void) )
    {
       _Available = Available;
       _Read = Read;
    }

	void InputPort::HLAPI_Dettach()
	{
		_Available = NULL;
		_Read = NULL;
		_SetBaudRate = NULL;
		_Initialize = NULL;
	}

	bool InputPort::HLAPI_Status()
	{
		// Only checks id _Available and _Read are binded, because the other functionality is optional
		if( (_Available != NULL) && (_Read != NULL) )
		{
			return 1;
		}
		return 0;
	}

	bool InputPort::AvailableAPI_Status()
	{
		if( _Available != NULL ){ return 1; }
		return 0;
	}

	bool InputPort::ReadAPI_Status()
	{
		if( _Read != NULL ){ return 1; }
		return 0;
	}

	bool InputPort::InitializeAPI_Status()
	{
		if( _Initialize != NULL ){ return 1; }
		return 0;
	}

	bool InputPort::SetBaudRateAPI_Status()
	{
		if( _SetBaudRate != NULL ){ return 1; }
		return 0;
	}

//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UART::Port API

	bool InputPort::EnablePort()
	{
		if(HLAPI_Status())
		{
			return Uart::BindPort( (*this) );
		}
		return 0;
	}

	void InputPort::DisablePort()
	{
		Uart::ReleasePort( (*this) );
	}

	Uart::PortID InputPort::UartPortID()
	{
		return Uart::GetSystemPortID(*this);
	}

	#if defined(MCC_MIDI_PORT_ENABLED)

		Midi::PortID InputPort::MidiPortID()
		{
			auto UartSystemPortID = GetSystemPortID(*this);
        
			if( UartSystemPortID != Uart::InvalidPortID )
			{
				return Midi::GetSystemPortID( Uart::SystemPorts[UartSystemPortID] );
			}
        
			return Midi::InvalidID;
		}

	#endif
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Low Level Hardware API

	void InputPort::Initialize()
	{
		if(_Initialize != NULL)
		{
			_Initialize();
		}
	}

	void InputPort::SetBaudRate(uint32_t BaudRate)
	{
		if(_SetBaudRate != NULL)
		{
			_SetBaudRate(BaudRate);
		}
	}

	uint8_t InputPort::BytesAvailable()
	{
		if(_Available != NULL)
		{
			return _Available();
		}
		return 0;
	}

	uint8_t InputPort::ReadByte()
	{
		if(_Read != NULL)
		{
			return _Read();
		}
		return 0;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generic Port API

	const CPString::string& InputPort::Name() const
	{
		return _Name;
	}

	void InputPort::SetName(const CPString::string& NewName)
	{
		_Name = NewName;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UART In API
    
    void InputPort::AppendCallback(void(*Callback)(CPVector::vector<uint8_t>&))
	{
		if(Callback != NULL)
		{
			_CallbackVector.push_back(Callback);
		}
	}

    void InputPort::DetachCallback(void(*Callback)(CPVector::vector<uint8_t>&))
	{
		for(uint8_t i = 0; i < _CallbackVector.size(); i++)
		{
			if(_CallbackVector[i] == Callback)
			{
				_CallbackVector.erase(i);
				return;
			}
		}
	}


	void InputPort::SetBufferSize(uint8_t size)
	{
		if(size > 3){_MessageBuffer.resize(size);}
		else{_MessageBuffer.resize(3);}
	}

	void InputPort:: Service()
	{
		while(BytesAvailable())
    	{
    		uint8_t read = ReadByte();

    		if(SysExFlag())
    		{
    			_MessageBuffer[_BufferIndex++] = read;

    			if(read == (MCC_MidiCore::Protocol::System::Exclusive::End))
    			{
    				CPVector::vector<uint8_t> MidiMessage = _MessageBuffer;
    				MidiMessage.resize(_BufferIndex);

    				for(uint8_t i = 0; i < _CallbackVector.size(); i++)
    				{
    					(*_CallbackVector[i])(_MessageBuffer);
    				}
    			}

    			if(_BufferIndex == _MessageBuffer.size())
    			{
    				_BufferIndex = 0;
	    			SetSysExFlag(0);
    				
    			}
    		}

    		else 
    		{
    			if((read >> 7)&0b1) // Start of message
	    		{
	    			if(read == (MCC_MidiCore::Protocol::System::Exclusive::Start))
	    			{
	    				SetSysExFlag(1);
	    				SetSOMF(0);
	    				_BufferIndex = 0;
	    			}
	    			else
	    			{
	    				SetSysExFlag(0);
	    				SetSOMF(1);
	    				_BufferIndex = 0;
	    			}
	    		}

	    		if(SOMF())
	    		{

	    			_MessageBuffer[_BufferIndex++] = read;

	    			switch(_MessageBuffer[0]&0xF0)
	    			{
	    				case MCC_MidiCore::Protocol::ChannelVoice::NoteOn:
	    				case MCC_MidiCore::Protocol::ChannelVoice::AfterTouch:
	    				case MCC_MidiCore::Protocol::ChannelVoice::ControlChange:
	    				case MCC_MidiCore::Protocol::ChannelVoice::ProgramChange:
	    				case MCC_MidiCore::Protocol::ChannelVoice::ChannelPressure:
	    				case MCC_MidiCore::Protocol::ChannelVoice::PitchBend:

	    					if(_BufferIndex == 3)
	    					{
	    						for(uint8_t i = 0; i < _CallbackVector.size(); i++)
	    						{
	    							(*_CallbackVector[i])(_MessageBuffer);
	    						}
	    					}

	    				break;

	    				case MCC_MidiCore::Protocol::ChannelVoice::NoteOff:

	    					if(_BufferIndex == 2)
	    					{
	    						for(uint8_t i = 0; i < _CallbackVector.size(); i++)
	    						{
	    							(*_CallbackVector[i])(_MessageBuffer);
	    						}
	    					}

	    				break;

	    				case 0xF0: 

	    					switch(_MessageBuffer[0]&0x0F)
	    					{
	    						case MCC_MidiCore::Protocol::System::Common::TuningRequest:
	    						case MCC_MidiCore::Protocol::System::RealTime::TimingTick:
	    						case MCC_MidiCore::Protocol::System::RealTime::Start:
	    						case MCC_MidiCore::Protocol::System::RealTime::Continue:
	    						case MCC_MidiCore::Protocol::System::RealTime::Stop:
	    						case MCC_MidiCore::Protocol::System::RealTime::ActiveSensing:
	    						case MCC_MidiCore::Protocol::System::RealTime::SystemReset:
								
									if(_BufferIndex == 1)
			    					{
			    						for(uint8_t i = 0; i < _CallbackVector.size(); i++)
			    						{
			    							(*_CallbackVector[i])(_MessageBuffer);
			    						}
			    					}

	    						break;


	    						case MCC_MidiCore::Protocol::System::Common::MTC_QuarterFrame:
	    						case MCC_MidiCore::Protocol::System::Common::SongSelect:

		    						if(_BufferIndex == 2)
			    					{
			    						for(uint8_t i = 0; i < _CallbackVector.size(); i++)
			    						{
			    							(*_CallbackVector[i])(_MessageBuffer);
			    						}
			    					}

	    						break;

	    						case MCC_MidiCore::Protocol::System::Common::SongPositionPointer:

		    						if(_BufferIndex == 3)
			    					{
			    						for(uint8_t i = 0; i < _CallbackVector.size(); i++)
			    						{
			    							(*_CallbackVector[i])(_MessageBuffer);
			    						}
			    					}

	    						break;
	    					}

	    				break;
	    			}
	    		}
	    	}
    	}
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helpers

	void InputPort::SetSysExFlag(bool State)
	{
        _FlagRegister &= 0b11111101;
        _FlagRegister |= (State<<1u);
	}

	const bool InputPort::SysExFlag() const
	{
        return (_FlagRegister >> 1u) & 1u;
	}

	void InputPort::SetSOMF(bool State)
	{
        _FlagRegister &= 0b11111011;
        _FlagRegister |= (State<<2u);
	}

	const bool InputPort::SOMF() const
	{
        return (_FlagRegister >> 2u) & 1u;
	}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
