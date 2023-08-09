#ifndef MCC_MIDI_CORE_H
#define MCC_MIDI_CORE_H

	#include <MCC_BuildSettings.h>
	
	
	#include "MidiDefinitions.h"

	#if defined MCC_MIDI_NOTE_ENABLED
		#include "MidiNote/MidiNote.h"
	#endif

	#if defined MCC_MIDI_MESSAGE_ENABLED
		#include "MidiMessage/MidiMessage.h"
	#endif

#endif//MCC_MIDI_CORE_H