#ifndef MCC_ACCIDENTAL_CLASS_SORTING_H
#define MCC_ACCIDENTAL_CLASS_SORTING_H

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
						namespace AccidentalClass
						{
                        int8_t Ascending(const Pitch::Accidental& Element, const Pitch::Accidental& Pivot);
                        int8_t Descending(const Pitch::Accidental& Element, const Pitch::Accidental& Pivot);
						}
					}
				}
			}
		}
	}

#endif//MCC_ACCIDENTAL_CLASS_SORTING_H
