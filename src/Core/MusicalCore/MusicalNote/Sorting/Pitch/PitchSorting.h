#ifndef MCC_PITCH_CLASS_SORTING_H
#define MCC_PITCH_CLASS_SORTING_H

	#include <MCC_BuildSettings.h>
#include <CPVector.h>

	#include "../../MusicalNote.h"
	#include "../../Pitch/NotePitch.h"

	namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Sorting::Pitch
	{
		const auto Letter_Ascending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.Letter() < Pivot.Letter();
		}

		const auto Letter_Ascending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.Letter() > Pivot.Letter();
		}

		const auto Accidental_Ascending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.Accidental() < Pivot.Accidental();
		}

		const auto Accidental_Ascending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.Accidental() > Pivot.Accidental();
		}
		
		const auto NotePitch_Ascending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.NotePitch() < Pivot.NotePitch();
		}

		const auto NotePitch_Ascending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.NotePitch() > Pivot.NotePitch();
		}
		
		const auto MidiPitch_Ascending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.MidiPitch() < Pivot.MidiPitch();
		}

		const auto MidiPitch_Ascending = [](const MCC_MusicalNote::Pitch& Element, const MCC_MusicalNote::Pitch& Pivot){
			return Element.MidiPitch() > Pivot.MidiPitch();
		}
	}

#endif//MCC_PITCH_CLASS_SORTING_H