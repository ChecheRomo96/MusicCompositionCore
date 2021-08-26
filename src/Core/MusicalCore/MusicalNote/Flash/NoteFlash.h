#ifndef MCC_MUSICAL_NOTE_FLASH_H
#define MCC_MUSICAL_NOTE_FLASH_H

    #include <MCC_BuildSettings.h>

    #include "NoteFlash_Definitions.h"

    #include "../Format/NoteFormat.h"
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
                            
                                char* GetName(char* buff, const Note& source, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                                const char* GetName(const Note& source, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // PitchClass + Format
                                
                                char* GetName(char* buff, const Pitch::PitchClass& source, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                                const char* GetName(const Pitch::PitchClass& source, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // PitchClass + Octave + Format
                            
                                char* GetName(char* buff, const Pitch::PitchClass& source, int8_t octave, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                                const char* GetName(const Pitch::PitchClass& source, int8_t octave, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // LetterClass + AccidentalClass + Format
                            
                                char* GetName(char* buff, const Pitch::Letter::LetterClass& note, const MusicalNote::Pitch::Accidental::AccidentalClass& accidental, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                                const char* GetName(const MusicalNote::Pitch::Letter::LetterClass& note, const MusicalNote::Pitch::Accidental::AccidentalClass& accidental, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // LetterClass + AccidentalClass + Octave + Format
                            
                                char* GetName(char* buff, const Pitch::Letter::LetterClass& note, const MusicalNote::Pitch::Accidental::AccidentalClass& accidental, int8_t octave, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                                const char* GetName(const MusicalNote::Pitch::Letter::LetterClass& note, const MusicalNote::Pitch::Accidental::AccidentalClass& accidental, int8_t octave, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // LetterType + AccidentalType + Format

                                char* GetName(char* buff, const Pitch::LetterType& note, const Pitch::AccidentalType& accidental, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                                const char* GetName(const Pitch::LetterType& note, const Pitch::AccidentalType& accidental, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                            // LetterType + AccidentalType + Octave + Format

                                char* GetName(char* buff, const Pitch::LetterType& note, const Pitch::AccidentalType& accidental, int8_t octave, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                                const char* GetName(const Pitch::LetterType& note, const Pitch::AccidentalType& accidental, int8_t octave, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                            //
                            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Get Accidental Name

                            char* GetAccidentalName(char* buff, const MusicalNote::Pitch::Accidental::AccidentalClass& accidental, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                            const char* GetAccidentalName(const MusicalNote::Pitch::Accidental::AccidentalClass& accidental, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Get Letter Name

                            char* GetLetterName(char* buff, const MusicalNote::Pitch::Letter::LetterClass& letter, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                            const char* GetLetterName(const MusicalNote::Pitch::Letter::LetterClass& letter, const NoteFormat::Format& format = NoteFormat::DefaultFormat);
                        //
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    }
                }
            }
        }
    }

   namespace MCC_MusicalNoteFlash = MusicCompositionCore::Core::MusicalCore::MusicalNote::Flash;  

#endif//MCC_MUSICAL_NOTE_FLASH_H