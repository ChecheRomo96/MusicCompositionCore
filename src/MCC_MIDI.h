#ifndef MCC_MIDI_H
#define MCC_MIDI_H

    #include <MCC_BuildSettings.h>

    #include "MidiProtocol/MCC_MidiProtocol.h"

    #if defined MCC_MIDI_NOTE_ENABLED
        #include "MidiNote/MidiNote.h"
    #endif

    #if defined MCC_MIDI_MESSAGE_ENABLED
        #include "MidiMessage/MidiMessage.h"
    #endif

#endif//MCC_MIDI_H