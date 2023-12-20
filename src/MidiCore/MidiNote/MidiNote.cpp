#include "MidiNote.h"

using namespace MCC_MidiCore::Protocol;

MusicCompositionCore::MidiCore::MidiNote::MidiNote(uint8_t Pitch, uint8_t OnVel , uint8_t Channel, uint8_t OffVel)
{
    if(Pitch >= MidiNoteRange){_pitch = InvalidMidiNote;}
	else{_pitch = Pitch;}

	if(OnVel >= MidiVelocityRange){ _onVelocity = InvalidMidiVelocity;}
	else{_onVelocity = OnVel;}

	if(OffVel >= MidiVelocityRange){ _offVelocity = InvalidMidiVelocity;}
	else{_offVelocity = OffVel;}

	if(Channel >= MidiChannelRange){ _channel = InvalidMidiChannel;}
	else{_channel = Channel;}
}

MusicCompositionCore::MidiCore::MidiNote::MidiNote(const MusicalCore::MusicalNote::Note& source, uint8_t OnVel , uint8_t Channel, uint8_t OffVel)
{
	if(source.MidiPitch() >= MidiNoteRange){_pitch = InvalidMidiNote;}
	else{_pitch = source.MidiPitch();}

	if(OnVel >= MidiVelocityRange){ _onVelocity = InvalidMidiVelocity;}
	else{_onVelocity = OnVel;}

	if(OffVel >= MidiVelocityRange){ _offVelocity = InvalidMidiVelocity;}
	else{_offVelocity = OffVel;}

	if(Channel >= MidiChannelRange){_channel = InvalidMidiChannel;}
	else{_channel = Channel;}
}

MusicCompositionCore::MidiCore::MidiNote::MidiNote(const MCC_MusicalNote::Pitch& source, uint8_t OnVel , uint8_t Channel, uint8_t OffVel)
{
	if(MCC_MusicalNote::Note(source,3).MidiPitch() >= MidiNoteRange){_pitch = InvalidMidiNote;}
	else{_pitch = MCC_MusicalNote::Note(source,3).MidiPitch();}

	if(OnVel >= MidiVelocityRange){ _onVelocity = InvalidMidiVelocity;}
	else{_onVelocity = OnVel;}

	if(OffVel >= MidiVelocityRange){ _offVelocity = InvalidMidiVelocity;}
	else{_offVelocity = OffVel;}

	if(Channel >= MidiChannelRange){_channel = InvalidMidiChannel;}
	else{_channel = Channel;}
}

const uint8_t MusicCompositionCore::MidiCore::MidiNote::Pitch() const
{
	return _pitch;
}

void MusicCompositionCore::MidiCore::MidiNote::SetPitch(uint8_t NewPitch)
{
	_pitch = NewPitch&0x7F;
}

const uint8_t MusicCompositionCore::MidiCore::MidiNote::OnVelocity() const
{
	return _onVelocity;
}

void MusicCompositionCore::MidiCore::MidiNote::SetOnVelocity(uint8_t NewVelocity)
{
	_onVelocity = NewVelocity&0x7F;
}

const uint8_t MusicCompositionCore::MidiCore::MidiNote::OffVelocity() const
{
	return _offVelocity;
}

void MusicCompositionCore::MidiCore::MidiNote::SetOffVelocity(uint8_t NewVelocity)
{
	_offVelocity = NewVelocity&0x7F;
}

const uint8_t MusicCompositionCore::MidiCore::MidiNote::Channel() const
{
	return _channel;
}

void MusicCompositionCore::MidiCore::MidiNote::SetChannel(uint8_t NewChannel)
{
	_channel = NewChannel&0xF;
}
