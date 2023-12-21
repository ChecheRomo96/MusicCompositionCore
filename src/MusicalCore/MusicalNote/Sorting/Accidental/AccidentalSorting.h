#ifndef MCC_ACCIDENTAL_SORTING_H
#define MCC_ACCIDENTAL_SORTING_H

	#include <MCC_BuildSettings.h>
	#include <CPVector.h>
	
	#include "../../Pitch/NotePitch.h"

	namespace MusicCompositionCore::MusicalCore::MusicalNote::Sorting::Accidental
	{
		const auto Ascending = [](const Pitch::Accidental& Element, const Pitch::Accidental& Pivot){
			return Element < Pivot;
		};

		const auto Descending = [](const Pitch::Accidental& Element, const Pitch::Accidental& Pivot){
			return Element > Pivot;
		};
	}

#endif//MCC_ACCIDENTAL_SORTING_H
