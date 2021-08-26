#include "NoteFlash.h"
#include <MCC_BuildSettings.h>

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;
using namespace MusicCompositionCore::Core::UtilityCore;

char Flash::Buffer[24];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Note + Format

	char* GetName(char* buff, const Note& source, const NoteFormat::Format& Format)
	{
		return GetName(buff, source.Letter(), source.Accidental(), source.Octave(), Format);
	}

	const char* GetName(const Note& source, const NoteFormat::Format& Format)
	{
		return GetName(source.Letter(), source.Accidental(), source.Octave(), Format);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PitchClass + Format

	char* GetName(char* buff, const Pitch::PitchClass& source, const NoteFormat::Format& Format)
	{
		NoteFormat::Format tmp = Format;
		Format.Set_OctaveDisabled();

		return GetName(buff, source.Note(), source.Accidental(), 0, Format);
	}

	const char* GetName(const Pitch::PitchClass& source, const NoteFormat::Format& Format)
	{
		NoteFormat::Format tmp = Format;
		Format.Set_OctaveDisabled();

		return GetName(Flash::Buffer, source.Note(), source.Accidental(), 0, Format);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PitchClass + Octave + Format

	char* GetName(char* buff, const Pitch::PitchClass& source, int8_t octave, const NoteFormat::Format& Format)
	{
		NoteFormat::Format tmp = Format;
		Format.Set_OctaveDisabled();

		return GetName(buff, source.Note(), source.Accidental(), octave, Format);
	}

	const char* GetName(const Pitch::PitchClass& source, int8_t octave, const NoteFormat::Format& Format)
	{
		NoteFormat::Format tmp = Format;
		Format.Set_OctaverDisabled();

		return GetName(buff, source.Note(), source.Accidental(), octave, Format);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LetterClass + AccidentalClass + Format

	char* GetName(char* buff, const Pitch::Letter::LetterClass& Letter, const Pitch::Accidental::AccidentalClass& Accidental, const NoteFormat::Format& Format);
	const char* GetName(const Pitch::Letter::LetterClass& Letter, const Pitch::Accidental::AccidentalClass& Accidental, const NoteFormat::Format& Format);
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LetterClass + AccidentalClass + Octave + Format

	char* GetName(char* buff, const Pitch::Letter::LetterClass& Letter, const Pitch::Accidental::AccidentalClass& Accidental, int8_t octave, const NoteFormat::Format& Format
	{
		return GetName(Flash::Buffer, Letter, Accidental, octave, Format);
	}

	const char* GetName(const Pitch::Letter::LetterClass& Letter, const Pitch::Accidental::AccidentalClass& Accidental, int8_t octave, const NoteFormat::Format& Format);
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LetterType + AccidentalType + Format

	char* GetName(char* buff, const Pitch::LetterType& Letter, const Pitch::AccidentalType& Accidental, const NoteFormat::Format& Format);
	const char* GetName(const Pitch::LetterType& Letter, const Pitch::AccidentalType& Accidental, const NoteFormat::Format& Format);
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LetterType + AccidentalType + Octave + Format

	char* GetName(char* buff, const Pitch::LetterType& Letter, const Pitch::AccidentalType& Accidental, int8_t octave, const NoteFormat::Format& Format)
	{
		if((Letter == Pitch::Letter::Count)||(Accidental < Pitch::Accidental::Min)||(Accidental > Pitch::Accidental::Max)){buff[0] = '\0'; return buff;}
	    
		switch(Format.SpaceMode())
		{
			
			case NoteFormat::SpaceJustified:
			{
				#if defined(ARDUINO_IDE)
					buff[0] = pgm_read_byte(pgm_read_word(&NoteNames[Letter.ID()]));
					if((Accidental == Pitch::Accidental::Natural) && (Format.NaturalMode() == MusicCompositionCore::Disabled)){}
					else
					{
						strcpy_P(buff + 1, (PGM_P)pgm_read_word(&(AccidentalNames[Accidental.ID() + 4][Format.AccidentalMode()])));
					}	
				#else
					buff[0] = NoteNames[Letter.ID()][0];
					if((Accidental == Pitch::Accidental::Natural) && (Format.NaturalMode() == MusicCompositionCore::Disabled)){}
					else
					{
						strcpy(buff + 1, AccidentalNames[Accidental.ID() + 4][Format.AccidentalMode()]);
					}
				#endif
				
				uint8_t offset;

				if(Format.AccidentalMode() == NoteFormat::AccidentalShort)
				{
					switch(Accidental.ID())
					{
						case Pitch::Accidental::Natural:
							buff[1] = ' ';
						case Pitch::Accidental::Flat:
						case Pitch::Accidental::Sharp:
							buff[2] = ' ';
	                    case Pitch::Accidental::DoubleFlat:
	                    case Pitch::Accidental::DoubleSharp:
							buff[3] = ' ';
						break;
					}
					offset = 4;
				}
				else
				{
					switch(Accidental.ID())
					{
						case Pitch::Accidental::Flat:
							buff[5] = ' ';
						case Pitch::Accidental::Sharp:
							buff[6] = ' ';
							buff[7] = ' ';
						case Pitch::Accidental::Natural:
							if(Format.NaturalMode() == MusicCompositionCore::Disabled)
							{
								buff[1] = ' ';
								buff[2] = ' ';
								buff[3] = ' ';
								buff[4] = ' ';
								buff[5] = ' ';
								buff[6] = ' ';
								buff[7] = ' ';
							}
							buff[8] = ' ';
							buff[9] = ' ';
							buff[10] = ' ';
							buff[11] = ' ';
	                    case Pitch::Accidental::DoubleFlat:
	                    case Pitch::Accidental::TripleFlat:
							buff[12] = ' ';
	                    case Pitch::Accidental::DoubleSharp:
	                    case Pitch::Accidental::TripleSharp:
							buff[13] = ' ';
	                    case Pitch::Accidental::QuadrupleFlat:
	                        buff[14] = ' ';
	                        buff[15] = ' ';
	                        buff[16] = ' ';
	                    case Pitch::Accidental::QuadrupleSharp:
	                        buff[17] = ' ';
	                        
						break;
					}
					offset = 18;
				}

	            if(Format.OctaveEnabled() == NoteFormat::OctaveEnabled)
				{
	                
	                CPString::string tmp(octave);

					for(uint8_t i = 0; i<4; i++)
					{
						if(i<tmp.length())
	 					{
							buff[offset+i] = tmp[i];
						}
						else
						{
							buff[offset+i] = ' ';
						}
						buff[offset+4] = '\0';
					}
				}
				else
				{ 
					buff[offset] = '\0';
				}
			}
			break;
			
			case NoteFormat::SpaceEnabled:
			{
				#if defined(ARDUINO_IDE)
					buff[0] = pgm_read_byte(pgm_read_word(&NoteNames[Letter.ID()]));
					if((Accidental == Pitch::Accidental::Natural) && (Format.NaturalMode() == MusicCompositionCore::Disabled)){buff[1]='\0';}
					else
					{
						strcpy_P(buff + 2, (PGM_P)pgm_read_word(&(AccidentalNames[Accidental.ID() + 4][Format.AccidentalMode()])));
					}	
				#else
					buff[0] = NoteNames[Letter.ID()][0];
					if((Format.NaturalMode() == MusicCompositionCore::Disabled)&&(Accidental == Pitch::Accidental::Natural))
	                {
		                buff[1]='\0';
	                }
					else
					{
	                    buff[1] = ' ';
						strcpy(buff + 2, AccidentalNames[Accidental.ID() + 4][Format.AccidentalMode()]);
					}
				#endif


				if(Format.OctaveEnabled() == NoteFormat::OctaveEnabled)
				{
	                buff[1] = ' ';
					uint8_t offset = strlen(buff);

					buff[offset++] = ' ';
	                
	                CPString::string tmp(octave);

					for(uint8_t i = 0; i < tmp.length(); i++)
					{
						buff[offset+i] = tmp[i];
					}
					buff[offset+tmp.length()] = '\0';
				}
				else
				{ 
					buff[strlen(buff)] = '\0';
				}
			}
			break;
			
			case NoteFormat::SpaceDisabled:
			{
				
				#if defined(ARDUINO_IDE)
					buff[0] = pgm_read_byte(pgm_read_word(&NoteNames[Letter.ID()]));
					if((Accidental == Pitch::Accidental::Natural) && (Format.NaturalMode() == MusicCompositionCore::Disabled)){buff[1]='\0';}
					else
					{
						strcpy_P(buff + 1, (PGM_P)pgm_read_word(&(AccidentalNames[Accidental.ID() + 4][Format.AccidentalMode()])));
					}	
				#else
					buff[0] = NoteNames[Letter.ID()][0];
					if((Accidental == Pitch::Accidental::Natural) && (Format.NaturalMode() == MusicCompositionCore::Disabled)){buff[1]='\0';}
					else
					{
						strcpy(buff + 1, AccidentalNames[Accidental.ID() + 4][Format.AccidentalMode()]);
					}
				#endif

				if(Format.OctaveEnabled() == NoteFormat::OctaveEnabled)
				{
					uint8_t offset = strlen(buff);
	                CPString::string tmp(octave);
	                
					for(uint8_t i = 0; i < tmp.length(); i++)
					{
						buff[offset+i] = tmp[i];
					}
					buff[offset+tmp.length()] = '\0';
				}
				else
				{ 
					buff[strlen(buff)] = '\0';
				}
			}
			break;
		}
		return buff;
	}

	const char* GetName(const Pitch::LetterType& Letter, const Pitch::AccidentalType& Accidental, int8_t octave, const NoteFormat::Format& Format);
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get Accidental Name
	char* Flash::GetAccidentalName(char* buff, const Pitch::Accidental::AccidentalClass& Accidental, const NoteFormat::Format& Format)
	{
	    #if defined(ARDUINO_IDE)
	        if((Accidental == Pitch::Accidental::Natural) && (Format.NaturalMode() == MusicCompositionCore::Disabled)){}
	        else
	        {
	            strcpy_P(buff, (PGM_P)pgm_read_word(&(AccidentalNames[Accidental.ID() + 4][Format.AccidentalMode()])));
	        }
	    #else
	        if((Accidental == Pitch::Accidental::Natural) && (Format.NaturalMode() == MusicCompositionCore::Disabled)){}
	        else
	        {
	            strcpy(buff, AccidentalNames[Accidental.ID() + 4][Format.AccidentalMode()]);
	        }
	    #endif
	    return buff;
	}

	const char* Flash::GetAccidentalName(const Pitch::Accidental::AccidentalClass& Accidental, const NoteFormat::Format& Format)
	{
	    return GetAccidentalName(Flash::Buffer, Accidental, Format);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get Letter Name

	char* Flash::GetLetterName(char* buff, const Pitch::Letter::LetterClass& letter, const NoteFormat::Format& Format)
	{
	    #if defined(ARDUINO_IDE)
	        strcpy_P(buff, (PGM_P)pgm_read_word(&(NoteNames[letter.ID() + 4][Format.AccidentalMode()])));
	    #else
	        strcpy(buff, &NoteNames[letter.ID() + 4][Format.AccidentalMode()]);
	    #endif
	    return buff;
	}

	const char* Flash::GetLetterName(const Pitch::Letter::LetterClass& letter, const NoteFormat::Format& Format)
	{
	    return GetLetterName(Flash::Buffer, letter, Format);
	}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
