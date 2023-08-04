#include "MidiNote.h"

MusicCompositionCore::Core::MidiCore::MidiNote::MidiNote(uint8_t Pitch, uint8_t OnVel , uint8_t Channel, uint8_t OffVel)
{
    if(Pitch >= MidiNoteRange){_pitch = InvalidMidiNote;}
	else{_pitch = Pitch;}

	if(OnVel >= MidiVelocityRange){ _onVelocity = InvalidMidiVelocity;}
	else{_onVelocity = OnVel;}

	if(OffVel >= MidiVelocityRange){ _offVelocity = InvalidMidiVelocity;}
	else{_offVelocity = OffVel;}

	if(channel >= MidiChannelRange){ _channel = InvalidMidiChannel;}
	else{_channel = channel;}
}

MusicCompositionCore::Core::MidiCore::MidiNote::MidiNote(const MusicalCore::MusicalNote::Note& source, uint8_t OnVel , uint8_t Channel, uint8_t OffVel)
{
	if(source.MidiPitch() >= MidiNoteRange){_pitch = InvalidMidiNote;}
	else{_pitch = source.MidiPitch();}

	if(OnVel >= MidiVelocityRange){ _onVelocity = InvalidMidiVelocity;}
	else{_onVelocity = OnVel;}

	if(OffVel >= MidiVelocityRange){ _offVelocity = InvalidMidiVelocity;}
	else{_offVelocity = OffVel;}

	if(channel >= MidiChannelRange){_channel = InvalidMidiChannel;}
	else{_channel = channel;}
}

MusicCompositionCore::Core::MidiCore::MidiNote::MidiNote(const MCC_MusicalNote::Pitch& source, uint8_t OnVel , uint8_t Channel, uint8_t OffVel)
{
	if(MCC_MusicalNote::Note(source,3).MidiPitch() >= MidiNoteRange){_pitch = InvalidMidiNote;}
	else{_pitch = MCC_MusicalNote::Note(source,3).MidiPitch();}

	if(OnVel >= MidiVelocityRange){ _onVelocity = InvalidMidiVelocity;}
	else{_onVelocity = OnVel;}

	if(OffVel >= MidiVelocityRange){ _offVelocity = InvalidMidiVelocity;}
	else{_offVelocity = OffVel;}

	if(channel >= MidiChannelRange){_channel = InvalidMidiChannel;}
	else{_channel = channel;}
}

const uint8_t MusicCompositionCore::Core::MidiCore::MidiNote::Pitch() const
{
	return _pitch;
}

void MusicCompositionCore::Core::MidiCore::MidiNote::SetPitch(uint8_t NewPitch)
{
	_pitch = NewPitch&0x7F;
}

const uint8_t MusicCompositionCore::Core::MidiCore::MidiNote::OnVelocity() const
{
	return _onVelocity;
}

void MusicCompositionCore::Core::MidiCore::MidiNote::SetOnVelocity(uint8_t NewVelocity)
{
	_onVelocity = NewVelocity&0x7F;
}

const uint8_t MusicCompositionCore::Core::MidiCore::MidiNote::OffVelocity() const
{
	return _offVelocity;
}

void MusicCompositionCore::Core::MidiCore::MidiNote::SetOffVelocity(uint8_t NewVelocity)
{
	_offVelocity = NewVelocity&0x7F;
}

const uint8_t MusicCompositionCore::Core::MidiCore::MidiNote::Channel() const
{
	return _channel;
}

void MusicCompositionCore::Core::MidiCore::MidiNote::SetChannel(uint8_t NewChannel)
{
	_channel = NewChannel&0xF;
}
