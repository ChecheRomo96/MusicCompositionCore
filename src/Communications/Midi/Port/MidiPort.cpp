#include "MidiPort.h"

using namespace MCC::Communications;

namespace
{
    CPString::string emptyStr;
};

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
        
        emptyStr = "";
		return emptyStr;
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
				case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> Write(Data); break;
			#endif

			default:break;
		}
	}

	void Midi::Port::WriteMessage(uint8_t* Data, uint8_t Size)
	{
		switch (ParentType())
		{
			#if defined(MCC_UART_MIDI_ENABLED)
				case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> WriteMessage(Data, Size); break;
			#endif

			default:break;
		}
	}

	void Midi::Port::WriteMessage(const CPVector::vector<uint8_t>& Data)
	{
		switch (ParentType())
		{
			#if defined(MCC_UART_MIDI_ENABLED)
				case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> WriteMessage(Data); break;
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
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> WriteMessage(Data); break;
				#endif

				default:break;
			}
		}
	#endif


    //////////////////////////////////////////////////////////////////
    // Channel Voice Messages

		void Midi::Port::NoteOn(uint8_t Note, uint8_t Velocity, uint8_t Channel)
		{
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> NoteOn( Note,  Velocity,  Channel); break;
				#endif

				default:break;
			}
			
		}
		
	    void Midi::Port::NoteOff(uint8_t Note, uint8_t Velocity, uint8_t Channel)
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> NoteOff( Note,  Velocity,  Channel); break;
				#endif

				default:break;
			}
	    }

	    void Midi::Port::AfterTouch(uint8_t Note, uint8_t Value, uint8_t Channel)
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> AfterTouch( Note,  Value,  Channel); break;
				#endif

				default:break;
			}
	    }

	    void Midi::Port::ControlChange(uint8_t ControlNumber, uint8_t Value, uint8_t Channel)
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> ControlChange( ControlNumber,  Value,  Channel); break;
				#endif

				default:break;
			}
	    }

	    void Midi::Port::ChannelPressure(uint8_t Pressure, uint8_t Channel)
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> ChannelPressure( Pressure,  Channel); break;
				#endif

				default:break;
			}
	    }

	    void Midi::Port::PitchBend(uint8_t BendValue, uint8_t Channel)
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> PitchBend( BendValue,  Channel); break;
				#endif

				default:break;
			}
	    }

	    void Midi::Port::PitchBend(int8_t BendValue, uint8_t Channel)
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> PitchBend( BendValue,  Channel); break;
				#endif

				default:break;
			}
	    }

	    void Midi::Port::PitchBend(uint16_t BendValue, uint8_t Channel)
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> PitchBend( BendValue,  Channel); break;
				#endif

				default:break;
			}
	    }

	    void Midi::Port::PitchBend(int16_t BendValue, uint8_t Channel)
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> PitchBend( BendValue,  Channel); break;
				#endif

				default:break;
			}
	    }

	    //////////////////////////////////////////////////////////////
	    // MCC_MidiCore::MidiNote

	        #if defined (MCC_MIDI_NOTE_ENABLED)

	            void Midi::Port::NoteOn(const MidiCore::MidiNote& Source)
	            {
					switch (ParentType())
					{
						#if defined(MCC_UART_MIDI_ENABLED)
							case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> NoteOn( Source); break;
						#endif

						default:break;
					}
	            }

	            void Midi::Port::NoteOff(const MidiCore::MidiNote& Source)
	            {
					switch (ParentType())
					{
						#if defined(MCC_UART_MIDI_ENABLED)
							case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> NoteOff( Source); break;
						#endif

						default:break;
					}
	            }
	        #endif
	    //
	    //////////////////////////////////////////////////////////////
	    // Mcc_MusicalNote::Note

	        #if defined (MCC_MUSICAL_NOTE_ENABLED)

	            void Midi::Port::NoteOn(const MCC_MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel)
	            {
					switch (ParentType())
					{
						#if defined(MCC_UART_MIDI_ENABLED)
							case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> NoteOn( Source, Vel, Channel); break;
						#endif

						default:break;
					}
	            }

	            void Midi::Port::NoteOff(const MCC_MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel)
	            {
					switch (ParentType())
					{
						#if defined(MCC_UART_MIDI_ENABLED)
							case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> NoteOff( Source, Vel, Channel); break;
						#endif

						default:break;
					}
	            }
	        #endif
	    //
	    //////////////////////////////////////////////////////////////
	    // Mcc_MusicalNote::Pitch

	        #if defined (MCC_MUSICAL_NOTE_ENABLED)

	            void Midi::Port::NoteOn(const MCC_MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel, uint8_t Channel)
	            {
					switch (ParentType())
					{
						#if defined(MCC_UART_MIDI_ENABLED)
							case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> NoteOn( Source, Octave, Vel, Channel); break;
						#endif

						default:break;
					}
	            }

	            void Midi::Port::NoteOff(const MCC_MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel, uint8_t Channel)
	            {
					switch (ParentType())
					{
						#if defined(MCC_UART_MIDI_ENABLED)
							case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> NoteOff( Source, Octave, Vel, Channel); break;
						#endif

						default:break;
					}
	            }
	        #endif
	    //
	    //////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////
	// Sysytem Common Messages

	    void Midi::Port::MTC_QuarterFrame(uint8_t MTC_ID, uint8_t Data)
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> MTC_QuarterFrame( MTC_ID, Data); break;
				#endif

				default:break;
			}
	    }

	    void Midi::Port::SongPositionPointer(uint16_t Position)
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> SongPositionPointer( Position); break;
				#endif

				default:break;
			}
	    }

	    void Midi::Port::SongSelect(uint8_t SongID)
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> SongSelect( SongID); break;
				#endif

				default:break;
			}
	    }

        void Midi::Port::TuningRequest()
        {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> TuningRequest(); break;
				#endif

				default:break;
			}
        }
    //
    //////////////////////////////////////////////////////////////////
    // System Real Time Messages
    
	    void Midi::Port::TimingTick()
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> TimingTick(); break;
				#endif

				default:break;
			}
	    }

	    void Midi::Port::Start()
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> Start(); break;
				#endif

				default:break;
			}
	    }

	    void Midi::Port::Continue()
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> Continue(); break;
				#endif

				default:break;
			}
	    }

	    void Midi::Port::Stop()
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> Stop(); break;
				#endif

				default:break;
			}
	    }

		void Midi::Port::ActiveSensing()
		{
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> ActiveSensing(); break;
				#endif

				default:break;
			}
		}

	    void Midi::Port::SystemReset()
	    {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> SystemReset(); break;
				#endif

				default:break;
			}
	    }
	//
	//////////////////////////////////////////////////////////////////
	// Sysytem Exclusive Messages

        void Midi::Port::SystemExclusive(const CPVector::vector<uint8_t>& Data)
        {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> SystemExclusive(Data); break;
				#endif

				default:break;
			}
        }

        void Midi::Port::SystemExclusive(uint8_t* Data, uint8_t Length)
        {
			switch (ParentType())
			{
				#if defined(MCC_UART_MIDI_ENABLED)
					case PortTypes::UartMidi: ((UartMidi::Port*)_PortPointer) -> SystemExclusive(Data, Length); break;
				#endif

				default:break;
			}
        }

	    /*
	    void Midi::Port::SystemExclusive(uint8_t ManufacturerID , uint8_t* Data, uint8_t size)
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

	    }*/
	//
    //////////////////////////////////////////////////////////////////
//						
///////////////////////////////////////////////////////////////////////
