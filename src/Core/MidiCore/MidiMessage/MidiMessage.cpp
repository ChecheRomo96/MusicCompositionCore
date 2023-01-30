#include "MidiMessage.h"
#include "../MidiDefinitions.h"
#include "../../MusicalCore/MusicalCore.h"

using namespace MusicCompositionCore::Core::MidiCore;

MidiMessage::MidiMessage()
{

}

const CPVector::vector<uint8_t>& MidiMessage::Buffer()
{
	return _Buffer;
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

MidiMessage& MidiMessage::NoteOn(uint8_t Pitch, uint8_t Vel, uint8_t Channel)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::NoteOn | (Channel&0x0F);
	_Buffer[1] = Pitch;
	_Buffer[2] = Vel;

	return *this;
}

MidiMessage& MidiMessage::NoteOn(const MidiCore::MidiNote& Source)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::NoteOn | (Source.Channel()&0x0F);
	_Buffer[1] = Source.Pitch();
	_Buffer[2] = Source.Velocity();
	
	return *this;
}

MidiMessage& MidiMessage::NoteOn(const MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::NoteOn | (Channel&0x0F);
	_Buffer[1] = Source.MidiPitch();
	_Buffer[2] = Vel;
	
	return *this;
}

MidiMessage& MidiMessage::NoteOn(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel, uint8_t Channel)
{
	_Buffer.resize(3);
	MCC_MusicalNote::Note tmpNote(Source,Octave);

	_Buffer[0] = MCC_MidiProtocol::NoteOn | (Channel&0x0F);
	_Buffer[1] = tmpNote.MidiPitch();
	_Buffer[2] = Vel;
	
	return *this;
}

MidiMessage& MidiMessage::NoteOff(uint8_t Pitch, uint8_t Channel)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::NoteOff | (Channel&0x0F);
	_Buffer[1] = Pitch;
	_Buffer[2] = 0;
	
	return *this;
}

MidiMessage& MidiMessage::NoteOff(const MidiCore::MidiNote& Source)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::NoteOff | (Source.Channel()&0x0F);
	_Buffer[1] = Source.Pitch();
	_Buffer[2] = 0;
	
	return *this;
}

MidiMessage& MidiMessage::NoteOff(const MusicalCore::MusicalNote::Note& Source, uint8_t Channel)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::NoteOff | (Channel&0x0F);
	_Buffer[1] = Source.MidiPitch();
	_Buffer[2] = 0;
	
	return *this;
}

MidiMessage& MidiMessage::NoteOff(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Channel)
{
	_Buffer.resize(3);
	MCC_MusicalNote::Note tmpNote(Source,Octave);

	_Buffer[0] = MCC_MidiProtocol::NoteOff | (Channel&0x0F);
	_Buffer[1] = tmpNote.MidiPitch();
	_Buffer[2] = 0;
	
	return *this;
}

MidiMessage& MidiMessage::ProgramChange(uint8_t Program, uint8_t Channel)
{
	_Buffer.resize(2);

	_Buffer[0] = MCC_MidiProtocol::ProgramChange | (Channel&0x0F);
	_Buffer[1] = Program;
	
	return *this;
}

MidiMessage& MidiMessage::ContinuousController(uint8_t ControllerNumber, uint8_t Value, uint8_t Channel)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::ContinuousController | (Channel&0x0F);
	_Buffer[1] = ControllerNumber;
	_Buffer[2] = Value;

	return *this;
}

MidiMessage& MidiMessage::PitchBend(int16_t Value, uint8_t Channel)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::PitchBend | (Channel&0x0F);
	_Buffer[1] = Value & 0xFF;
	_Buffer[2] = (Value>>8) & 0xFF;
	
	return *this;
}

MidiMessage& MidiMessage::AfterTouch(uint8_t Note, uint8_t Pressure, uint8_t Channel)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::AfterTouch | (Channel&0x0F);
	_Buffer[1] = Note;
	_Buffer[2] = Pressure;

	return *this;
}

MidiMessage& MidiMessage::ChannelPressure(uint8_t Pressure, uint8_t Channel)
{
	_Buffer.resize(2);

	_Buffer[0] = MCC_MidiProtocol::ChannelPressure | (Channel&0x0F);
	_Buffer[1] = Pressure;

	return *this;
}

MidiMessage& MidiMessage::Start()
{
	_Buffer.resize(1);

	_Buffer[0] = MCC_MidiProtocol::SystemMessage | MCC_MidiProtocol::StartSong;

	return *this;
}

MidiMessage& MidiMessage::Continue()
{
	_Buffer.resize(1);

	_Buffer[0] = MCC_MidiProtocol::SystemMessage | MCC_MidiProtocol::ContinueSong;

	return *this;
}

MidiMessage& MidiMessage::Stop()
{
	_Buffer.resize(1);

	_Buffer[0] = MCC_MidiProtocol::SystemMessage | MCC_MidiProtocol::StopSong;

	return *this;
}

MidiMessage& MidiMessage::ClockTick()
{
	_Buffer.resize(1);

	_Buffer[0] = MCC_MidiProtocol::SystemMessage | MCC_MidiProtocol::TimingTick;

	return *this;
}

MidiMessage& MidiMessage::SongPositionCounter(uint16_t Position)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::SystemMessage | MCC_MidiProtocol::SongPosition;
	_Buffer[1] = Position&0xFF;
	_Buffer[2] = (Position>>8)&0xFF;

	return *this;
}

MidiMessage& MidiMessage::SongSelect(uint8_t Song)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::SystemMessage | MCC_MidiProtocol::SongPosition;
	_Buffer[1] = Song & 0x7F;

	return *this;
}

MidiMessage& MidiMessage::SystemExclusive(const CPVector::vector<uint8_t>& Data)
{

	return *this;
}
MidiMessage& MidiMessage::SystemExclusive(uint8_t* Data, uint8_t Length)
{

	return *this;
}