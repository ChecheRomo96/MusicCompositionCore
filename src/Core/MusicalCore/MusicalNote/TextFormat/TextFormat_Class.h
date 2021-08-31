#ifndef MCC_NOTE_FORMAT_CLASS_H
#define MCC_NOTE_FORMAT_CLASS_H

	#include <MCC_BuildSettings.h>

	#include "NoteFormat.h"

	namespace MusicCompositionCore
	{
        namespace Core
        {
        	namespace MusicalCore
       		{
       			namespace MusicalNote
       			{
       				namespace TextFormat
       				{
       					class Format
       					{
	       					uint8_t data;

		       				public:
		       					/////////////////////////////////////////////////////////////////////////
								// Constructors, Destructors and Clear Function

			       					Format();
			       					~Format();
			       					void Clear();
			       				//
		       					/////////////////////////////////////////////////////////////////////////
								// Copy Constructor and assignment operator

			       					Format(const Format& source);
			       					Format(uint8_t data);
			       					Format(bool AccidentalMode, bool OctaveEnabled, uint8_t Spacing, bool NaturalMode = NaturalDisabled);
			       					Format& operator=(const Format& src);
			       				//
		       					/////////////////////////////////////////////////////////////////////////
								// Operators
						        	operator uint8_t() const;
						        //
		       					/////////////////////////////////////////////////////////////////////////
								// Const Return Functions
									
									const uint8_t Data() const;

									const bool AccidentalMode() const;
									const bool NaturalMode() const;
									const bool OctaveEnabled() const;
									const uint8_t SpaceMode() const;
						        //
		       					/////////////////////////////////////////////////////////////////////////
								// Setters

									void Set_AccidentalMode(bool x);
									void Set_AccidentalShort();
									void Set_AccidentalLong();

									void Set_OctaveMode(bool x);
									void Set_OctaveEnabled();
									void Set_OctaveDisabled();

									void Set_SpacingMode(uint8_t x);
									void Set_SpaceEnabled();
									void Set_SpaceJustified();
									void Set_SpaceDisabled();

									void Set_NaturalMode(bool x);
									void Set_NaturalEnabled();
									void Set_NaturalDisabled();
								//
		       					/////////////////////////////////////////////////////////////////////////
	       				};
	       			}
				}
			}
		}
	}

#endif//MCC_NOTE_FORMAT_CLASS_H