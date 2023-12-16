#ifndef MCC_NOTE_CLASS_SORTING_H
#define MCC_NOTE_CLASS_SORTING_H

	#include <MCC_BuildSettings.h>
	#include <CPVector.h>
	
	#include "../../Note_Class.h"


	namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Sorting::Note
	{

		const auto Letter_Ascending = [](const MusicalNote::Note& Element, const MusicalNote::Note& Pivot){
			return Element.Letter() < Pivot.Letter();
		};

		const auto Letter_Descending = [](const MusicalNote::Note& Element, const MusicalNote::Note& Pivot){
			return Element.Letter() > Pivot.Letter();
		};
		
		const auto Accidental_Ascending = [](const MusicalNote::Note& Element, const MusicalNote::Note& Pivot){
			return Element.Accidental() < Pivot.Accidental();
		};

		const auto Accidental_Ascending = [](const MusicalNote::Note& Element, const MusicalNote::Note& Pivot){
			return Element.Accidental() > Pivot.Accidental();
		};
		
		const auto NotePitch_Ascending = [](const MusicalNote::Note& Element, const MusicalNote::Note& Pivot){
			return Element.NotePitch() < Pivot.NotePitch();
		};

		const auto NotePitch_Ascending = [](const MusicalNote::Note& Element, const MusicalNote::Note& Pivot){
			return Element.NotePitch() > Pivot.NotePitch();
		};
		
		const auto MidiPitch_Ascending = [](const MusicalNote::Note& Element, const MusicalNote::Note& Pivot){
			return Element.MidiPitch() < Pivot.MidiPitch();
		};

		const auto MidiPitch_Ascending = [](const MusicalNote::Note& Element, const MusicalNote::Note& Pivot){
			return Element.MidiPitch() > Pivot.MidiPitch();
		};
		
		const auto Octave_Ascending = [](const MusicalNote::Note& Element, const MusicalNote::Note& Pivot){
			return Element.Octave() < Pivot.Octave();
		};

		const auto Octave_Ascending = [](const MusicalNote::Note& Element, const MusicalNote::Note& Pivot){
			return Element.Octave() > Pivot.Octave();
		};
	}

#endif//MCC_NOTE_CLASS_SORTING_H
