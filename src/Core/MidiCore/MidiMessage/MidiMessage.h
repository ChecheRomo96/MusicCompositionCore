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

                    MidiNote();

                    MidiNote(uint8_t Pitch, uint8_t Vel , uint8_t Channel = 0);
                    MidiNote(const MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel = 0);
                    MidiNote(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Vel, uint8_t Channel = 0);

                    MidiNote& MidiNote::operator=(const MidiNote& Source);

                    void NoteOn(uint8_t Pitch, uint8_t Vel , uint8_t Channel = 0);
                    void NoteOn(const MidiCore::MidiNote& Source);
                    void NoteOn(const MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel = 0);
                    void NoteOn(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Vel, uint8_t Channel = 0);

                    void NoteOff(uint8_t Pitch, uint8_t Channel = 0);
                    void NoteOff(const MidiCore::MidiNote& Source);
                    void NoteOff(const MusicalCore::MusicalNote::Note& Source, uint8_t Channel = 0);
                    void NoteOff(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Channel = 0);

                    void ProgramChange(uint8_t Program, uint8_t Channel = 0);
                    void ContinuousController(uint8_t ControllerNumber, uint8_t Value, uint8_t Channel = 0);
                    void PitchBend(int16_t Value, uint8_t Channel = 0);
                    void PolyphonicAfetrtouch(uint8_t Note, uint8_t Pressure, uint8_t Channel = 0);

                    void Start();
                    void Continue();
                    void Stop();

                    void ClockTick();
                    void SongPositionCounter(uint16_t Position);
                    void SongSelect(uint8_t Song);

                    void SystemExclusive(const CPVector::vector& Data);
                    void SystemExclusive(uint8_t* Data, uint8_t Length);

            };
        }
    }
}

#endif//MCC_MIDI_MESSAGE_H