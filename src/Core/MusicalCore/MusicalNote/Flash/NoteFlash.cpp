#include "NoteFlash.h"
#include <MCC_BuildSettings.h>
#include <CPstring.h>

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;
//using namespace MusicCompositionCore::Core::UtilityCore;

char Flash::Buffer[24];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Note + Format

	char* Flash::GetName(char* buff, const Note& source, const TextFormat::FormatClass& Format)
	{
		return GetName(buff, source.Letter(), source.Accidental(), source.Octave(), Format);
	}

	const char* Flash::GetName(const Note& source, const TextFormat::FormatClass& Format)
	{
		return GetName(Flash::Buffer, source.Letter(), source.Accidental(), source.Octave(), Format);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PitchClass + Format

	char* Flash::GetName(char* buff, const Pitch& source, const TextFormat::FormatClass& Format)
	{
		TextFormat::FormatClass tmp = Format;
        tmp.Octave_Disabled();

		return GetName(buff, source.GetLetter(), source.GetAccidental(), 0, tmp);
	}

	const char* Flash::GetName(const Pitch& source, const TextFormat::FormatClass& Format)
	{
		TextFormat::FormatClass tmp = Format;
		tmp.Octave_Disabled();

		return GetName(Flash::Buffer, source.GetLetter(), source.GetAccidental(), 0, tmp);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PitchClass + Octave + Format

	char* Flash::GetName(char* buff, const Pitch& source, int8_t octave, const TextFormat::FormatClass& Format)
	{
		return GetName(buff, source.GetLetter(), source.GetAccidental(), octave, Format);
	}

	const char* Flash::GetName(const Pitch& source, int8_t octave, const TextFormat::FormatClass& Format)
	{
		return GetName(Flash::Buffer, source.GetLetter(), source.GetAccidental(), octave, Format);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LetterClass + AccidentalClass + Format

	char* Flash::GetName(char* buff, const Pitch::Letter& Letter, const Pitch::Accidental& Accidental, const TextFormat::FormatClass& Format)
	{
        TextFormat::FormatClass tmp = Format;
        tmp.Octave_Disabled();

		return GetName(buff, Letter.ID(), Accidental.ID(), tmp);
	}

	const char* Flash::GetName(const Pitch::Letter& Letter, const Pitch::Accidental& Accidental, const TextFormat::FormatClass& Format)
	{
        TextFormat::FormatClass tmp = Format;
        tmp.Octave_Disabled();
        
		return GetName(Flash::Buffer, Letter.ID(), Accidental.ID(), tmp);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LetterClass + AccidentalClass + Octave + Format

	char* Flash::GetName(char* buff, const Pitch::Letter& Letter, const Pitch::Accidental& Accidental, int8_t octave, const TextFormat::FormatClass& Format)
	{
        return GetName(buff, Letter.ID(), Accidental.ID(), octave, Format);
	}

	const char* Flash::GetName(const Pitch::Letter& Letter, const Pitch::Accidental& Accidental, int8_t octave, const TextFormat::FormatClass& Format)
	{

        return GetName(Flash::Buffer, Letter.ID(), Accidental.ID(), octave, Format);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LetterType + AccidentalType + Format

	char* Flash::GetName(char* buff, const Pitch::Letter::LetterType& Letter, const Pitch::Accidental::AccidentalType& Accidental, const TextFormat::FormatClass& Format)
	{
		TextFormat::FormatClass tmp = Format;
        tmp.Octave_Disabled();

		return GetName(buff,Letter,Accidental,0,tmp);
	}

	const char* Flash::GetName(const Pitch::Letter::LetterType& Letter, const Pitch::Accidental::AccidentalType& Accidental, const TextFormat::FormatClass& Format)
	{
		TextFormat::FormatClass tmp = Format;
        tmp.Octave_Disabled();
        
		return GetName(Flash::Buffer,Letter,Accidental,0,tmp);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LetterType + AccidentalType + Octave + Format

	char* Flash::GetName(char* buff, const Pitch::Letter::LetterType& Letter, const Pitch::Accidental::AccidentalType& Accidental, int8_t Octave, const TextFormat::FormatClass& Format)
	{
		if((Letter == Pitch::Letter::InvalidID)||(Accidental < Pitch::Accidental::MinIterator)||(Accidental > Pitch::Accidental::MaxIterator)){buff[0] = '\0'; return buff;}

		cpstd::string OutputStr;

		switch(Format.SpacingMode())
		{
			
			case TextFormat::SpacingMode::Justified:
			{
				OutputStr = Flash::GetLetterText(Letter);

				if (Format.AccidentalMode() == TextFormat::AccidentalMode::Text)
				{
					OutputStr += " ";
				}

				OutputStr += Flash::GetAccidentalText(Accidental, Format);
				

				if(Format.AccidentalMode() == TextFormat::AccidentalMode::Symbol)
				{
					switch(Accidental)
					{
						case Pitch::Accidental::Natural:
							OutputStr += " ";
							[[fallthrough]];
						case Pitch::Accidental::Flat:
						case Pitch::Accidental::Sharp:
							OutputStr += " ";
							[[fallthrough]];
	                    case Pitch::Accidental::DoubleFlat:
	                    case Pitch::Accidental::DoubleSharp:
							OutputStr += " ";
						break;
					}
				}
				else
				{
					switch(Accidental)
					{
						case Pitch::Accidental::Flat:
							OutputStr += " ";
							[[fallthrough]];
						case Pitch::Accidental::Sharp:
							OutputStr += "  ";
							[[fallthrough]];
						case Pitch::Accidental::Natural:
							if(Format.NaturalMode() == MusicCompositionCore::Disabled)
							{
								OutputStr += "       ";
							}
							OutputStr += "    ";
							[[fallthrough]];
	                    case Pitch::Accidental::DoubleFlat:
	                    case Pitch::Accidental::TripleFlat:
							OutputStr += " ";
							[[fallthrough]];
	                    case Pitch::Accidental::DoubleSharp:
	                    case Pitch::Accidental::TripleSharp:
							OutputStr += " ";
							[[fallthrough]];
	                    case Pitch::Accidental::QuadrupleFlat:
							OutputStr += "   ";
							[[fallthrough]];
	                    case Pitch::Accidental::QuadrupleSharp:
							OutputStr += " ";
						break;
					}
				}

	            if(Format.OctaveMode() == TextFormat::OctaveMode::Enabled)
				{
					uint8_t max_chars = 3;

					if(Octave >= 0)
					{
						OutputStr += " ";
						max_chars = 2;
					}

					OutputStr += Octave;

					for(uint8_t i = cpstd::string(Octave).length(); i<max_chars; i++)
					{
						OutputStr += " ";
					}
				}
			}
			break;
			
			case TextFormat::SpacingMode::Enabled:
			{

				OutputStr = Flash::GetLetterText(Letter);

				if (Format.AccidentalMode() == TextFormat::AccidentalMode::Text)
				{
					OutputStr += " ";
				}

				OutputStr += Flash::GetAccidentalText(Accidental, Format);

				if (Format.OctaveMode() == TextFormat::OctaveMode::Enabled)
				{
					OutputStr += " ";
					OutputStr += Octave;
				}
			}
			break;
			
			case TextFormat::SpacingMode::Disabled:
			{
				OutputStr = Flash::GetLetterText(Letter);
		
				if (Format.AccidentalMode() == TextFormat::AccidentalMode::Text)
				{
					OutputStr += " ";
				}

				OutputStr += Flash::GetAccidentalText(Accidental, Format);

				if(Format.OctaveMode() == TextFormat::OctaveMode::Enabled)
				{
					OutputStr += cpstd::string(Octave,10);
				}
			}
			break;
		}
	

		//Serial.println(OutputStr);

		for (uint8_t i = 0; i < OutputStr.size(); i++)
		{
			buff[i] = OutputStr.at(i);
		}

		buff[OutputStr.size()] = '\0';

		return buff;
	}

	const char* Flash::GetName(const Pitch::Letter::LetterType& Letter, const Pitch::Accidental::AccidentalType& Accidental, int8_t octave, const TextFormat::FormatClass& Format)
    {
        return GetName(Flash::Buffer, Letter,Accidental,octave,Format);
    }
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get Accidental Name
    
	char* Flash::GetAccidentalText(char* buff, const Pitch::Accidental& Accidental, const TextFormat::FormatClass& Format)
	{
	    #if defined(__AVR__)
	        if((Accidental == Pitch::Accidental::Natural) && (Format.NaturalMode() == TextFormat::NaturalMode::Enabled) && (Format.AccidentalMode() == TextFormat::AccidentalMode::Symbol))
	        {
	        	buff[0] = '\0';
	        }
	        else
	        {
				strcpy_P(buff, (PGM_P)pgm_read_word(&(AccidentalNames[Accidental.ID() + 4][Format.AccidentalMode()])));
	        }
	    #else
	        if(((Accidental == Pitch::Accidental::Natural) && (Format.NaturalMode() == TextFormat::NaturalMode::Enabled) && (Format.AccidentalMode() == TextFormat::AccidentalMode::Symbol)) || (Accidental == Pitch::Accidental::InvalidID) )
	        {
	        	buff[0] = '\0';
	        }
	        else
	        {
	            strcpy(buff, AccidentalNames[Accidental.ID() + 4][Format.AccidentalMode()]);
	        }
	    #endif

	    return buff;
	}

	const char* Flash::GetAccidentalText(const Pitch::Accidental& Accidental, const TextFormat::FormatClass& Format)
	{
	    return GetAccidentalText(Flash::Buffer, Accidental, Format);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get Letter Name

	char* Flash::GetLetterText(char* buff, const Pitch::Letter& letter)
	{
	    #if defined(__AVR__)
	        memcpy_P(buff,  (PGM_P)pgm_read_word(&(NoteNames[letter.ID()])), 1 );
	    #else
	        memcpy(buff, NoteNames[letter.ID()], 1);
	    #endif
		
		buff[1] = '\0';
	    
		return buff;
	}

	const char* Flash::GetLetterText(const Pitch::Letter& letter)
	{
	    return GetLetterText(Flash::Buffer, letter);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
