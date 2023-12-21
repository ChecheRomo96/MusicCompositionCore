#ifndef MCC_SCALE_PROPERTIES_DEFINITIONS_H
#define MCC_SCALE_PROPERTIES_DEFINITIONS_H

	namespace MusicCompositionCore
	{
    	namespace MusicalCore
   		{
   			namespace MusicalScale
   			{
				namespace ScaleProperties
				{
					/////////////////////////////////////////////////////////////
					// Notes Mode
					//
					// Fixed Mapping: ScaleMapping will remain the same, this
					// 				  means you'll have the same intervals
					// 				  as you change the root note.
					//
					// Dynamic Mapping: ScaleMapping will change , this menas
					// 				   	you'll have the same notes but different
					// 				  	intervals as you change the root note.

						namespace MappingMode
						{
							static constexpr bool Fixed = 0u;
							static constexpr uint8_t Fixed_Mapping = 0b0;

							static constexpr bool Dynamic = 1u;
							static constexpr uint8_t Dynamic_Mapping = 0b1;

							static constexpr uint8_t bitshift = 0u;
						}
					//
					/////////////////////////////////////////////////////////////
					// Scale Location
					//
					//	This flag is used to determine wether the scale was built
					//	from flash, EEPROM, or if it was user created.
					//
					//	Flash: Scales stored on flash
					//
					//	EEPROM: Scales stored on EEPROM
					//
					//	A Scale is considered user created when:
					//	
					//	-It has an user appended name
					//	-The scale mapping has been modified
					//	-The note mode has been modified
					//

						namespace Location
						{
							static constexpr uint8_t None = 0u;
							static constexpr uint8_t None_Mapping = 0b00;

							static constexpr uint8_t Flash = 1u;
							static constexpr uint8_t Flash_Mapping = 0b10;

							static constexpr uint8_t EEPROM = 2u;
							static constexpr uint8_t EEPROM_Mapping = 0b100;

							static constexpr uint8_t bitshift = 1u;
						}
					//
					/////////////////////////////////////////////////////////////
					//  Name Flag
					//
					//	This flag is used to determine wether the scale has an
					//	user defined name. 

						namespace NameFlag
						{
							static constexpr bool System = 0u;
							static constexpr uint8_t System_Mapping = 0b0000;

							static constexpr bool User = 1u;
							static constexpr uint8_t User_Mapping = 0b1000;

							static constexpr uint8_t bitshift = 3u;
						}
					//
					/////////////////////////////////////////////////////////////
				}
			}
   		}
    }

#endif//MCC_SCALE_PROPERTIES_DEFINITIONS_H
