#ifndef MCC_LETTER_CLASS_SORTING_H
#define MCC_LETTER_CLASS_SORTING_H

	#include <MCC_BuildSettings.h>
	#include <CPVector.h>
	
	#include "../../Pitch/NotePitch.h"

	namespace MusicCompositionCore::MusicalNote::Sorting::Letter
	{
		const auto Ascending = [](const Pitch::Letter& Element, const Pitch::Letter& Pivot){
			return Element < Pivot;
		};

		const auto Descending = [](const Pitch::Letter& Element, const Pitch::Letter& Pivot){
			return Element > Pivot;
		};
	}
						
#endif//MCC_LETTER_CLASS_SORTING_H
 
  