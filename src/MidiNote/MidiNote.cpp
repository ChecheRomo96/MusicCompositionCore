#include "MidiNote.h"

using namespace MCC_MidiProtocol;

MusicCompositionCore::MidiNote::MidiNote(uint8_t Pitch, uint8_t OnVel , uint8_t Channel, uint8_t OffVel)
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

MusicCompositionCore::MidiNote::MidiNote(const MCC_MusicalNote::Note& source, uint8_t OnVel , uint8_t Channel, uint8_t OffVel)
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

MusicCompositionCore::MidiNote::MidiNote(const MCC_MusicalNote::Pitch& source, uint8_t OnVel , uint8_t Channel, uint8_t OffVel)
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

const uint8_t MusicCompositionCore::MidiNote::Pitch() const
{
	return _pitch;
}

void MusicCompositionCore::MidiNote::SetPitch(uint8_t NewPitch)
{
	_pitch = NewPitch&0x7F;
}

const uint8_t MusicCompositionCore::MidiNote::OnVelocity() const
{
	return _onVelocity;
}

void MusicCompositionCore::MidiNote::SetOnVelocity(uint8_t NewVelocity)
{
	_onVelocity = NewVelocity&0x7F;
}

const uint8_t MusicCompositionCore::MidiNote::OffVelocity() const
{
	return _offVelocity;
}

void MusicCompositionCore::MidiNote::SetOffVelocity(uint8_t NewVelocity)
{
	_offVelocity = NewVelocity&0x7F;
}

const uint8_t MusicCompositionCore::MidiNote::Channel() const
{
	return _channel;
}

void MusicCompositionCore::MidiNote::SetChannel(uint8_t NewChannel)
{
	_channel = NewChannel&0xF;
}
