#ifndef MCC_MUSICAL_NOTE_FLASH_DEFINITIONS_H
#define MCC_MUSICAL_NOTE_FLASH_DEFINITIONS_H

	#include <MCC_BuildSettings.h>

	namespace MusicCompositionCore
	{
        namespace Core
        {
        	namespace MusicalCore
       		{
       			namespace MusicalNote
       			{
       				namespace Flash
       				{
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					    // Note Names

						    const char C_Char PROGMEM_MACRO = 'C';
							const char D_Char PROGMEM_MACRO = 'D';
							const char E_Char PROGMEM_MACRO = 'E';
							const char F_Char PROGMEM_MACRO = 'F';
							const char G_Char PROGMEM_MACRO = 'G';
							const char A_Char PROGMEM_MACRO = 'A';
							const char B_Char PROGMEM_MACRO = 'B';
							
							const char * const NoteNames[7] PROGMEM_MACRO = {&C_Char,&D_Char,&E_Char,&F_Char,&G_Char,&A_Char,&B_Char};
						//
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						// Accidental Names

                            const char QuadrupleFlat_Str[] PROGMEM_MACRO = {'Q','u','a','d','r','u','p','l','e',' ','F','l','a','t','\0'};
                            const char QuadrupleFlat_Simbol[] PROGMEM_MACRO = {'b','b','b','b','\0'};
                        
                            const char TripleFlat_Str[] PROGMEM_MACRO = {'T','r','i','p','l','e',' ','F','l','a','t','\0'};
                            const char TripleFlat_Simbol[] PROGMEM_MACRO = {'b','b','b','\0'};
                        
                            const char DoubleFlat_Str[] PROGMEM_MACRO = {'D','o','u','b','l','e',' ','F','l','a','t','\0'};
                            const char DoubleFlat_Simbol[] PROGMEM_MACRO = {'b','b','\0'};

							const char Flat_Str[] PROGMEM_MACRO = {'F','l','a','t','\0'};
							const char Flat_Simbol[] PROGMEM_MACRO = {'b','\0'};

							const char Natural_Str[] PROGMEM_MACRO = {'N','a','t','u','r','a','l','\0'};
							const char Natural_Simbol[] PROGMEM_MACRO = {'\0'};

							const char Sharp_Str[] PROGMEM_MACRO = {'S','h','a','r','p','\0'};
							const char Sharp_Simbol[] PROGMEM_MACRO = {'#','\0'};

                            const char DoubleSharp_Str[] PROGMEM_MACRO = {'D','o','u','b','l','e',' ','S','h','a','r','p','\0'};
                            const char DoubleSharp_Simbol[] PROGMEM_MACRO = {'#','#','\0'};
                        
                            const char TripleSharp_Str[] PROGMEM_MACRO = {'T','r','i','p','l','e',' ','S','h','a','r','p','\0'};
                            const char TripleSharp_Simbol[] PROGMEM_MACRO = {'#','#','#','\0'};
                        
                            const char QuadrupleSharp_Str[] PROGMEM_MACRO = {'Q','u','a','d','r','u','p','l','e',' ','S','h','a','r','p','\0'};
                            const char QuadrupleSharp_Simbol[] PROGMEM_MACRO = {'#','#','#','#','\0'};

							const char* const AccidentalNames[9][2] PROGMEM_MACRO = 
							{
                                {QuadrupleFlat_Str,QuadrupleFlat_Simbol},
                                {TripleFlat_Str,TripleFlat_Simbol},
                                {DoubleFlat_Str,DoubleFlat_Simbol},
								{Flat_Str,Flat_Simbol},
								{Natural_Str,Natural_Simbol},
								{Sharp_Str,Sharp_Simbol},
                                {DoubleSharp_Str,DoubleSharp_Simbol},
                                {TripleSharp_Str,TripleSharp_Simbol},
                                {QuadrupleSharp_Str,QuadrupleSharp_Simbol},
							};
						//	
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					}
				}
			}
		}
	}

#endif//MCC_MUSICAL_NOTE_FLASH_DEFINITIONS_H