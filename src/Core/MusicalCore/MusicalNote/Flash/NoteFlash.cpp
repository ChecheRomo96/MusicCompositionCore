#include "NoteFlash.h"
#include <MCC_BuildSettings.h>

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

	char* Flash::GetName(char* buff, const Pitch::PitchClass& source, const TextFormat::FormatClass& Format)
	{
		TextFormat::FormatClass tmp = Format;
        tmp.Octave_Disabled();

		return GetName(buff, source.Letter(), source.Accidental(), 0, tmp);
	}

	const char* Flash::GetName(const Pitch::PitchClass& source, const TextFormat::FormatClass& Format)
	{
		TextFormat::FormatClass tmp = Format;
		tmp.Octave_Disabled();

		return GetName(Flash::Buffer, source.Letter(), source.Accidental(), 0, tmp);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PitchClass + Octave + Format

	char* Flash::GetName(char* buff, const Pitch::PitchClass& source, int8_t octave, const TextFormat::FormatClass& Format)
	{
		return GetName(buff, source.Letter(), source.Accidental(), octave, Format);
	}

	const char* Flash::GetName(const Pitch::PitchClass& source, int8_t octave, const TextFormat::FormatClass& Format)
	{
		return GetName(Flash::Buffer, source.Letter(), source.Accidental(), octave, Format);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LetterClass + AccidentalClass + Format

	char* Flash::GetName(char* buff, const Pitch::Letter::LetterClass& Letter, const Pitch::Accidental::AccidentalClass& Accidental, const TextFormat::FormatClass& Format)
	{
        TextFormat::FormatClass tmp = Format;
        tmp.Octave_Disabled();

		return GetName(buff, Letter, Accidental, tmp);
	}

	const char* Flash::GetName(const Pitch::Letter::LetterClass& Letter, const Pitch::Accidental::AccidentalClass& Accidental, const TextFormat::FormatClass& Format)
	{
        TextFormat::FormatClass tmp = Format;
        tmp.Octave_Disabled();
        
		return GetName(Flash::Buffer, Letter, Accidental, tmp);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LetterClass + AccidentalClass + Octave + Format

	char* Flash::GetName(char* buff, const Pitch::Letter::LetterClass& Letter, const Pitch::Accidental::AccidentalClass& Accidental, int8_t octave, const TextFormat::FormatClass& Format)
	{
        return GetName(buff, Letter.ID(), Accidental.ID(), octave, Format);
	}

	const char* Flash::GetName(const Pitch::Letter::LetterClass& Letter, const Pitch::Accidental::AccidentalClass& Accidental, int8_t octave, const TextFormat::FormatClass& Format)
	{

        return GetName(Flash::Buffer, Letter.ID(), Accidental.ID(), octave, Format);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LetterType + AccidentalType + Format

	char* Flash::GetName(char* buff, const Pitch::LetterType& Letter, const Pitch::AccidentalType& Accidental, const TextFormat::FormatClass& Format)
	{
		TextFormat::FormatClass tmp = Format;
        tmp.Octave_Disabled();

		return GetName(buff,Letter,Accidental,0,tmp);
	}

	const char* Flash::GetName(const Pitch::LetterType& Letter, const Pitch::AccidentalType& Accidental, const TextFormat::FormatClass& Format)
	{
		TextFormat::FormatClass tmp = Format;
        tmp.Octave_Disabled();
        
		return GetName(Flash::Buffer,Letter,Accidental,0,tmp);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LetterType + AccidentalType + Octave + Format

	char* Flash::GetName(char* buff, const Pitch::LetterType& Letter, const Pitch::AccidentalType& Accidental, int8_t Octave, const TextFormat::FormatClass& Format)
	{
		Serial.println(F("Checkpoint A")); delay(1000);

		if((Letter == Pitch::Letter::Count)||(Accidental < Pitch::Accidental::Min)||(Accidental > Pitch::Accidental::Max)){buff[0] = '\0'; return buff;}

		Serial.println(F("Checkpoint B")); delay(1000);

		CPString::string LetterStr(Flash::GetLetterText(Letter));
		CPString::string AccidentalStr(Flash::GetAccidentalText(Accidental, Format));
		CPString::string OctaveStr(Octave);
		CPString::string SpaceStr(" ");

		CPString::string OutputStr;

		Serial.println(F("Checkpoint C")); delay(1000);

		switch(Format.SpacingMode())
		{
			
			case TextFormat::SpacingMode::Justified:
			{

				Serial.println(F("Checkpoint D.1")); delay(1000);
				OutputStr += LetterStr;

				if (Format.AccidentalMode() == TextFormat::AccidentalMode::Text)
				{
					OutputStr += SpaceStr;
				}

				OutputStr += AccidentalStr;
				

				if(Format.AccidentalMode() == TextFormat::AccidentalMode::Symbol)
				{
					switch(Accidental)
					{
						case Pitch::Accidental::Natural:
							OutputStr += SpaceStr;
						case Pitch::Accidental::Flat:
						case Pitch::Accidental::Sharp:
							OutputStr += SpaceStr;
	                    case Pitch::Accidental::DoubleFlat:
	                    case Pitch::Accidental::DoubleSharp:
							OutputStr += SpaceStr;
						break;
					}
				}
				else
				{
					switch(Accidental)
					{
						case Pitch::Accidental::Flat:

							OutputStr += SpaceStr;

						case Pitch::Accidental::Sharp:

							OutputStr += SpaceStr;
							OutputStr += SpaceStr;

						case Pitch::Accidental::Natural:

							if(Format.NaturalMode() == MusicCompositionCore::Disabled)
							{
								OutputStr += SpaceStr;
								OutputStr += SpaceStr;
								OutputStr += SpaceStr;
								OutputStr += SpaceStr;
								OutputStr += SpaceStr;
								OutputStr += SpaceStr;
								OutputStr += SpaceStr;
							}

							OutputStr += SpaceStr;
							OutputStr += SpaceStr;
							OutputStr += SpaceStr;
							OutputStr += SpaceStr;

	                    case Pitch::Accidental::DoubleFlat:
	                    case Pitch::Accidental::TripleFlat:

							OutputStr += SpaceStr;

	                    case Pitch::Accidental::DoubleSharp:
	                    case Pitch::Accidental::TripleSharp:

							OutputStr += SpaceStr;
							
	                    case Pitch::Accidental::QuadrupleFlat:

							OutputStr += SpaceStr;
							OutputStr += SpaceStr;
							OutputStr += SpaceStr;
							
	                    case Pitch::Accidental::QuadrupleSharp:

							OutputStr += SpaceStr;
							
						break;
					}
				}

	            if(Format.OctaveMode() == TextFormat::OctaveMode::Enabled)
				{
					uint8_t max_chars = 3;

					if(Octave >= 0)
					{
						OutputStr += SpaceStr;
						max_chars = 2;
					}

					OutputStr += OctaveStr;

					for(uint8_t i = OctaveStr.length(); i<max_chars; i++)
					{
						OutputStr += SpaceStr;
					}
				}
			}
			break;
			
			case TextFormat::SpacingMode::Enabled:
			{

				Serial.println(F("Checkpoint D.2")); delay(1000);
				OutputStr += LetterStr;

				if (Format.AccidentalMode() == TextFormat::AccidentalMode::Text)
				{
					OutputStr += SpaceStr;
				}

				OutputStr += AccidentalStr;

				if (Format.OctaveMode() == TextFormat::OctaveMode::Enabled)
				{
					OutputStr += SpaceStr;
					OutputStr += OctaveStr;
				}
			}
			break;
			
			case TextFormat::SpacingMode::Disabled:
			{

				Serial.println(F("Checkpoint D.3")); delay(1000);
				OutputStr += LetterStr;

				if (Format.AccidentalMode() == TextFormat::AccidentalMode::Text)
				{
					OutputStr += SpaceStr;
				}

				OutputStr += AccidentalStr;

				if(Format.OctaveMode() == TextFormat::OctaveMode::Enabled)
				{
					OutputStr += OctaveStr;
				}
			}
			break;
		}

		Serial.println(F("Checkpoint E")); delay(1000);
		
		strcpy(buff, OutputStr.c_str());
		
		Serial.println(F("Checkpoint F")); delay(1000);

		return buff;
	}

	const char* Flash::GetName(const Pitch::LetterType& Letter, const Pitch::AccidentalType& Accidental, int8_t octave, const TextFormat::FormatClass& Format)
    {
        return GetName(Flash::Buffer, Letter,Accidental,octave,Format);
    }
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get Accidental Name
    
	char* Flash::GetAccidentalText(char* buff, const Pitch::Accidental::AccidentalClass& Accidental, const TextFormat::FormatClass& Format)
	{
	    #if defined(ARDUINO)
	        if((Accidental == Pitch::Accidental::Natural) && (Format.NaturalMode() == TextFormat::NaturalMode::Enabled) && (Format.AccidentalMode() == TextFormat::AccidentalMode::Symbol))
	        {
	        	buff[0] = '\0';
	        }
	        else
	        {
				strcpy_P(buff, (PGM_P)pgm_read_word(&(AccidentalNames[Accidental + 4][Format.AccidentalMode()])));
	        }
	    #else
	        if((Accidental == Pitch::Accidental::Natural) && (Format.NaturalMode() == TextFormat::NaturalMode::Enabled) && (Format.AccidentalMode() == TextFormat::AccidentalMode::Symbol))
	        {
	        	buff[0] = '\0';
	        }
	        else
	        {
	            strcpy(buff, AccidentalNames[Accidental + 4][Format.AccidentalMode()]);
	        }
	    #endif

	    return buff;
	}

	const char* Flash::GetAccidentalText(const Pitch::Accidental::AccidentalClass& Accidental, const TextFormat::FormatClass& Format)
	{
	    return GetAccidentalText(Flash::Buffer, Accidental, Format);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get Letter Name

	char* Flash::GetLetterText(char* buff, const Pitch::Letter::LetterClass& letter)
	{
	    #if defined(ARDUINO)
	        strcpy_P(buff, (PGM_P)pgm_read_word(&(NoteNames[letter.ID()])));
	    #else
	        memcpy(buff, NoteNames[letter.ID()], 1);
	    #endif
		
		buff[1] = '\0';
	    
		return buff;
	}

	const char* Flash::GetLetterText(const Pitch::Letter::LetterClass& letter)
	{
	    return GetLetterText(Flash::Buffer, letter);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
