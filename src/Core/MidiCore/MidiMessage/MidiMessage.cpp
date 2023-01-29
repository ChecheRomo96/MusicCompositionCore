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

	for(uint8_t i = 0; i < _Buffer.size(; i++)
	{
		_Buffer[i] = Source.Buffer()[i];
	}

	return *this;
}

MidiMessage& MidiMessage::NoteOn(uint8_t Pitch, uint8_t Vel , uint8_t Channel)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::NoteOn & (Channel&=0x0F);
	_Buffer[1] = Pitch;
	_Buffer[2] = Vel;

	return *this;
}

MidiMessage& MidiMessage::NoteOn(const MidiCore::MidiNote& Source)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::NoteOn & (Channel&=0x0F);
	_Buffer[1] = Source.Pitch();
	_Buffer[2] = Source.Velocity();
	
	return *this;
}

MidiMessage& MidiMessage::NoteOn(const MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::NoteOn & (Channel&=0x0F);
	_Buffer[1] = Source.MidiPitch();
	_Buffer[2] = Vel;
	
	return *this;
}

MidiMessage& MidiMessage::NoteOn(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel, uint8_t Channel)
{
	_Buffer.resize(3);
	MCC_MusicalNote::Note tmpNote(Source,Octave);

	_Buffer[0] = MCC_MidiProtocol::NoteOn & (Channel&=0x0F);
	_Buffer[1] = tmpNote.MidiPitch();
	_Buffer[2] = Vel;
	
	return *this;
}

MidiMessage& MidiMessage::NoteOff(uint8_t Pitch, uint8_t Channel)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::NoteOff & (Channel&=0x0F);
	_Buffer[1] = Pitch;
	_Buffer[2] = 0;
	
	return *this;
}

MidiMessage& MidiMessage::NoteOff(const MidiCore::MidiNote& Source)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::NoteOff & (Channel&=0x0F);
	_Buffer[1] = Source.Pitch();
	_Buffer[2] = 0;
	
	return *this;
}

MidiMessage& MidiMessage::NoteOff(const MusicalCore::MusicalNote::Note& Source, uint8_t Channel)
{
	_Buffer.resize(3);

	_Buffer[0] = MCC_MidiProtocol::NoteOff & (Channel&=0x0F);
	_Buffer[1] = Source.MidiPitch();
	_Buffer[2] = 0;
	
	return *this;
}

MidiMessage& MidiMessage::NoteOff(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Channel)
{
	_Buffer.resize(3);
	MCC_MusicalNote::Note tmpNote(Source,Octave);

	_Buffer[0] = MCC_MidiProtocol::NoteOff & (Channel&=0x0F);
	_Buffer[1] = tmpNote.MidiPitch();
	_Buffer[2] = 0;
	
	return *this;
}

MidiMessage& MidiMessage::ProgramChange(uint8_t Program, uint8_t Channel)
{
	_Buffer.resize(2);

	_Buffer[0] = MCC_MidiProtocol::ProgramChange & (Channel&=0x0F);
	_Buffer[1] = Program;
	
	return *this;
}

MidiMessage& MidiMessage::ContinuousController(uint8_t ControllerNumber, uint8_t Value, uint8_t Channel)
{

	
	return *this;
}
MidiMessage& MidiMessage::PitchBend(int16_t Value, uint8_t Channel)
{

	
	return *this;
}
MidiMessage& MidiMessage::PolyphonicAfetrtouch(uint8_t Note, uint8_t Pressure, uint8_t Channel)
{

	
	return *this;
}

MidiMessage& MidiMessage::Start()
{

	
	return *this;
}
MidiMessage& MidiMessage::Continue()
{

	
	return *this;
}
MidiMessage& MidiMessage::Stop()
{

	return *this;
}

MidiMessage& MidiMessage::ClockTick()
{

	return *this;
}
MidiMessage& MidiMessage::SongPositionCounter(uint16_t Position)
{

	return *this;
}
MidiMessage& MidiMessage::SongSelect(uint8_t Song)
{

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