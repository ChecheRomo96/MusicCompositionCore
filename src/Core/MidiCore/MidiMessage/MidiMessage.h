#ifndef MCC_MIDI_MESSAGE_H
#define MCC_MIDI_MESSAGE_H

#include <MCC_BuildSettings.h>
#include <CPVector.h>
#include "../MidiCore.h"

namespace MusicCompositionCore
{
    namespace Core
    {
        namespace MidiCore
        {
            class MidiMessage
            {
                CPVector::vector<uint8_t> Buffer;

                public:

                    MidiMessage();

                    MidiMessage& MidiMessage::operator=(const MidiMessage& Source);
                    const CPVector::vector& Buffer

                    MidiMessage& NoteOn(uint8_t Pitch, uint8_t Vel , uint8_t Channel = 0);
                    MidiMessage& NoteOn(const MidiCore::MidiNote& Source);
                    MidiMessage& NoteOn(const MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel = 0);
                    MidiMessage& NoteOn(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Vel, uint8_t Channel = 0);

                    MidiMessage& NoteOff(uint8_t Pitch, uint8_t Channel = 0);
                    MidiMessage& NoteOff(const MidiCore::MidiNote& Source);
                    MidiMessage& NoteOff(const MusicalCore::MusicalNote::Note& Source, uint8_t Channel = 0);
                    MidiMessage& NoteOff(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Channel = 0);

                    MidiMessage& ProgramChange(uint8_t Program, uint8_t Channel = 0);
                    MidiMessage& ContinuousController(uint8_t ControllerNumber, uint8_t Value, uint8_t Channel = 0);
                    MidiMessage& PitchBend(int16_t Value, uint8_t Channel = 0);
                    MidiMessage& PolyphonicAfetrtouch(uint8_t Note, uint8_t Pressure, uint8_t Channel = 0);

                    MidiMessage& Start();
                    MidiMessage& Continue();
                    MidiMessage& Stop();

                    MidiMessage& ClockTick();
                    MidiMessage& SongPositionCounter(uint16_t Position);
                    MidiMessage& SongSelect(uint8_t Song);

                    MidiMessage& SystemExclusive(const CPVector::vector& Data);
                    MidiMessage& SystemExclusive(uint8_t* Data, uint8_t Length);

            };
        }
    }
}

#endif//MCC_MIDI_MESSAGE_H