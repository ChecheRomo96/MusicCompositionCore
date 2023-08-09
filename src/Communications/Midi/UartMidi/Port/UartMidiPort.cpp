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


									case MCC_MidiCore::Protocol::System::Common::MTC::QuarterFrame:
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

		void UartMidi::Port::NoteOn(uint8_t Note, uint8_t Velocity, uint8_t Channel)
		{
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.NoteOn(Note, Velocity, Channel);

			WriteMessage(MidiMessage);
		}
	
	    void UartMidi::Port::NoteOff(uint8_t Note, uint8_t Velocity, uint8_t Channel)
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.NoteOff(Note, Velocity, Channel);

			WriteMessage(MidiMessage);
	    }

	    void UartMidi::Port::AfterTouch(uint8_t Note, uint8_t Value, uint8_t Channel)
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.AfterTouch(Note, Value, Channel);

			WriteMessage(MidiMessage);
	    }

	    void UartMidi::Port::ControlChange(uint8_t ControlNumber, uint8_t Value, uint8_t Channel)
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.ControlChange(ControlNumber, Value, Channel);

			WriteMessage(MidiMessage);
	    }

		void UartMidi::Port::ProgramChange(uint8_t Program, uint8_t Channel)
		{
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.ProgramChange(Program, Channel);

			WriteMessage(MidiMessage);
		}

	    void UartMidi::Port::ChannelPressure(uint8_t Pressure, uint8_t Channel)
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.ChannelPressure(Pressure, Channel);

			WriteMessage(MidiMessage);
	    }

	    void UartMidi::Port::PitchBend(int8_t BendValue, uint8_t Channel)
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.PitchBend(BendValue, Channel);

			WriteMessage(MidiMessage);
	    }

	    void UartMidi::Port::PitchBend(int16_t BendValue, uint8_t Channel)
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.PitchBend(BendValue, Channel);

			WriteMessage(MidiMessage);
	    }

	    void UartMidi::Port::PitchBend(uint8_t BendValue, uint8_t Channel)
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.PitchBend(BendValue, Channel);

			WriteMessage(MidiMessage);
	    }

	    void UartMidi::Port::PitchBend(uint16_t BendValue, uint8_t Channel)
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.PitchBend(BendValue, Channel);

			WriteMessage(MidiMessage);
	    }

	    //////////////////////////////////////////////////////////////
	    // MCC_MidiCore::MidiNote

	        #if defined (MCC_MIDI_NOTE_ENABLED)

	            void UartMidi::Port::NoteOn(const MidiCore::MidiNote& Source)
	            {
					MCC_MidiCore::MidiMessage MidiMessage;
					MidiMessage.NoteOn(Source);

					WriteMessage(MidiMessage);
	            }

	            void UartMidi::Port::NoteOff(const MidiCore::MidiNote& Source)
	            {
					MCC_MidiCore::MidiMessage MidiMessage;
					MidiMessage.NoteOff(Source);

					WriteMessage(MidiMessage);
	            }
	        #endif
	    //
	    //////////////////////////////////////////////////////////////
	    // Mcc_MusicalNote::Note

	        #if defined (MCC_MUSICAL_NOTE_ENABLED)

	            void UartMidi::Port::NoteOn(const MCC_MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel)
	            {
					MCC_MidiCore::MidiMessage MidiMessage;
					MidiMessage.NoteOff(Source, Vel, Channel);

					WriteMessage(MidiMessage);
	            }

	            void UartMidi::Port::NoteOff(const MCC_MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel)
	            {
					MCC_MidiCore::MidiMessage MidiMessage;
					MidiMessage.NoteOff(Source, Vel, Channel);

					WriteMessage(MidiMessage);
	            }
	        #endif
	    //
	    //////////////////////////////////////////////////////////////
	    // Mcc_MusicalNote::Pitch

	        #if defined (MCC_MUSICAL_NOTE_ENABLED)

	            void UartMidi::Port::NoteOn(const MCC_MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel, uint8_t Channel)
	            {
					MCC_MidiCore::MidiMessage MidiMessage;
					MidiMessage.NoteOn(Source, Octave, Vel, Channel);

					WriteMessage(MidiMessage);
	            }

	            void UartMidi::Port::NoteOff(const MCC_MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel, uint8_t Channel)
	            {
					MCC_MidiCore::MidiMessage MidiMessage;
					MidiMessage.NoteOff(Source, Octave, Vel, Channel);

					WriteMessage(MidiMessage);
	            }
	        #endif
	    //
	    //////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////
	// Sysytem Common Messages

	    void UartMidi::Port::MTC_QuarterFrame(uint8_t MTC_ID, uint8_t Data)
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.MTC_QuarterFrame(MTC_ID, Data);

			WriteMessage(MidiMessage);
	    }

	    void UartMidi::Port::SongPositionPointer(uint16_t Position)
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.SongPositionPointer(Position);

			WriteMessage(MidiMessage);
	    }

	    void UartMidi::Port::SongSelect(uint8_t SongID)
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.SongSelect(SongID);

			WriteMessage(MidiMessage);
	    }

        void UartMidi::Port::TuningRequest()
        {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.TuningRequest();

			WriteMessage(MidiMessage);
        }
	//
	//////////////////////////////////////////////////////////////////
    // System Real Time Messages
    
	    void UartMidi::Port::TimingTick()
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.TimingTick();

			WriteMessage(MidiMessage);
	    }

	    void UartMidi::Port::Start()
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.Start();

			WriteMessage(MidiMessage);
	    }

	    void UartMidi::Port::Continue()
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.Continue();

			WriteMessage(MidiMessage);
	    }

	    void UartMidi::Port::Stop()
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.Stop();

			WriteMessage(MidiMessage);
	    }

		void UartMidi::Port::ActiveSensing()
		{
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.ActiveSensing();

			WriteMessage(MidiMessage);
		}

	    void UartMidi::Port::SystemReset()
	    {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.SystemReset();

			WriteMessage(MidiMessage);
	    }
	//
	//////////////////////////////////////////////////////////////////
    // System Exclusive Messages

        void UartMidi::Port::SystemExclusive(const CPVector::vector<uint8_t>& Data)
        {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.SystemExclusive(Data);

			WriteMessage(MidiMessage);
        }

        void UartMidi::Port::SystemExclusive(uint8_t* Data, uint8_t Length)
        {
			MCC_MidiCore::MidiMessage MidiMessage;
			MidiMessage.SystemExclusive(Data, Length);

			WriteMessage(MidiMessage);
        }

	    /*

	    void UartMidi::Port::SysteExclusive(uint8_t ManufacturerID , uint8_t* Data, uint8_t size)
	    {

	    }

	    void UartMidi::Port::SysteExclusive(uint8_t ManufacturerID , const CPVector::vector<uint8_t>& Data)
	    {

	    }

	    void UartMidi::Port::SysteExclusive(uint32_t ManufacturerID , uint8_t* Data, uint8_t size)
	    {

	    }

	    void UartMidi::Port::SysteExclusive(uint32_t ManufacturerID , const CPVector::vector<uint8_t>& Data)
	    {

	    }
	    */
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