#ifndef MCC_LETTER_CLASS_SORTING_H
#define MCC_LETTER_CLASS_SORTING_H

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
						namespace LetterClass
						{
							int8_t Ascending(const LetterClass& Element, const LetterClass& Pivot);
							int8_t Descending(const LetterClass& Element, const LetterClass& Pivot);
						}
					}
				}
			}
		}
	}

#endif//MCC_LETTER_CLASS_SORTING_H