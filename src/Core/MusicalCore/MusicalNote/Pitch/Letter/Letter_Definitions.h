#ifndef MCC_NOTE_LETTER_DEFINITIONS_H
#define MCC_NOTE_LETTER_DEFINITIONS_H

	#include <MCC_BuildSettings.h>
	
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
						typedef uint8_t LetterType;
						
						namespace Letter
						{

							static constexpr LetterType C = 0u;
							static constexpr LetterType D = 1u;
							static constexpr LetterType E = 2u;
							static constexpr LetterType F = 3u;
							static constexpr LetterType G = 4u;
							static constexpr LetterType A = 5u;
							static constexpr LetterType B = 6u;

							static constexpr LetterType InvalidID = 7u;
							static constexpr uint8_t Count = 7u;
                            
						}
					}
				}
			}	
		}
	}

#endif//MCC_NOTE_LETTER_DEFINITIONS_H