#include "UartMidiPort.h"
#include <Core/MidiCore/MidiCore.h>

using namespace MCC::Communications;
using namespace MCC::Communications::Midi;

///////////////////////////////////////////////////////////////////////
// Constructors

	UartMidi::Port::Port()
	{
		UnlinkFromPort();
		_FlagRegister = 0;
		_MessageBuffer.resize(3);
	}


	#if defined(MCC_UART_PORT_ENABLED)
		UartMidi::Port::Port(const Uart::Port& Parent)
		{
			UnlinkFromPort();
			LinkToPort(Parent);
			_FlagRegister = 0;
			_MessageBuffer.resize(3);
		}
	#endif

	//UartMidiPort(const UartMidi::OutputPort& Parent);
	//UartMidiPort(const UartMidi::DuplexPort& Parent);
//
///////////////////////////////////////////////////////////////////////
// High Level API

	void UartMidi::Port::LinkToPort(const Uart::Port& Parent)
	{
	    _PortPointer = (Uart::Port*)&Parent;
	    Midi::SystemPorts.BindPort(*this);
	}

	void UartMidi::Port::UnlinkFromPort()
	{
	    _PortPointer = NULL;
	    Midi::SystemPorts.UnbindPort(*this);
	}
	
	const Uart::PortType& UartMidi::Port::ParentType() const
	{
		if(_PortPointer == NULL){ return Uart::PortTypes::InvalidType; }

		return _PortPointer->ParentType();
	}

	const Uart::Port* UartMidi::Port::Uart_PortPointer() const
	{
	    return _PortPointer;
	}
//
///////////////////////////////////////////////////////////////////////
// Midi Port Generic API

	const CPString::string& UartMidi::Port::Name() const
	{
		if(_PortPointer != NULL)
		{
			return _PortPointer->Name();
		}

		return CPString::string("");
	}

	void UartMidi::Port::SetName(const CPString::string& NewName)
	{
		if(_PortPointer != NULL)
		{
			return _PortPointer->SetName(NewName);
		}
	}
//
///////////////////////////////////////////////////////////////////////
// Midi In API

	void UartMidi::Port::AppendCallback(void(*Callback)(const CPVector::vector<uint8_t>&))
	{
		if(Callback != NULL)
		{
			bool flag = 1;

			for(uint8_t i = 0; i < _CallbackVector.size(); i++)
			{
				if(_CallbackVector[i] == Callback){flag=0;}
			}

			if(flag){ _CallbackVector.push_back(Callback); }
		}
	}

	void UartMidi::Port::DetachCallback(void(*Callback)(const CPVector::vector<uint8_t>&))
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

	void UartMidi::Port::SetBufferSize(uint8_t size)
	{
		if(size > 0){_MessageBuffer.resize(size);}
		else{_MessageBuffer.resize(3);}
	}

	void UartMidi::Port::Service()
	{
		if (_PortPointer != NULL)
		{
			while(_PortPointer -> BytesAvailable())
			{
				uint8_t read = _PortPointer -> ReadByte();

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
						//Buffer Overflow Protection
						if (_MessageBuffer.size() <= _BufferIndex)
						{
							SetSOMF(0);
							_BufferIndex = 0;
						}

		    			_MessageBuffer[_BufferIndex++] = read;

		    			switch(_MessageBuffer[0]&0xF0)
		    			{
		    				case MCC_MidiCore::Protocol::ChannelVoice::NoteOn:
							case MCC_MidiCore::Protocol::ChannelVoice::NoteOff:
		    				case MCC_MidiCore::Protocol::ChannelVoice::AfterTouch:
		    				case MCC_MidiCore::Protocol::ChannelVoice::ControlChange:
		    				case MCC_MidiCore::Protocol::ChannelVoice::ProgramChange:
		    				case MCC_MidiCore::Protocol::ChannelVoice::ChannelPressure:
		    				case MCC_MidiCore::Protocol::ChannelVoice::PitchBend:

		    					if(_BufferIndex == 3){ InvokeCallbacks(); }

		    				break;

		    				case 0xF0: 

		    					switch(_MessageBuffer[0])
		    					{
		    						case MCC_MidiCore::Protocol::System::Common::TuningRequest:
		    						case MCC_MidiCore::Protocol::System::RealTime::TimingTick:
		    						case MCC_MidiCore::Protocol::System::RealTime::Start:
		    						case MCC_MidiCore::Protocol::System::RealTime::Continue:
		    						case MCC_MidiCore::Protocol::System::RealTime::Stop:
		    						case MCC_MidiCore::Protocol::System::RealTime::ActiveSensing:
		    						case MCC_MidiCore::Protocol::System::RealTime::SystemReset:
									
										if(_BufferIndex == 1){ InvokeCallbacks(); }

		    						break;


		    						case MCC_MidiCore::Protocol::System::Common::MTC_QuarterFrame:
		    						case MCC_MidiCore::Protocol::System::Common::SongSelect:

			    						if(_BufferIndex == 2){ InvokeCallbacks(); }

		    						break;

		    						case MCC_MidiCore::Protocol::System::Common::SongPositionPointer:

			    						if(_BufferIndex == 3){ InvokeCallbacks(); }

		    						break;
		    					}

		    				break;
		    			}

						//Buffer Overflow Protection
						if (_MessageBuffer.size() == _BufferIndex)
						{
							
							SetSOMF(0);
							_BufferIndex = 0;
						}
		    		}

	    		}
			}
		}
	}
