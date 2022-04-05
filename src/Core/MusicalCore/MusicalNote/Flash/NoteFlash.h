#ifndef MCC_MUSICAL_NOTE_FLASH_H
#define MCC_MUSICAL_NOTE_FLASH_H

    #include <MCC_BuildSettings.h>
    #include <CPString.h>

    #include "NoteFlash_Definitions.h"

    #include "../TextFormat/TextFormat.h"
    #include "../Pitch/NotePitch.h"
    #include "../Note_Class.h"

    namespace MusicCompositionCore
    {
        namespace Core
        {
            namespace MusicalCore
            {
                namespace MusicalNote
                {
                    class Note;
                          
                    namespace Flash
                    {
                        extern char Buffer[24];

                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Get Name

                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // Note + Format
                            
                                char* GetName(char* buff, const Note& source, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                                const char* GetName(const Note& source, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // PitchClass + Format
                                
                                char* GetName(char* buff, const Pitch& source, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                                const char* GetName(const Pitch& source, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // PitchClass + Octave + Format
                            
                                char* GetName(char* buff, const Pitch& source, int8_t octave, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                                const char* GetName(const Pitch& source, int8_t octave, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // LetterClass + AccidentalClass + Format
                            
                                char* GetName(char* buff, const Pitch::Letter& note, const MusicalNote::Pitch::Accidental& accidental, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                                const char* GetName(const MusicalNote::Pitch::Letter& note, const MusicalNote::Pitch::Accidental& accidental, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // LetterClass + AccidentalClass + Octave + Format
                            
                                char* GetName(char* buff, const Pitch::Letter& note, const MusicalNote::Pitch::Accidental& accidental, int8_t octave, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                                const char* GetName(const MusicalNote::Pitch::Letter& note, const MusicalNote::Pitch::Accidental& accidental, int8_t octave, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // LetterType + AccidentalType + Format

                                char* GetName(char* buff, const Pitch::Letter::LetterType& note, const Pitch::Accidental::AccidentalType& accidental, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                                const char* GetName(const Pitch::Letter::LetterType& note, const Pitch::Accidental:: AccidentalType& accidental, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // LetterType + AccidentalType + Octave + Format

                                char* GetName(char* buff, const Pitch::Letter::LetterType& note, const Pitch::Accidental::AccidentalType& accidental, int8_t octave, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                                const char* GetName(const Pitch::Letter::LetterType& note, const Pitch::Accidental::AccidentalType& accidental, int8_t octave, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Get Accidental Name

                            char* GetAccidentalText(char* buff, const MusicalNote::Pitch::Accidental& accidental, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                            const char* GetAccidentalText(const MusicalNote::Pitch::Accidental& accidental, const TextFormat::FormatClass& format = TextFormat::DefaultFormat);
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Get Letter Name

                            char* GetLetterText(char* buff, const MusicalNote::Pitch::Letter& letter);
                            const char* GetLetterText(const MusicalNote::Pitch::Letter& letter);
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    }
                }
            }
        }
    }

   namespace MCC_MusicalNoteFlash = MusicCompositionCore::Core::MusicalCore::MusicalNote::Flash;  

#endif//MCC_MUSICAL_NOTE_FLASH_H