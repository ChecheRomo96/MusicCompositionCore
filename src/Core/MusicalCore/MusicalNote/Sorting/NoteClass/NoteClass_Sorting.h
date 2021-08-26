#ifndef MCC_NOTE_CLASS_SORTING_H
#define MCC_NOTE_CLASS_SORTING_H

	#include <MCC_BuildSettings.h>
	
	#include "../../NoteClass.h"

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
						namespace NoteClass
						{
							int8_t Letter_Ascending(const NoteClass& Element, const NoteClass& Pivot);
							int8_t Letter_Descending(const NoteClass& Element, const NoteClass& Pivot);

							int8_t Accidental_Ascending(const NoteClass& Element, const NoteClass& Pivot);
							int8_t Accidental_Descending(const NoteClass& Element, const NoteClass& Pivot);

							int8_t NotePitch_Ascending(const NoteClass& Element, const NoteClass& Pivot);
							int8_t NotePitch_Descending(const NoteClass& Element, const NoteClass& Pivot);

							int8_t MidiPitch_Ascending(const NoteClass& Element, const NoteClass& Pivot);
							int8_t MidiPitch_Descending(const NoteClass& Element, const NoteClass& Pivot);

							int8_t Octave_Ascending(const NoteClass& Element, const NoteClass& Pivot);
							int8_t Octave_Descending(const NoteClass& Element, const NoteClass& Pivot);
						}
					}
				}
			}
		}
	}

#endif//MCC_NOTE_CLASS_SORTING_H