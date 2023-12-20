#ifndef MCC_MIDI_MESSAGE_H
#define MCC_MIDI_MESSAGE_H

#include <MCC_BuildSettings.h>
#include <CPvector.h>

#include "../MidiCore.h"

#if defined (MCC_MIDI_NOTE_ENABLED)
    #include "../MidiNote/MidiNote.h"
#endif

#if defined (MCC_MUSICAL_CORE_ENABLED)
    #include "../../MusicalCore/MusicalCore.h"
#endif


namespace MusicCompositionCore::MidiCore
{
    class MidiMessage {

    protected:

        cpstd::vector<uint8_t> _Buffer;

    public:

        //////////////////////////////////////////////////////////////////
        // Constructor and Assignment operator

            MidiMessage();

            MidiMessage& operator=(const MidiMessage& Source);
        //
        //////////////////////////////////////////////////////////////////
        // Buffer API

            const cpstd::vector<uint8_t>& Buffer() const;
        //
        //////////////////////////////////////////////////////////////////
        // Channel Voice Messages
            
            MidiMessage& NoteOff(uint8_t Pitch, uint8_t Vel = 0, uint8_t Channel = 0);
            MidiMessage& NoteOn(uint8_t Pitch, uint8_t Vel , uint8_t Channel = 0);
            MidiMessage& AfterTouch(uint8_t Note, uint8_t Pressure, uint8_t Channel = 0);
            MidiMessage& ControlChange(uint8_t ControllerNumber, uint8_t Value, uint8_t Channel = 0);
            MidiMessage& ProgramChange(uint8_t Program, uint8_t Channel = 0);
            MidiMessage& ChannelPressure(uint8_t Pressure, uint8_t Channel = 0);
            MidiMessage& PitchBend(int8_t Value, uint8_t Channel = 0);
            MidiMessage& PitchBend(int16_t Value, uint8_t Channel = 0);
            MidiMessage& PitchBend(uint8_t Value, uint8_t Channel = 0);
            MidiMessage& PitchBend(uint16_t Value, uint8_t Channel = 0);

            //////////////////////////////////////////////////////////////
            // MCC_MidiCore::MidiNote

                #if defined (MCC_MIDI_NOTE_ENABLED)
                    MidiMessage& NoteOff(const MidiCore::MidiNote& Source);
                    MidiMessage& NoteOn(const MidiCore::MidiNote& Source);
                #endif
            //
            //////////////////////////////////////////////////////////////
            // Mcc_MusicalNote::Note

                #if defined (MCC_MUSICAL_NOTE_ENABLED)
                    MidiMessage& NoteOn(const MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel = 0);
                    MidiMessage& NoteOff(const MusicalCore::MusicalNote::Note& Source, uint8_t Vel = 0, uint8_t Channel = 0);
                #endif
            //
            //////////////////////////////////////////////////////////////
            // Mcc_MusicalNote::Pitch

                #if defined (MCC_MUSICAL_NOTE_ENABLED)
                    MidiMessage& NoteOn(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel, uint8_t Channel = 0);
                    MidiMessage& NoteOff(const MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel = 0, uint8_t Channel = 0);
                #endif
            //
            //////////////////////////////////////////////////////////////
        //
        //////////////////////////////////////////////////////////////////
        // System Common Messages

            MidiMessage& MTC_QuarterFrame(uint8_t MTC_ID, uint8_t Data);
            MidiMessage& SongPositionPointer(uint16_t Position);
            MidiMessage& SongSelect(uint8_t Song);
            MidiMessage& TuningRequest();
        //
        //////////////////////////////////////////////////////////////////
        // System Real Time Messages

            MidiMessage& TimingTick();
            MidiMessage& Start();
            MidiMessage& Continue();
            MidiMessage& Stop();
            MidiMessage& ActiveSensing();
            MidiMessage& SystemReset();
        //
        //////////////////////////////////////////////////////////////////
        // System Exclusive Messages

            MidiMessage& SystemExclusive(const cpstd::vector<uint8_t>& Data);
            MidiMessage& SystemExclusive(uint8_t* Data, uint8_t Length);
        //
        //////////////////////////////////////////////////////////////////
        
    };
}

#endif//MCC_MIDI_MESSAGE_H
