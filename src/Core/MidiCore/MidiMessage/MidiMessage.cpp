#include "MidiMessage.h"
#include "../MidiDefinitions.h"
#include "../../MusicalCore/MusicalCore.h"

#include <CPvector.h>
using namespace MusicCompositionCore::Core::MidiCore;

//////////////////////////////////////////////////////////////////
// Constructor and Assignment operator

	MidiMessage::MidiMessage()
	{

	}

	MidiMessage& MidiMessage::operator=(const MidiMessage& Source)
	{
		_Buffer.resize(Source.Buffer().size());

		for(uint8_t i = 0; i < _Buffer.size(); i++)
		{
			_Buffer[i] = Source.Buffer()[i];
		}

		return *this;
	}
//
//////////////////////////////////////////////////////////////////
// Buffer API

	const cpstd::vector<uint8_t>& MidiMessage::Buffer() const
	{
		return _Buffer;
	}
//
//////////////////////////////////////////////////////////////////
// Channel Voice Messages

	MidiMessage& MidiMessage::NoteOn(uint8_t Pitch, uint8_t Vel, uint8_t Channel)
	{
		_Buffer.resize(3);

		_Buffer[0] = MCC_MidiProtocol::ChannelVoice::NoteOn | (Channel&0x0F);
		_Buffer[1] = Pitch & 0x7F;
		_Buffer[2] = Vel & 0x7F;

		return *this;
	}

	MidiMessage& MidiMessage::NoteOff(uint8_t Pitch, uint8_t Vel, uint8_t Channel)
	{
		_Buffer.resize(3);

		_Buffer[0] = MCC_MidiProtocol::ChannelVoice::NoteOff | (Channel&0x0F);
		_Buffer[1] = Pitch & 0x7F;
		_Buffer[2] = Vel & 0x7F;
		
		return *this;
	}

	MidiMessage& MidiMessage::AfterTouch(uint8_t Note, uint8_t Pressure, uint8_t Channel)
	{
		_Buffer.resize(3);

		_Buffer[0] = MCC_MidiProtocol::ChannelVoice::AfterTouch | (Channel&0x0F);
		_Buffer[1] = Note & 0x7F;
		_Buffer[2] = Pressure & 0x7F;

		return *this;
	}

	MidiMessage& MidiMessage::ControlChange(uint8_t ControllerNumber, uint8_t Value, uint8_t Channel)
	{
		_Buffer.resize(3);

		_Buffer[0] = MCC_MidiProtocol::ChannelVoice::ControlChange | (Channel&0x0F);
		_Buffer[1] = ControllerNumber & 0x7F;
		_Buffer[2] = Value & 0x7F;

		return *this;
	}

	MidiMessage& MidiMessage::ProgramChange(uint8_t Program, uint8_t Channel)
	{
		_Buffer.resize(2);

		_Buffer[0] = MCC_MidiProtocol::ChannelVoice::ProgramChange | (Channel&0x0F);
		_Buffer[1] = Program & 0x7F;
		
		return *this;
	}

	MidiMessage& MidiMessage::ChannelPressure(uint8_t Pressure, uint8_t Channel)
	{
		_Buffer.resize(2);

		_Buffer[0] = MCC_MidiProtocol::ChannelVoice::ChannelPressure | (Channel&0x0F);
		_Buffer[1] = Pressure & 0x7F;

		return *this;
	}

	MidiMessage& MidiMessage::PitchBend(int8_t Value, uint8_t Channel)
	{
		_Buffer.resize(3);

		if(Value >= 0x40){Value = 0x3F;}
		if(Value < -0x40){Value = 0x40;}
		Value = 0x40 + Value;

		_Buffer[0] = MCC_MidiProtocol::ChannelVoice::PitchBend | (Channel&0x0F);
		_Buffer[1] = 0;
		_Buffer[2] = Value & 0b01111111;
		
		return *this;
	}

	MidiMessage& MidiMessage::PitchBend(int16_t Value, uint8_t Channel)
	{
		_Buffer.resize(3);
		if(Value >= 0x2000){Value = 0x1FFF;}
		if(Value < -0x2000){Value = -0x2000;}
		Value = 0x2000 + Value;

		_Buffer[0] = MCC_MidiProtocol::ChannelVoice::PitchBend | (Channel&0x0F);
		_Buffer[1] = Value & 0b01111111;
		_Buffer[2] = ((Value)>>7) & 0b01111111;
		
		return *this;
	}

	MidiMessage& MidiMessage::PitchBend(uint8_t Value, uint8_t Channel)
	{
		_Buffer.resize(3);

		_Buffer[0] = MCC_MidiProtocol::ChannelVoice::PitchBend | (Channel&0x0F);
		_Buffer[1] = 0;
		_Buffer[2] = Value & 0b01111111;
		
		return *this;
	}

	MidiMessage& MidiMessage::PitchBend(uint16_t Value, uint8_t Channel)
	{
		_Buffer.resize(3);

		_Buffer[0] = MCC_MidiProtocol::ChannelVoice::PitchBend | (Channel&0x0F);
		_Buffer[1] = Value & 0b01111111;
		_Buffer[2] = ((Value)>>7) & 0b01111111 ;
		
		return *this;
	}

	//////////////////////////////////////////////////////////////
	// MCC_MidiCore::MidiNote

		#if defined (MCC_MIDI_NOTE_ENABLED)

			MidiMessage& MidiMessage::NoteOn(const MidiCore::MidiNote& Source)
			{
				_Buffer.resize(3);

				_Buffer[0] = MCC_MidiProtocol::ChannelVoice::NoteOn | (Source.Channel()&0x0F);
				_Buffer[1] = Source.Pitch();
				_Buffer[2] = Source.OnVelocity();
				
				return *this;
			}

			MidiMessage& MidiMessage::NoteOff(const MidiCore::MidiNote& Source)
			{
				_Buffer.resize(3);

				_Buffer[0] = MCC_MidiProtocol::ChannelVoice::NoteOff | (Source.Channel()&0x0F);
				_Buffer[1] = Source.Pitch();
				_Buffer[2] = Source.OffVelocity();
				
				return *this;
			}
		#endif
	//
	//////////////////////////////////////////////////////////////
	// Mcc_MusicalNote::Note

		#if defined (MCC_MUSICAL_NOTE_ENABLED)

			MidiMessage& MidiMessage::NoteOn(const MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel)
			{
				_Buffer.resize(3);

				_Buffer[0] = MCC_MidiProtocol::ChannelVoice::NoteOn | (Channel&0x0F);
				_Buffer[1] = Source.MidiPitch();
				_Buffer[2] = Vel & 0x7F;
				
				return *this;
			}

			MidiMessage& MidiMessage::NoteOff(const MusicalCore::MusicalNote::Note& Source, uint8_t Vel,  uint8_t Channel)
			{
				_Buffer.resize(3);

				_Buffer[0] = MCC_MidiProtocol::ChannelVoice::NoteOff | (Channel&0x0F);
				_Buffer[1] = Source.MidiPitch();
				_Buffer[2] = Vel & 0x7F;
				
				return *this;
			}
		#endif
	//
	//////////////////////////////////////////////////////////////
	// Mcc_MusicalNote::Pitch

		#if defined (MCC_MUSICAL_NOTE_ENABLED)

			MidiMessage& MidiMessage::NoteOn(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel, uint8_t Channel)
			{
				_Buffer.resize(3);
				MCC_MusicalNote::Note tmpNote(Source,Octave);

				_Buffer[0] = MCC_MidiProtocol::ChannelVoice::NoteOn | (Channel&0x0F);
				_Buffer[1] = tmpNote.MidiPitch();
				_Buffer[2] = Vel & 0x7F;
				
				return *this;
			}

			MidiMessage& MidiMessage::NoteOff(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel, uint8_t Channel)
			{
				_Buffer.resize(3);
				MCC_MusicalNote::Note tmpNote(Source,Octave);

				_Buffer[0] = MCC_MidiProtocol::ChannelVoice::NoteOff | (Channel&0x0F);
				_Buffer[1] = tmpNote.MidiPitch();
				_Buffer[2] = Vel & 0x7F;
				
				return *this;
			}
		#endif
	//
	//////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////
