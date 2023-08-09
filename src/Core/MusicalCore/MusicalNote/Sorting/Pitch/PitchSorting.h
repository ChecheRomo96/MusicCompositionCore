#ifndef MCC_PITCH_CLASS_SORTING_H
#define MCC_PITCH_CLASS_SORTING_H

	#include <MCC_BuildSettings.h>
#include <CPVector.h>

	#include "../../MusicalNote.h"
	#include "../../Pitch/NotePitch.h"

	namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Sorting::Pitch
	{
		int8_t Letter_Ascending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot);
		int8_t Letter_Descending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot);

		int8_t Accidental_Ascending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot);
		int8_t Accidental_Descending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot);

		int8_t NotePitch_Ascending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot);
		int8_t NotePitch_Descending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot);

		int8_t MidiPitch_Ascending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot);
		int8_t MidiPitch_Descending(const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot);
	}

#endif//MCC_PITCH_CLASS_SORTING_H