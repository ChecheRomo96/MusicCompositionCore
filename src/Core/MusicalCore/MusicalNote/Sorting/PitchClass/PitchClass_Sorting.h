#ifndef MCC_PITCH_CLASS_SORTING_H
#define MCC_PITCH_CLASS_SORTING_H

	#include <MCC_BuildSettings.h>
	
	#include "../../Pitch/NotePitch.h"

	namespace MusicCompositionCore
	{
		namespace Core
		{
			namespace MusicalCore
			{
				namespace MusicalNote
				{
					namespace Sorting
					{
						namespace PitchClass
						{
							int8_t Letter_Ascending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot);
							int8_t Letter_Descending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot);

							int8_t Accidental_Ascending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot);
							int8_t Accidental_Descending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot);

							int8_t NotePitch_Ascending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot);
							int8_t NotePitch_Descending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot);

							int8_t MidiPitch_Ascending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot);
							int8_t MidiPitch_Descending(const Pitch::PitchClass& Element, const Pitch::PitchClass& Pivot);
						}
					}
				}
			}
		}
	}

#endif//MCC_PITCH_CLASS_SORTING_H