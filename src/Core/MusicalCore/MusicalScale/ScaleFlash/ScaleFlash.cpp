#include "ScaleFlash.h"

    char MCC_MusicalScaleFlash::Buffer[23];

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // Scale Name
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Flash Container Notes
            
            const char* MCC_MusicalScaleFlash::GetScaleName(const Container_Notes& source)
            {
                return GetScaleName(MCC_MusicalScaleFlash::Buffer, source);
            }

            char* MCC_MusicalScaleFlash::GetScaleName(char* buff, const Container_Notes& source)
            {
                #if defined(__AVR__)
                    strcpy_P(buff, (PGM_P)pgm_read_word(&(source.Name)));
                #else
                    strcpy(buff,source.Name);
                #endif

                return buff;
            }
        //
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Flash Container Mapping

            const char* MCC_MusicalScaleFlash::GetScaleName(const Container_Mapping& source)
            {
                return GetScaleName(MCC_MusicalScaleFlash::Buffer, source);
            }

            char* MCC_MusicalScaleFlash::GetScaleName(char* buff, const Container_Mapping& source)
            {

                #if defined(__AVR__)
                    strcpy_P(buff, (PGM_P)pgm_read_word(&(source.Name)));
                #else
                    strcpy(buff,source.Name);
                #endif

                return buff;
            }
        //
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // Flash Container 
                                        
            const char* MCC_MusicalScaleFlash::GetScaleName(const Container& source)
            {
                return GetScaleName(MCC_MusicalScaleFlash::Buffer, source);
            }

            char* MCC_MusicalScaleFlash::GetScaleName(char* buff, const Container& source)
            {
                const MCC_MusicalScaleFlash::Container_Notes* ptr1 = source.NotesPointer;
                const MCC_MusicalScaleFlash::Container_Mapping* ptr2 = source.MappingPointer;

                if(ptr1 != NULL)
                {
                    #if defined(__AVR__)
                        strcpy_P(buff, (PGM_P)pgm_read_word(&(ptr1->Name)));
                    #else
                        strcpy(buff,ptr1->Name);
                    #endif
                }
                else if(ptr2 != NULL)
                {
                    #if defined(__AVR__)
                        strcpy_P(buff, (PGM_P)pgm_read_word(&(ptr2->Name)));
                    #else
                        strcpy(buff,ptr2->Name);
                    #endif
                }

                return buff;
            }

                                        
            const char* MCC_MusicalScaleFlash::GetScaleName(const Container* source, uint8_t ID)
            {
                return GetScaleName(MCC_MusicalScaleFlash::Buffer, source, ID);
            }

            char* MCC_MusicalScaleFlash::GetScaleName(char* buff, const Container* source, uint8_t ID)
            {
                const MCC_MusicalScaleFlash::Container_Notes* ptr1 = source[ID].NotesPointer;
                const MCC_MusicalScaleFlash::Container_Mapping* ptr2 = source[ID].MappingPointer;

                if(ptr1 != NULL)
                {
                    #if defined(__AVR__)
                        strcpy_P(buff, (PGM_P)pgm_read_word(&(ptr1->Name)));
                    #else
                        strcpy(buff,ptr1->Name);
                    #endif
                }
                else if(ptr2 != NULL)
                {
                    #if defined(__AVR__)
                        strcpy_P(buff, (PGM_P)pgm_read_word(&(ptr2->Name)));
                    #else
                        strcpy(buff,ptr2->Name);
                    #endif
                }

                return buff;
            }
        //
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // ID (Flash Scales Array) 
                                    
            const char* MCC_MusicalScaleFlash::GetScaleName(uint8_t ID)
            {
                return GetScaleName(MCC_MusicalScaleFlash::Buffer, ID);
            }

            char* MCC_MusicalScaleFlash::GetScaleName(char* buff,uint8_t ScaleFlashID)
            {
                const MCC_MusicalScaleFlash::Container_Notes* ptr1 = MCC_MusicalScaleFlash::ScaleArrays::Flash[ScaleFlashID].NotesPointer;
                const MCC_MusicalScaleFlash::Container_Mapping* ptr2 = MCC_MusicalScaleFlash::ScaleArrays::Flash[ScaleFlashID].MappingPointer;

                if(ptr1 != NULL)
                {
                    #if defined(__AVR__)
                        strcpy_P(buff, (PGM_P)pgm_read_word(&(ptr1->Name)));
                    #else
                        strcpy(buff,ptr1->Name);
                    #endif
                }
                else if(ptr2 != NULL)
                {
                    #if defined(__AVR__)
                        strcpy_P(buff, (PGM_P)pgm_read_word(&(ptr2->Name)));
                    #else
                        strcpy(buff,ptr2->Name);
                    #endif
                }
                return buff;
            }

            const char* MCC_MusicalScaleFlash::GetScaleName(const MCC_MusicalNote::Pitch& root, uint8_t ScaleID)
            {
                return GetScaleName(MCC_MusicalScaleFlash::Buffer, root, ScaleID);
            }

            char* MCC_MusicalScaleFlash::GetScaleName(char* buff, const MCC_MusicalNote::Pitch& root, uint8_t ScaleID)
            {
                if(ScaleID>=MCC_MusicalScaleFlash::ScaleArrays::Flash_Size){return buff;}
                
                MCC_MusicalNote::TextFormat::FormatClass format(MCC_MusicalNote::TextFormat::AccidentalMode::Symbol, MCC_MusicalNote::TextFormat::OctaveMode::Disabled, MCC_MusicalNote::TextFormat::SpacingMode::Disabled);
                
                strcpy(buff,root.Name(format));

                uint8_t offset = strlen(root.Name(format)); 
                buff[offset] = ' ';

                #if defined(__AVR__)

                    if(MCC_MusicalScaleFlash::ScaleArrays::Flash[ScaleID].NotesPointer!=NULL)
                    {
                        const MCC_MusicalScale::Flash::Container_Notes* pointer = MCC_MusicalScaleFlash::ScaleArrays::Flash[ScaleID].NotesPointer;
                        strcpy_P(buff+offset+1, (PGM_P)pgm_read_word(&(pointer->Name)));
                    }
                    else
                    {
                        const MCC_MusicalScale::Flash::Container_Mapping* pointer = MCC_MusicalScaleFlash::ScaleArrays::Flash[ScaleID].MappingPointer;
                        strcpy_P(buff+offset+1, (PGM_P)pgm_read_word(&(pointer->Name)));
                        
                    }
                
                #else
                
                    if(MCC_MusicalScaleFlash::ScaleArrays::Flash[ScaleID].NotesPointer != NULL)
                    {
                        strcpy(buff+offset+1,MCC_MusicalScaleFlash::ScaleArrays::Flash[ScaleID].NotesPointer->Name);
                    }
                    else
                    {
                        strcpy(buff+offset+1,MCC_MusicalScaleFlash::ScaleArrays::Flash[ScaleID].MappingPointer->Name);
                    }

                #endif
                
                return buff;
            }
        //
        ///////////////////////////////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // Scale ID

        uint8_t MCC_MusicalScaleFlash::GetScaleID(const Container_Notes& source)
        {
            #if defined(__AVR__)
                return pgm_read_byte(&(source.ID));
            #else
                return source.ID;
            #endif
        }

        uint8_t MCC_MusicalScaleFlash::GetScaleID(const Container_Mapping& source)
        {
            #if defined(__AVR__)
                return pgm_read_byte(&(source.ID));
            #else
                return source.ID;
            #endif
        }

        uint8_t MCC_MusicalScaleFlash::GetScaleID(const Container& source)
        {
            const MCC_MusicalScaleFlash::Container_Notes* ptr1 = source.NotesPointer;
            const MCC_MusicalScaleFlash::Container_Mapping* ptr2 = source.MappingPointer;

            if(ptr1 != NULL)
            {
                #if defined(__AVR__)
                    return pgm_read_byte(&(ptr1->ID));
                #else
                    return ptr1->ID;
                #endif
            }
            else if(ptr2 != NULL)
            {
                #if defined(__AVR__)
                    return pgm_read_byte(&(ptr2->ID));
                #else
                    return ptr2->ID;
                #endif
            }
            return 0;
        }   

        uint8_t MCC_MusicalScaleFlash::GetScaleID(const Container* container, uint8_t ID)
        {
            const MCC_MusicalScaleFlash::Container_Notes* ptr1 = container[ID].NotesPointer;
            const MCC_MusicalScaleFlash::Container_Mapping* ptr2 = container[ID].MappingPointer;

            if(ptr1 != NULL)
            {
                #if defined(__AVR__)
                    return pgm_read_byte(&(ptr1->ID));
                #else
                    return ptr1->ID;
                #endif
            }
            else if(ptr2 != NULL)
            {
                #if defined(__AVR__)
                    return pgm_read_byte(&(ptr2->ID));
                #else
                    return ptr2->ID;
                #endif
            }
            return 0;
        }   
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // Scale Properties

        uint8_t MCC_MusicalScaleFlash::GetScaleProperties(const Container_Notes& source)
        {
            #if defined(__AVR__)
                return pgm_read_byte(&(source.Properties));
            #else
                return source.Properties;
            #endif
        }

        uint8_t MCC_MusicalScaleFlash::GetScaleProperties(const Container_Mapping& source)
        {
            #if defined(__AVR__)
                return pgm_read_byte(&(source.Properties));
            #else
                return source.Properties;
            #endif
        }

        uint8_t MCC_MusicalScaleFlash::GetScaleProperties(const Container& source)
        {
            const MCC_MusicalScaleFlash::Container_Notes* ptr1 = source.NotesPointer;
            const MCC_MusicalScaleFlash::Container_Mapping* ptr2 = source.MappingPointer;

            if(ptr1 != NULL)
            {
                #if defined(__AVR__)
                    return pgm_read_byte(&(ptr1->Properties));
                #else
                    return ptr1->Properties;
                #endif
            }
            else if(ptr2 != NULL)
            {
                #if defined(__AVR__)
                    return pgm_read_byte(&(ptr2->Properties));
                #else
                    return ptr2->Properties;
                #endif
            }
            return 0;
        }

        uint8_t MCC_MusicalScaleFlash::GetScaleProperties(const Container* container, uint8_t ID)
        {

            const MCC_MusicalScaleFlash::Container_Notes* ptr1 = container[ID].NotesPointer;
            const MCC_MusicalScaleFlash::Container_Mapping* ptr2 = container[ID].MappingPointer;

            #if defined(__AVR__)
            
                if(ptr1 != NULL)
                {
                    return pgm_read_byte(&ptr1->Properties);
                }
                else if(ptr2 != NULL)
                {
                    return pgm_read_byte(&ptr2->Properties);
                }


            #else

                if(ptr1 != NULL)
                {
                    return ptr1->Properties;
                }
                else if(ptr2 != NULL)
                {
                    return ptr2->Properties;
                }

            #endif

            
            return 0;
        }

        uint8_t MCC_MusicalScaleFlash::GetScaleProperties(uint8_t ID)
        {

            const MCC_MusicalScaleFlash::Container_Notes* ptr1 = ScaleArrays::Flash[ID].NotesPointer;
            const MCC_MusicalScaleFlash::Container_Mapping* ptr2 = ScaleArrays::Flash[ID].MappingPointer;

            #if defined(__AVR__)
            
                if(ptr1 != NULL)
                {
                    return pgm_read_byte(&ptr1->Properties);
                }
                else if(ptr2 != NULL)
                {
                    return pgm_read_byte(&ptr2->Properties);
                }


            #else

                if(ptr1 != NULL)
                {
                    return ptr1->Properties;
                }
                else if(ptr2 != NULL)
                {
                    return ptr2->Properties;
                }

            #endif

            
            return 0;
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // Scale Mapping

        uint16_t MCC_MusicalScaleFlash::GetScaleMapping(const Container_Mapping& source)
        {
            #if defined(__AVR__)
                return pgm_read_word(&(source.Mapping));
            #else
                return source.Mapping;
            #endif
        }

        uint16_t MCC_MusicalScaleFlash::GetScaleMapping(const Container& source)
        {
            const MCC_MusicalScaleFlash::Container_Mapping* ptr = source.MappingPointer;

            #if defined(__AVR__)
            
                if(ptr != NULL)
                {
                    return pgm_read_word(&ptr->Mapping);
                }

            #else

                if(ptr != NULL)
                {
                    return ptr->Mapping;
                }

            #endif
            
            return 0;
        }

        uint16_t MCC_MusicalScaleFlash::GetScaleMapping(const Container* container, uint8_t ID)
        {
            const MCC_MusicalScaleFlash::Container_Mapping* ptr = container[ID].MappingPointer;

            #if defined(__AVR__)
            
                if(ptr != NULL)
                {
                    return pgm_read_word(&ptr->Mapping);
                }

            #else

                if(ptr != NULL)
                {
                    return ptr->Mapping;
                }

            #endif
            
            return 0;
        }

        uint16_t MCC_MusicalScaleFlash::GetScaleMapping(uint8_t ID)
        {
            const MCC_MusicalScaleFlash::Container_Mapping* ptr = MCC_MusicalScaleFlash::ScaleArrays::Flash[ID].MappingPointer;

            if(ptr != NULL)
            {
                #if defined(__AVR__)
                    return pgm_read_word(&ptr->Mapping);
                #else
                    return ptr->Mapping;
                #endif
                
            }
            return 0;
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // Generic Interval

        uint8_t MCC_MusicalScaleFlash::GetScaleGenericInterval(const Container_Mapping& source, uint8_t x)
        {
            #if defined(__AVR__)
                uint8_t* array = pgm_read_word(&source.GenericInterval);
                return pgm_read_byte(&array[x]);  
            #else
                return source.GenericInterval[x];
            #endif
        }

        uint8_t MCC_MusicalScaleFlash::GetScaleGenericInterval(const Container& source, uint8_t x)
        {
            const MCC_MusicalScaleFlash::Container_Mapping* ptr = source.MappingPointer;

            #if defined(__AVR__)
            
                if(ptr != NULL)
                {
                    uint8_t* array = pgm_read_word(&ptr->GenericInterval);
                    return pgm_read_byte(&array[x]);  
                }

            #else

                if(ptr != NULL)
                {
                    return ptr->GenericInterval[x];
                }

            #endif
            
            return 0;
        }

        uint8_t MCC_MusicalScaleFlash::GetScaleGenericInterval(const Container* source, uint8_t ID, uint8_t x)
        {
            const MCC_MusicalScaleFlash::Container_Mapping* ptr = source[ID].MappingPointer;

            #if defined(__AVR__)
            
                if(ptr != NULL)
                {
                    uint8_t* array = pgm_read_word(&ptr->GenericInterval);
                    return pgm_read_byte(&array[x]);  
                }

            #else

                if(ptr != NULL)
                {
                    return ptr->GenericInterval[x];
                }

            #endif
            
            return 0;
        }

        uint8_t MCC_MusicalScaleFlash::GetScaleGenericInterval(uint8_t ID, uint8_t x)
        {
            const MCC_MusicalScaleFlash::Container_Mapping* ptr = MCC_MusicalScaleFlash::ScaleArrays::Flash[ID].MappingPointer;

            if(ptr != NULL)
            {

                #if defined(__AVR__)
                    uint8_t* array = pgm_read_word(&ptr->GenericInterval);
                    return pgm_read_byte(&array[x]);                
                #else
                    return ptr->GenericInterval[x]; 
                #endif
                    
            }
            return 0;
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // Note Token

        uint8_t MCC_MusicalScaleFlash::GetScaleNoteToken(const Container_Notes& source, uint8_t x)
        {
            #if defined(__AVR__)
                uint8_t* array = pgm_read_word(&source.NoteTokens);
                return pgm_read_byte(&array[x]);  
            #else
                return source.NoteTokens[x];
            #endif
        }

        uint8_t MCC_MusicalScaleFlash::GetScaleNoteToken(const Container& source, uint8_t x)
        {
            const MCC_MusicalScaleFlash::Container_Notes* ptr = source.NotesPointer;

            #if defined(__AVR__)
            
                if(ptr != NULL)
                {
                    uint8_t* array = pgm_read_word(&ptr->NoteTokens);
                    return pgm_read_byte(&array[x]);  
                }

            #else

                if(ptr != NULL)
                {
                    return ptr->NoteTokens[x];
                }

            #endif
            
            return 0;
        }

        uint8_t MCC_MusicalScaleFlash::GetScaleNoteToken(const Container* source, uint8_t ID, uint8_t x)
        {
            const MCC_MusicalScaleFlash::Container_Notes* ptr = source[ID].NotesPointer;

            #if defined(__AVR__)
            
                if(ptr != NULL)
                {
                    uint8_t* array = pgm_read_word(&ptr->NoteTokens);
                    return pgm_read_byte(&array[x]);  
                }

            #else

                if(ptr != NULL)
                {
                    return ptr->NoteTokens[x];
                }

            #endif
            
            return 0;
        }

        uint8_t MCC_MusicalScaleFlash::GetScaleNoteToken(uint8_t ScaleFlashID, uint8_t x)
        {
            const MCC_MusicalScaleFlash::Container_Notes* ptr1 = MCC_MusicalScaleFlash::ScaleArrays::Flash[ScaleFlashID].NotesPointer;
            

            if(ptr1 != NULL)
            {
                #if defined(__AVR__)
                    uint8_t* array = pgm_read_word(&ptr1->NoteTokens);
                    return pgm_read_byte(&array[x]);      
                #else
                    return ptr1->NoteTokens[x];
                #endif
            }
            return 0;
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
