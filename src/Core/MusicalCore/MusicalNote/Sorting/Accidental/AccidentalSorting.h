#ifndef MCC_ACCIDENTAL_SORTING_H
#define MCC_ACCIDENTAL_SORTING_H

	#include <MCC_BuildSettings.h>
	#include <CPVector.h>
	
	#include "../../Pitch/NotePitch.h"

	namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Sorting::Accidental
	{
        int8_t Ascending(const Pitch::Accidental& Element, const Pitch::Accidental& Pivot);
        int8_t Descending(const Pitch::Accidental& Element, const Pitch::Accidental& Pivot);
	}

#endif//MCC_ACCIDENTAL_SORTING_H