// System Common Messages

	MidiMessage& MidiMessage::MTC_QuarterFrame(uint8_t MTC_ID, uint8_t Data)
	{
		_Buffer.resize(2);

		_Buffer[0] = MCC_MidiProtocol::System::Common::MTC::QuarterFrame;
		_Buffer[1] = ((MTC_ID &0b111)<<4) | (Data & 0x0F);

		return *this;
	}

	MidiMessage& MidiMessage::SongPositionPointer(uint16_t Position)
	{
		_Buffer.resize(3);

		_Buffer[0] = MCC_MidiProtocol::System::Common::SongPositionPointer;
		_Buffer[1] = Position&0xFF;
		_Buffer[2] = (Position>>8)&0xFF;

		return *this;
	}

	MidiMessage& MidiMessage::SongSelect(uint8_t Song)
	{
		_Buffer.resize(3);

		_Buffer[0] = MCC_MidiProtocol::System::Common::SongSelect;
		_Buffer[1] = Song & 0x7F;

		return *this;
	}

    MidiMessage& MidiMessage::TuningRequest()
    {
		_Buffer.resize(1);

		_Buffer[0] = MCC_MidiProtocol::System::Common::TuningRequest;
		return *this;
    }
//
//////////////////////////////////////////////////////////////////
// System Real Time Messages

	MidiMessage& MidiMessage::TimingTick()
	{
		_Buffer.resize(1);

		_Buffer[0] = MCC_MidiProtocol::System::RealTime::TimingTick;

		return *this;
	}

	MidiMessage& MidiMessage::Start()
	{
		_Buffer.resize(1);

		_Buffer[0] = MCC_MidiProtocol::System::RealTime::Start;

		return *this;
	}

	MidiMessage& MidiMessage::Continue()
	{
		_Buffer.resize(1);

		_Buffer[0] = MCC_MidiProtocol::System::RealTime::Continue;

		return *this;
	}

	MidiMessage& MidiMessage::Stop()
	{
		_Buffer.resize(1);

		_Buffer[0] = MCC_MidiProtocol::System::RealTime::Stop;

		return *this;
	}

    MidiMessage& MidiMessage::ActiveSensing()
    {
		_Buffer.resize(1);

		_Buffer[0] = MCC_MidiProtocol::System::RealTime::ActiveSensing;

		return *this;
    }

    MidiMessage& MidiMessage::SystemReset()
    {
		_Buffer.resize(1);

		_Buffer[0] = MCC_MidiProtocol::System::RealTime::SystemReset;
		
		return *this;
    }