//
///////////////////////////////////////////////////////////////////////
// Midi Out API

	void UartMidi::Port::Write(uint8_t Data)
	{
		if(_PortPointer != NULL)
		{
			_PortPointer -> Write(Data);
 		}
	}

	void UartMidi::Port::WriteMessage(uint8_t* Data, uint8_t Len)
	{
		if (_PortPointer != NULL)
		{
			_PortPointer->WriteBuffer(Data,Len);
		}
	}

	void UartMidi::Port::WriteMessage(const CPVector::vector<uint8_t>& Message)
	{
		if (_PortPointer != NULL)
		{
			_PortPointer->WriteBuffer(Message);
		}
	}

	#if defined (MCC_MIDI_MESSAGE_ENABLED)
		void UartMidi::Port::WriteMessage(const MCC_MidiCore::MidiMessage& Message)
		{
			if (_PortPointer != NULL)
			{
				_PortPointer->WriteBuffer(Message.Buffer());
			}
		}
	#endif

    //////////////////////////////////////////////////////////////////
    // Channel Voice Messages

		void Midi::Port::NoteOn(uint8_t Note, uint8_t Velocity, uint8_t Channel)
		{
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.NoteOn(Note, Velocity, Channel);

			WriteMessage(MidiMessage);
		}
	
	    void Midi::Port::NoteOff(uint8_t Note, uint8_t Velocity, uint8_t Channel)
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.NoteOff(Note, Velocity, Channel);

			WriteMessage(MidiMessage);
	    }

	    void Midi::Port::ControlChange(uint8_t ControlNumber, uint8_t NewValue, uint8_t Channel)
	    {
			Write( MCC_MidiCore::Protocol::ChannelVoice::ControlChange | (Channel & 0x0F) );
			Write( ControlNumber & 0b01111111 );
			Write(NewValue);
	    }

	    void Midi::Port::ChannelPressure(uint8_t Pressure, uint8_t Channel)
	    {
			Write(MCC_MidiCore::Protocol::ChannelVoice::ChannelPressure | (Channel & 0x0F) );
			Write( Pressure );
	    }

	    void Midi::Port::PitchBend(uint8_t BendValue, uint8_t Channel)
	    {
			Write(MCC_MidiCore::Protocol::ChannelVoice::PitchBend | (Channel & 0x0F) );
			Write( 0 );
			Write( BendValue & 0b01111111 );
	    }

	    void Midi::Port::PitchBend(int8_t BendValue, uint8_t Channel)
	    {
	    	if(BendValue >= 0x40){BendValue = 0x3F;}
	    	if(BendValue < -0x40){BendValue = 0x40;}

	    	BendValue = 0x40 + BendValue;

			Write(MCC_MidiCore::Protocol::ChannelVoice::PitchBend | (Channel & 0x0F) );
			Write( 0 );
			Write( BendValue & 0b01111111 );
	    }

	    void Midi::Port::PitchBend(uint16_t BendValue, uint8_t Channel)
	    {
			Write(MCC_MidiCore::Protocol::ChannelVoice::PitchBend | (Channel & 0x0F) );
			Write( BendValue & 0b01111111 );
			Write( ((BendValue)>>7) & 0b01111111 );
	    }

	    void Midi::Port::PitchBend(int16_t BendValue, uint8_t Channel)
	    {
	    	if(BendValue >= 0x2000){BendValue = 0x1FFF;}
	    	if(BendValue < -0x2000){BendValue = -0x2000;}

	    	BendValue = 0x2000 + BendValue;

			Write(MCC_MidiCore::Protocol::ChannelVoice::PitchBend | (Channel & 0x0F) );
			Write( BendValue & 0b01111111 );
			Write( ((BendValue)>>7) & 0b01111111 );
	    }

	    void Midi::Port::AfterTouch(uint8_t Note, uint8_t Value, uint8_t Channel)
	    {
			Write(MCC_MidiCore::Protocol::ChannelVoice::AfterTouch | (Channel & 0x0F) );
			Write( Note & 0b01111111 );
			Write( Value );
	    }
    //
    //////////////////////////////////////////////////////////////////
    // Sysytem Common Messages
    
	    void Midi::Port::TimingTick()
	    {
			Write(MCC_MidiCore::Protocol::System::RealTime::TimingTick);
	    }

	    void Midi::Port::Start()
	    {
			Write(MCC_MidiCore::Protocol::System::RealTime::Start);
	    }

	    void Midi::Port::Stop()
	    {
			Write(MCC_MidiCore::Protocol::System::RealTime::Stop);
	    }

	    void Midi::Port::Continue()
	    {
			Write(MCC_MidiCore::Protocol::System::RealTime::Continue);
	    }

		void Midi::Port::ActiveSensing()
		{
			Write(MCC_MidiCore::Protocol::System::RealTime::ActiveSensing);
		}
	//
	//////////////////////////////////////////////////////////////////
	// Sysytem Common Messages

	    void Midi::Port::SongPositionPointer(uint16_t Position)
	    {
			Write(MCC_MidiCore::Protocol::System::Common::SongPositionPointer);
			Write( Position & 0b01111111 );
			Write( ((Position)>>7) & 0b01111111 );
	    }

	    void Midi::Port::MTC_QuarterFrame(uint8_t MessageType, uint8_t Values)
	    {
			Write(MCC_MidiCore::Protocol::System::Common::MTC_QuarterFrame);
			Write( ((MessageType & 0b111)<<4) | (Values & 0x0F) );
	    }

	    void Midi::Port::SongSelect(uint8_t SongID)
	    {
			Write(MCC_MidiCore::Protocol::System::Common::SongSelect);
			Write( SongID & 0b01111111 );
	    }

	    void Midi::Port::SysteExclusive(uint8_t ManufacturerID , uint8_t* Data, uint8_t size)
	    {

	    }

	    void Midi::Port::SysteExclusive(uint8_t ManufacturerID , const CPVector::vector<uint8_t>& Data)
	    {

	    }

	    void Midi::Port::SysteExclusive(uint32_t ManufacturerID , uint8_t* Data, uint8_t size)
	    {

	    }

	    void Midi::Port::SysteExclusive(uint32_t ManufacturerID , const CPVector::vector<uint8_t>& Data)
	    {

	    }
	//
    //////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////
