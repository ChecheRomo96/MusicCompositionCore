#ifndef MCC_LETTER_CLASS_SORTING_H
#define MCC_LETTER_CLASS_SORTING_H

	#include <MCC_BuildSettings.h>
	#include <CPVector.h>
	
	#include "../../Note_Class.h"

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
                        int8_t Ascending(const Pitch::Letter& Element, const Pitch::Letter& Pivot);
                        int8_t Descending(const Pitch::Letter& Element, const Pitch::Letter& Pivot);
						}
					}
				}
			}
		}
	}

#endif//MCC_LETTER_CLASS_SORTING_H
