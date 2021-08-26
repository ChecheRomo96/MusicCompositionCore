#ifndef MCC_ACCIDENTAL_CLASS_SORTING_H
#define MCC_ACCIDENTAL_CLASS_SORTING_H

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
						namespace AccidentalClass
						{
							int8_t Ascending(const AccidentalClass& Element, const AccidentalClass& Pivot);
							int8_t Descending(const AccidentalClass& Element, const AccidentalClass& Pivot);
						}
					}
				}
			}
		}
	}

#endif//MCC_ACCIDENTAL_CLASS_SORTING_H