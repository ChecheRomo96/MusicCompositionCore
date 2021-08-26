#ifndef MCC_ACCIDENATAL_DEFINITIONS_H
#define MCC_ACCIDENATAL_DEFINITIONS_H

	#include <MCC_BuildSettings.h>

	#include "Accidental_Class.h"

	namespace MusicCompositionCore
	{
		namespace Core
	    {
	    	namespace MusicalCore
	   		{
	   			namespace MusicalNote
	   			{
	   				namespace Pitch
	   				{
	   					typedef int8_t AccidentalType;
	   					
	   					namespace Accidental
	   					{
							static constexpr AccidentalType QuadrupleFlat = -4;
							static constexpr AccidentalType TripleFlat = -3;
							static constexpr AccidentalType DoubleFlat = -2;
							static constexpr AccidentalType Flat = -1;
							static constexpr AccidentalType Natural = 0;
							static constexpr AccidentalType Sharp = 1;
							static constexpr AccidentalType DoubleSharp = 2;
							static constexpr AccidentalType TripleSharp = 3;
							static constexpr AccidentalType QuadrupleSharp = 4;
							
							static constexpr AccidentalType InvalidID = 5;
							static constexpr int8_t Min = -4;
							static constexpr int8_t Max = 4;
	   					}
					}
	   			}
	   		}
	   	}
	}

#endif//MCC_ACCIDENATAL_DEFINITIONS