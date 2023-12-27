#ifndef MCC_MIDI_NOTE_H
#define MCC_MIDI_NOTE_H

#include <MCC_BuildSettings.h>
#include "../MidiProtocol/MCC_MidiProtocol.h"
#include "../MusicalNote/MusicalNote.h"

namespace MusicCompositionCore
{
    class MidiNote
    {
        uint8_t _pitch;
        uint8_t _onVelocity;
        uint8_t _offVelocity;
        uint8_t _channel;

        public:

            MidiNote();

            MidiNote(uint8_t Pitch, uint8_t OnVel , uint8_t Channel = 0, uint8_t OffVel = 0);
            MidiNote(const MusicalNote::Note& Source, uint8_t OnVel, uint8_t Channel = 0, uint8_t OffVel = 0);
            MidiNote(const MusicalNote::Pitch& Source, uint8_t OnVel, uint8_t Channel = 0, uint8_t OffVel = 0);

            MidiNote& operator=(const MidiNote& Source);

            
            void SetPitch(uint8_t NewPitch);
            const uint8_t Pitch() const;

            void SetChannel(uint8_t NewChannel);
            const uint8_t Channel() const;
            
            void SetOnVelocity(uint8_t NewVelocity);
            const uint8_t OnVelocity() const;

            void SetOffVelocity(uint8_t NewVelocity);
            const uint8_t OffVelocity() const;
    };
}



#endif//MCC_MIDI_NOTE_H
