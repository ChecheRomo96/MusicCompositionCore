#ifndef MCC_NOTE_FORMAT_H
#define MCC_NOTE_FORMAT_H

	#include <MCC_BuildSettings.h>

	namespace MusicCompositionCore
	{
        namespace Core
        {
        	namespace MusicalCore
       		{
       			namespace MusicalNote
       			{
       				namespace NoteFormat
       				{
						class Format;
                        
						static constexpr bool AccidentalShort = 1;
						static constexpr bool AccidentalLong = 0;
						static constexpr uint8_t AccidentalMode_Bit = 0;
						static constexpr uint8_t AccidentalShort_Mask = 0b00000001;
						static constexpr uint8_t AccidentalLong_Mask = 0;
                        
						static constexpr bool OctaveEnabled = 1;
						static constexpr bool OctaveDisabled = 0;
						static constexpr uint8_t OctaveEnabled_Bit = 1;
						static constexpr uint8_t OctaveEnabled_Mask = 0b000010;
						static constexpr uint8_t OctaveDisabled_Mask = 0;
                        
                        static constexpr uint8_t SpaceEnabled = 0b10;
                        static constexpr uint8_t SpaceJustified = 0b01;
                        static constexpr uint8_t SpaceDisabled = 0;
                        
                        static constexpr uint8_t SpaceMode_Bit = 2;
                        static constexpr uint8_t SpaceEnabled_Mask = 0b000001000;
                        static constexpr uint8_t SpaceJustified_Mask = 0b000000100;
                        static constexpr uint8_t SpaceDisabled_Mask = 0;
                        
                        static constexpr uint8_t NaturalMode_Bit = 4;
                        static constexpr bool NaturalDisabled = 1;
                        static constexpr bool NaturalEnabled = 0;
                        static constexpr uint8_t NaturalDisabled_Mask = 0b000010000;
                        static constexpr uint8_t NaturalEnabled_Mask = 0;
                        
						extern Format DefaultFormat;
					}
				}
			}
		}
	}

	namespace MCC_MusicalNoteFormat = MusicCompositionCore::Core::MusicalCore::MusicalNote::NoteFormat;

	#include "NoteFormat_Class.h"
	
#endif//MCC_NOTE_FORMAT_H
