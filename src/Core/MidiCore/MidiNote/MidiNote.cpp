#include "MidiNote.h"

MusicCompositionCore::Core::MidiCore::MidiNote::MidiNote(uint8_t pitch, uint8_t vel , uint8_t channel)
{
    if(pitch >= MidiNoteRange){_pitch = InvalidMidiNote;}
	else{_pitch = pitch;}

	if(vel >= MidiVelocityRange){ _velocity = InvalidMidiVelocity;}
	else{_velocity = vel;}

	if(channel >= MidiChannelRange){ _channel = InvalidMidiChannel;}
	else{_channel = channel;}
}

MusicCompositionCore::Core::MidiCore::MidiNote::MidiNote(const MusicalCore::MusicalNote::Note& source, uint8_t vel, uint8_t channel)
{
	if(source.MidiPitch() >= MidiNoteRange){_pitch = InvalidMidiNote;}
	else{_pitch = source.MidiPitch();}

	if(vel >= MidiVelocityRange){_velocity = InvalidMidiVelocity;}
	else{_velocity = vel;}

	if(channel >= MidiChannelRange){_channel = InvalidMidiChannel;}
	else{_channel = channel;}
}

MusicCompositionCore::Core::MidiCore::MidiNote::MidiNote(const MCC_MusicalNote::Pitch& source, uint8_t vel, uint8_t channel)
{
	if(MCC_MusicalNote::Note(source,3).MidiPitch() >= MidiNoteRange){_pitch = InvalidMidiNote;}
	else{_pitch = MCC_MusicalNote::Note(source,3).MidiPitch();}

	if(vel >= MidiVelocityRange){_velocity = InvalidMidiVelocity;}
	else{_velocity = vel;}

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

const uint8_t MusicCompositionCore::Core::MidiCore::MidiNote::Velocity() const
{
	return _velocity;
}

void MusicCompositionCore::Core::MidiCore::MidiNote::SetChannel(uint8_t NewChannel)
{
	_channel = NewChannel&0xF;
}

const uint8_t MusicCompositionCore::Core::MidiCore::MidiNote::Channel() const
{
	return _channel;
}

void MusicCompositionCore::Core::MidiCore::MidiNote::SetVelocity(uint8_t NewVelocity)
{
	_velocity = NewVelocity&0x7F;
}