// Midi Port API

	bool UartMidi::Port::Midi_BindPort() const
	{
		return Midi::SystemPorts.BindPort(*this);
	}

	void UartMidi::Port::Midi_UnbindPort() const
	{
		Midi::SystemPorts.UnbindPort(*this);
	}

	Midi::SystemPortHandler::PortID UartMidi::Port::Midi_PortID() const
	{
		return Midi::SystemPorts.GetID(*this);
	}

	Midi::Port& UartMidi::Port::Midi_Port() const
	{
		return Midi::SystemPorts.GetPort(*this);
	}
//
///////////////////////////////////////////////////////////////////////
// Helpers

	void UartMidi::Port::InvokeCallbacks()
	{
		for(uint8_t i = 0; i < _CallbackVector.size(); i++)
		{
			(*_CallbackVector[i])(_MessageBuffer);
		}

		SetSOMF(0);
		_BufferIndex = 0;
	}

	void UartMidi::Port::SetSysExFlag(bool State)
	{
        _FlagRegister &= 0b11111101;
        _FlagRegister |= (State<<1u);
	}

	const bool UartMidi::Port::SysExFlag() const
	{
        return (_FlagRegister >> 1u) & 1u;
	}

	void UartMidi::Port::SetSOMF(bool State)
	{
        _FlagRegister &= 0b11111011;
        _FlagRegister |= (State<<2u);
	}

	const bool UartMidi::Port::SOMF() const
	{
        return (_FlagRegister >> 2u) & 1u;
	}
//
///////////////////////////////////////////////////////////////////////