//
//////////////////////////////////////////////////////////////////
// System Exclusive Messages

	MidiMessage& MidiMessage::SystemExclusive(const cpstd::vector<uint8_t>& Data)
	{
		uint8_t counter = 0;
		bool flag1 = 0;
		bool flag2 = 0;

		if(Data[0] != (MCC_MidiProtocol::System::Exclusive::Start))
		{
			counter++;
			flag1 = 1;
		}
		if(Data[Data.size() - 1] != (MCC_MidiProtocol::System::Exclusive::End))
		{
			counter++;
			flag2 = 1;
		}

		_Buffer.resize(Data.size() + counter);

		if(flag1){ _Buffer[0] = MCC_MidiProtocol::System::Exclusive::Start; }
		if(flag2){ _Buffer[_Buffer.size() - 1] = MCC_MidiProtocol::System::Exclusive::End; }
		
		for(uint8_t i = flag1; i < _Buffer.size() - flag2; i++)
		{
			_Buffer[i] = Data[i-flag1];
		}

		return *this;
	}

	MidiMessage& MidiMessage::SystemExclusive(uint8_t* Data, uint8_t Length)
	{
		uint8_t counter = 0;
		bool flag1 = 0;
		bool flag2 = 0;

		if(Data[0] != (MCC_MidiProtocol::System::Exclusive::Start))
		{
			counter++;
			flag1 = 1;
		}
		if(Data[Length - 1] != (MCC_MidiProtocol::System::Exclusive::End))
		{
			counter++;
			flag2 = 1;
		}

		_Buffer.resize(Length + counter);

		if(flag1){ _Buffer[0] = MCC_MidiProtocol::System::Exclusive::Start; }
		if(flag2){ _Buffer[_Buffer.size() - 1] = MCC_MidiProtocol::System::Exclusive::End; }
		
		for(uint8_t i = flag1; i < _Buffer.size() - flag2; i++)
		{
			_Buffer[i] = Data[i-flag1];
		}
		
		return *this;
	}
//
//////////////////////////////////////////////////////////////////