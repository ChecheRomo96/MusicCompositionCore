#include "MidiMessage.h"
#include "../MidiDefinitions.h"
#include "../../MusicalCore/MusicalCore.h"


MidiMessage::MidiMessage()
{

}

MidiMessage& MidiMessage::operator=(const MidiNote& Source)
{
	Buffer.resize(Source.Buffer.size());

	for(uint8_t i = 0; i < Buffer.size())
	{
		Buffer[i] = Source.Buffer[i];
	}
}

void MidiMessage::NoteOn(uint8_t Pitch, uint8_t Vel , uint8_t Channel = 0)
{
	Buffer.Resize(3);

	Buffer[0] = MCC_MidiProtocol::NoteOn & (Channel&=0x0F);
	Buffer[1] = Pitch;
	Buffer[2] = Vel;
}

void MidiMessage::NoteOn(const MidiCore::MidiNote& Source)
{
	Buffer.Resize(3);

	Buffer[0] = MCC_MidiProtocol::NoteOn & (Channel&=0x0F);
	Buffer[1] = Source.Pitch();
	Buffer[2] = Source.Velocity();
}

void MidiMessage::NoteOn(const MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel = 0)
{
	Buffer.Resize(3);

	Buffer[0] = MCC_MidiProtocol::NoteOn & (Channel&=0x0F);
	Buffer[1] = Source.MidiPitch();
	Buffer[2] = Vel;
}

void MidiMessage::NoteOn(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel, uint8_t Channel = 0)
{
	Buffer.Resize(3);
	MCC_MusicalNote::Note tmpNote(Source,Octave);

	Buffer[0] = MCC_MidiProtocol::NoteOn & (Channel&=0x0F);
	Buffer[1] = tmpNote.MidiPitch();
	Buffer[2] = Vel;
}

void MidiMessage::NoteOff(uint8_t Pitch, uint8_t Channel = 0)
{
	Buffer.Resize(3);

	Buffer[0] = MCC_MidiProtocol::NoteOff & (Channel&=0x0F);
	Buffer[1] = Pitch;
	Buffer[2] = 0;
}

void MidiMessage::NoteOff(const MidiCore::MidiNote& Source)
{
	Buffer.Resize(3);

	Buffer[0] = MCC_MidiProtocol::NoteOff & (Channel&=0x0F);
	Buffer[1] = Source.Pitch();
	Buffer[2] = 0;
}

void MidiMessage::NoteOff(const MusicalCore::MusicalNote::Note& Source, uint8_t Channel = 0)
{
	Buffer.Resize(3);

	Buffer[0] = MCC_MidiProtocol::NoteOff & (Channel&=0x0F);
	Buffer[1] = Source.MidiPitch();
	Buffer[2] = 0;
}

void MidiMessage::NoteOff(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Channel = 0)
{
	Buffer.Resize(3);
	MCC_MusicalNote::Note tmpNote(Source,Octave);

	Buffer[0] = MCC_MidiProtocol::NoteOff & (Channel&=0x0F);
	Buffer[1] = tmpNote.MidiPitch();
	Buffer[2] = 0;
}

void MidiMessage::ProgramChange(uint8_t Program, uint8_t Channel = 0)
{

}
void MidiMessage::ContinuousController(uint8_t ControllerNumber, uint8_t Value, uint8_t Channel = 0)
{

}
void MidiMessage::PitchBend(int16_t Value, uint8_t Channel = 0)
{

}
void MidiMessage::PolyphonicAfetrtouch(uint8_t Note, uint8_t Pressure, uint8_t Channel = 0)
{

}

void MidiMessage::Start()
{

}
void MidiMessage::Continue()
{

}
void MidiMessage::Stop()
{

}

void MidiMessage::ClockTick()
{

}
void MidiMessage::SongPositionCounter(uint16_t Position)
{

}
void MidiMessage::SongSelect(uint8_t Song)
{

}

void MidiMessage::SystemExclusive(const CPVector::vector& Data)
{

}
void MidiMessage::SystemExclusive(uint8_t* Data, uint8_t Length)
{

}