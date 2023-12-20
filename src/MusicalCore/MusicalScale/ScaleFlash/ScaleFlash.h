   #ifndef MCC_MUSICAL_SCALE_FLASH_H
#define MCC_MUSICAL_SCALE_FLASH_H

    #include <MCC_BuildSettings.h>

    #include "ScaleFlash_Definitions.h"

    #include "../MusicalScale.h"
    #include "ScaleDefinitions/ScaleDefinitions.h"

    namespace MusicCompositionCore
    {
        namespace Core
        {
            namespace MusicalCore
            {
                namespace MusicalScale
                {
                    namespace Flash
                    {
                        extern char Buffer[23];
                        
                        ////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Name

                            ////////////////////////////////////////////////////////////////////////////////////////////////////
                            // Fills char Buffer[23] and returns a pointer to it

                                const char* GetScaleName(const MCC_MusicalNote::Pitch& root, uint8_t ScaleID);
                                const char* GetScaleName(const Container_Notes& source);
                                const char* GetScaleName(const Container_Mapping& source);
                                const char* GetScaleName(const Container& source);
                                const char* GetScaleName(const Container* source, uint8_t ID);
                                const char* GetScaleName(uint8_t ID);
                            //
                            ////////////////////////////////////////////////////////////////////////////////////////////////////
                            // Fills buff and returns a pointer to it

                                char* GetScaleName(char* buff, const MCC_MusicalNote::Pitch& root, uint8_t ScaleID);
                                char* GetScaleName(char* buff, const Container_Notes& source);
                                char* GetScaleName(char* buff, const Container_Mapping& source);
                                char* GetScaleName(char* buff, const Container& source);
                                char* GetScaleName(char* buff, const Container* source, uint8_t ID);
                                char* GetScaleName(char* buff, uint8_t ID);
                            //
                            ////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // ID

                            uint8_t GetScaleID(const Container_Notes& source);
                            uint8_t GetScaleID(const Container_Mapping& source);
                            uint8_t GetScaleID(const Container& source);
                            uint8_t GetScaleID(const Container* source, uint8_t ID);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Properties

                            uint8_t GetScaleProperties(const Container_Notes& source);
                            uint8_t GetScaleProperties(const Container_Mapping& source);
                            uint8_t GetScaleProperties(const Container& source);
                            uint8_t GetScaleProperties(const Container* container, uint8_t ID);
                            uint8_t GetScaleProperties(uint8_t ID);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Mapping

                            uint16_t GetScaleMapping(const Container_Mapping& source);
                            uint16_t GetScaleMapping(const Container& source);
                            uint16_t GetScaleMapping(const Container* source, uint8_t ID);
                            uint16_t GetScaleMapping(uint8_t ID);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Generic Interval

                            uint8_t GetScaleGenericInterval(const Container_Mapping& source, uint8_t x);
                            uint8_t GetScaleGenericInterval(const Container& source, uint8_t x);
                            uint8_t GetScaleGenericInterval(const Container* source, uint8_t ID, uint8_t x);
                            uint8_t GetScaleGenericInterval(uint8_t ID, uint8_t x);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Note Token

                            uint8_t GetScaleNoteToken(const Container_Notes& source, uint8_t x);
                            uint8_t GetScaleNoteToken(const Container& source, uint8_t x);
                            uint8_t GetScaleNoteToken(const Container* source, uint8_t ID, uint8_t x);
                            uint8_t GetScaleNoteToken(uint8_t ID, uint8_t x);
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////////////////////

                    }
                }
            }
        }
    }

    namespace MCC_MusicalScaleFlash = MusicCompositionCore::Core::MusicalCore::MusicalScale::Flash;

#endif//MCC_MUSICAL_SCALE_FLASH_H
