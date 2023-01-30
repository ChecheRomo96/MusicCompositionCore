#ifndef MCC_MIDI_NOTE_H
#define MCC_MIDI_NOTE_H

#include <MCC_BuildSettings.h>
#include "../MidiDefinitions.h"
#include "../../MusicalCore/MusicalNote/MusicalNote.h"

namespace MusicCompositionCore
{
    namespace Core
    {
        namespace MidiCore
        {
            class MidiNote
            {
                uint8_t _pitch;
                uint8_t _velocity;
                uint8_t _channel;

                public:

                    MidiNote();

                    MidiNote(uint8_t pitch, uint8_t vel , uint8_t channel = 0);
                    MidiNote(const MusicalCore::MusicalNote::Note& source, uint8_t vel, uint8_t channel = 0);
                    MidiNote(const MusicalCore::MusicalNote::Pitch& source, uint8_t vel, uint8_t channel = 0);

                    MidiNote& MidiNote::operator=(const MidiNote& Source);

                    
                    void SetPitch(uint8_t NewPitch);
                    const uint8_t Pitch() const;

                    void SetChannel(uint8_t NewChannel);
                    const uint8_t Channel() const;
                    
                    void SetVelocity(uint8_t NewVelocity);
                    const uint8_t Velocity() const;
            };
        }
    }
}



#endif//MCC_MIDI_NOTE_H
