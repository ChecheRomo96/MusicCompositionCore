#ifndef MCC_NOTE_LETTER_CLASS_H
#define MCC_NOTE_LETTER_CLASS_H

    #include <MCC_BuildSettings.h>

    #include "Letter_Definitions.h"

    namespace MusicCompositionCore
    {
        namespace Core
        {
            namespace MusicalCore
            {
                namespace MusicalNote
                {
                    namespace Pitch
                    {
                        class PitchClass;
                        
                        namespace Accidental
                        {
                            class AccidentalClass;
                        }
                        
                        namespace Letter
                        {
                            class LetterClass
                            {
                                LetterType _ID;
                                
                            public:
                                LetterClass();
                                LetterClass(LetterType id);
                                LetterClass& operator=(LetterType id);
                                
                                LetterClass(const LetterClass& source);
                                LetterClass& operator=(const LetterClass& source);
                                
                                LetterClass(const PitchClass& token);
                                LetterClass& operator=(const PitchClass& token);
                                
                                bool operator!=(const LetterClass& rhs) const;
                                
                                friend bool operator < (const LetterClass& lhs, const LetterClass& rhs);
                                friend bool operator <= (const LetterClass& lhs, const LetterClass& rhs);
                                friend bool operator > (const LetterClass& lhs, const LetterClass& rhs);
                                friend bool operator >= (const LetterClass& lhs, const LetterClass& rhs);
                                
                                friend bool operator == (const LetterClass& lhs, const LetterClass& rhs);
                                friend bool operator == (const LetterType& lhs, const LetterClass& rhs);
                                friend bool operator == (const LetterClass& lhs, const LetterType& rhs);
                                
                                friend bool operator != (const LetterClass& lhs, const LetterClass& rhs);
                                friend bool operator != (const LetterType& lhs, const LetterClass& rhs);
                                friend bool operator != (const LetterClass& lhs, const LetterType& rhs);
                                
                                const LetterType& ID() const;
                                operator const LetterType() const;
                                
                                PitchClass& GenerateToken(const Accidental::AccidentalClass& source);
                                
                                
                                void Next();
                                void Previous();
                            };
                            extern LetterClass Letter_Buffer;

                            bool operator < (const LetterClass& lhs, const LetterClass& rhs);
                            bool operator <= (const LetterClass& lhs, const LetterClass& rhs);
                            bool operator > (const LetterClass& lhs, const LetterClass& rhs);
                            bool operator >= (const LetterClass& lhs, const LetterClass& rhs);
                            
                            bool operator == (const LetterClass& lhs, const LetterClass& rhs);
                            bool operator == (const LetterType& lhs, const LetterClass& rhs);
                            bool operator == (const LetterClass& lhs, const LetterType& rhs);
                            
                            bool operator != (const LetterClass& lhs, const LetterClass& rhs);
                            bool operator != (const LetterType& lhs, const LetterClass& rhs);
                            bool operator != (const LetterClass& lhs, const LetterType& rhs);
                        }
                    }
                }
            }
        }
    }

#endif//MCC_NOTE_LETTER_CLASS_H
