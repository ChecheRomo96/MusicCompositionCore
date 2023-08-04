#include "MidiPort.h"

using namespace MCC::Communications;

///////////////////////////////////////////////////////////////////////
// Constructors

	Midi::Port::Port()
	{
		UnlinkFromPort();
	}

	#if defined (MCC_UART_MIDI_ENABLED)
		Midi::Port::Port(const UartMidi::Port& Parent)
		{
			UnlinkFromPort();
			LinkToPort(Parent);
		}
	#endif
//
///////////////////////////////////////////////////////////////////////
// High Level API

	#if defined (MCC_UART_MIDI_ENABLED)
		void Midi::Port::LinkToPort(const UartMidi::Port& Parent)
		{
		    _PortPointer = (void*) &Parent;
		    _PortType = PortTypes::UartMidi;
		}
	#endif

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
			#if defined(MCC_UART_MIDI_ENABLED) & defined(MCC_UART_IN_ENABLED)
				case PortTypes::UartMidi: return ((UartMidi::Port*) _PortPointer) -> Name();
			#endif		

			default: break;
		}

		return CPString::string("");
	}

	void Midi::Port::SetName(const CPString::string& NewName)
	{
		switch(_PortType)
		{
			#if defined(MCC_UART_MIDI_ENABLED) & defined(MCC_UART_IN_ENABLED)
				case PortTypes::UartMidi: ((UartMidi::Port*) _PortPointer) -> SetName(NewName);  break;
			#endif

			default: break;
		} 
	}
//
///////////////////////////////////////////////////////////////////////
// Midi In API

    void Midi::Port::AppendCallback(void(*Callback)(const CPVector::vector<uint8_t>&))
    {
		switch(_PortType)
		{
			#if defined(MCC_UART_MIDI_ENABLED) & defined(MCC_UART_IN_ENABLED)
				case PortTypes::UartMidi: ((UartMidi::Port*) _PortPointer) -> AppendCallback(Callback);  break;
			#endif	

			default: break;
		}
    }

    void Midi::Port::DetachCallback(void(*Callback)(const CPVector::vector<uint8_t>&))
    {
		switch(_PortType)
		{
			#if defined(MCC_UART_MIDI_ENABLED) & defined(MCC_UART_IN_ENABLED)
				case PortTypes::UartMidi: ((UartMidi::Port*) _PortPointer) -> DetachCallback(Callback);  break;
			#endif	

			default: break;
		}
    }


    void Midi::Port::SetBufferSize(uint8_t size)
    {
		switch(_PortType)
		{
			#if defined(MCC_UART_MIDI_ENABLED) & defined(MCC_UART_IN_ENABLED)
				case PortTypes::UartMidi: ((UartMidi::Port*) _PortPointer) -> SetBufferSize(size);  break;
			#endif	

			default: break;
		}
    }


	void Midi::Port::Service()
	{
		switch(_PortType)
		{
			#if defined(MCC_UART_MIDI_ENABLED) & defined(MCC_UART_IN_ENABLED)
				case PortTypes::UartMidi: ((UartMidi::Port*) _PortPointer) -> Service();  break;
			#endif	

			default: break;
		}
	}
//
///////////////////////////////////////////////////////////////////////
// Midi Out API

	void Midi::Port::Write(uint8_t Data)
	{
		switch (ParentType())
		{
			#if defined(MCC_UART_MIDI_ENABLED)
				case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> Write(Data);
			#endif

			default:break;
		}
	}

	void Midi::Port::WriteMessage(uint8_t* Data, uint8_t Size)
	{
		switch (ParentType())
		{
			#if defined(MCC_UART_MIDI_ENABLED)
				case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> WriteMessage(Data, Size);
			#endif

			default:break;
		}
	}

	void Midi::Port::WriteMessage(const CPVector::vector<uint8_t>& Data)
	{
		switch (ParentType())
		{
			#if defined(MCC_UART_MIDI_ENABLED)
				case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> WriteMessage(Data);
			#endif

			default:break;
		}
	}

	#if defined (MCC_MIDI_MESSAGE_ENABLED)
		void Midi::Port::WriteMessage(const MCC_MidiCore::MidiMessage& Data)
		{
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> WriteMessage(Data);
				#endif

				default:break;
			}
		}
	#endif

/*
    //////////////////////////////////////////////////////////////////
    // Channel Voice Messages

		void Midi::Port::NoteOn(uint8_t Note, uint8_t Velocity, uint8_t Channel)
		{

			CPVector::vector<uint8_t> Message;

			if(Message.resize(3))
			{
				Message[0] = (MCC_MidiCore::Protocol::ChannelVoice::NoteOn | (Channel & 0x0F));
				Message[1] = (Note & 0b01111111);
				Message[2] = (Velocity & 0b01111111);
			} else{ return; }

			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> WriteMessage(Message);
				#endif

				default:break;
			}
			
		}
	
	    void Midi::Port::NoteOff(uint8_t Note, uint8_t Velocity, uint8_t Channel)
	    {
			Write(MCC_MidiCore::Protocol::ChannelVoice::NoteOff | (Channel & 0x0F) );
			Write( Note & 0b01111111 );
			Write( Velocity );
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

*/

//						
///////////////////////////////////////////////////////////////////////
// Helpers


//						
///////////////////////////////////////////////////////////////////////
