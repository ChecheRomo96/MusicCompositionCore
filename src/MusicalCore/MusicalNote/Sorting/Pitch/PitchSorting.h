#ifndef MCC_PITCH_CLASS_SORTING_H
#define MCC_PITCH_CLASS_SORTING_H

	#include <MCC_BuildSettings.h>

	#include "../../MusicalNote.h"
	#include "../../Pitch/NotePitch.h"

	namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Sorting::Pitch
	{
		const auto Letter_Ascending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.GetLetter() < Pivot.GetLetter();
		};

		const auto Letter_Descending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.GetLetter() > Pivot.GetLetter();
		};

		const auto Accidental_Ascending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.GetAccidental() < Pivot.GetAccidental();
		};

		const auto Accidental_Descending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.GetAccidental() > Pivot.GetAccidental();
		};
		
		const auto NotePitch_Ascending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.NotePitch() < Pivot.NotePitch();
		};

		const auto NotePitch_Descending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.NotePitch() > Pivot.NotePitch();
		};
		
		const auto MidiPitch_Ascending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.MidiPitch() < Pivot.MidiPitch();
		};

		const auto MidiPitch_Descending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.MidiPitch() > Pivot.MidiPitch();
		};
	}

#endif//MCC_PITCH_CLASS_SORTING_H