#ifndef MCC_NOTE_CLASS_SORTING_H
#define MCC_NOTE_CLASS_SORTING_H

	#include <MCC_BuildSettings.h>
	#include <CPVector.h>
	
	#include "../../Note_Class.h"


	namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Sorting::Note
	{
    	int8_t Letter_Ascending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot);
		int8_t Letter_Descending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot);

		int8_t Accidental_Ascending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot);
		int8_t Accidental_Descending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot);

		int8_t NotePitch_Ascending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot);
		int8_t NotePitch_Descending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot);

		int8_t MidiPitch_Ascending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot);
		int8_t MidiPitch_Descending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot);

		int8_t Octave_Ascending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot);
		int8_t Octave_Descending(const MusicalNote::Note& Element, const MusicalNote::Note& Pivot);
	}

#endif//MCC_NOTE_CLASS_SORTING_H
