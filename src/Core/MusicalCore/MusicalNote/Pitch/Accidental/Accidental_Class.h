#ifndef MCC_ACCIDENTAL_CLASS_H
#define MCC_ACCIDENTAL_CLASS_H

    #include <MCC_BuildSettings.h>
    #include "Accidental_Definitions.h"

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

                        namespace Letter
                        {
                          class LetterClass;
                        }

                        namespace Accidental
                        {
                            class AccidentalClass
                            {
                                AccidentalType _ID;
                                
                                public:
                                    AccidentalClass();
                                    AccidentalClass(AccidentalType id);
                                    AccidentalClass& operator=(AccidentalType id);
                                
                                    AccidentalClass(const AccidentalClass& source);
                                    AccidentalClass& operator=(const AccidentalClass& source);
                                
                                    AccidentalClass(const PitchClass& source);
                                    AccidentalClass& operator=(const PitchClass& source);
                                
                                    bool operator!=(const AccidentalClass& rhs) const;

                                    friend bool operator < (const AccidentalClass& lhs, const AccidentalClass& rhs);
                                    friend bool operator <= (const AccidentalClass& lhs, const AccidentalClass& rhs);
                                    friend bool operator > (const AccidentalClass& lhs, const AccidentalClass& rhs);
                                    friend bool operator >= (const AccidentalClass& lhs, const AccidentalClass& rhs);

                                    friend bool operator == (const AccidentalClass& lhs, const AccidentalClass& rhs);
                                    friend bool operator == (const AccidentalType& lhs, const AccidentalClass& rhs);
                                    friend bool operator == (const AccidentalClass& lhs, const AccidentalType& rhs);

                                    friend bool operator != (const AccidentalClass& lhs, const AccidentalClass& rhs);
                                    
                                    char* Name(char* buff);
                                    const char* Name() const;

                                    void Set_ID(const AccidentalClass& source);
                                    const AccidentalType& ID() const;
                                
                                    PitchClass& GenerateToken(const Letter::LetterClass& source);
                                
                                    bool Sharp();
                                    bool Flat();
                            };

                            extern AccidentalClass AccidentalID_Buffer;

                            bool operator < (const AccidentalClass& lhs, const AccidentalClass& rhs);
                            bool operator <= (const AccidentalClass& lhs, const AccidentalClass& rhs);
                            bool operator > (const AccidentalClass& lhs, const AccidentalClass& rhs);
                            bool operator >= (const AccidentalClass& lhs, const AccidentalClass& rhs);

                            bool operator == (const AccidentalClass& lhs, const AccidentalClass& rhs);
                            bool operator == (const AccidentalType& lhs, const AccidentalClass& rhs);
                            bool operator == (const AccidentalClass& lhs, const AccidentalType& rhs);

                            bool operator != (const AccidentalClass& lhs, const AccidentalClass& rhs);
                                
                        }
                    }
                }
            }
        }
    }

#endif//MCC_ACCIDENTAL_CLASS_H