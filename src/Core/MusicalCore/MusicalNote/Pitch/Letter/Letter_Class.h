#ifndef MCC_NOTE_LETTER_CLASS_H
#define MCC_NOTE_LETTER_CLASS_H

    #include <MCC_BuildSettings.h>

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
                        
                        class Accidental;
                        
                    
                        class Letter
                        {
                            /////////////////////////////////////////////////////////////////////////////////
                            // typrdef and constants declaration
                             
                                public:
                                    typedef uint8_t LetterType;

                                    static Letter Buffer;

                                    static constexpr LetterType C = 0u;
                                    static constexpr LetterType D = 1u;
                                    static constexpr LetterType E = 2u;
                                    static constexpr LetterType F = 3u;
                                    static constexpr LetterType G = 4u;
                                    static constexpr LetterType A = 5u;
                                    static constexpr LetterType B = 6u;

                                    static constexpr LetterType InvalidID = 7u;
                                    static constexpr uint8_t MinIterator = 0u;
                                    static constexpr uint8_t MaxIterator = 6u;
                            //
                            /////////////////////////////////////////////////////////////////////////////////
                            // Variable Definitions

                                private:
                                    LetterType _ID;
                            //
                            /////////////////////////////////////////////////////////////////////////////////
                            // Method Declaration
                            
                                public:
                                    Letter();
                                    Letter(LetterType id);
                                    Letter& operator=(LetterType id);
                                    
                                    Letter(const Letter& source);
                                    Letter& operator=(const Letter& source);
                                    
                                    Letter(const PitchClass& token);
                                    Letter& operator=(const PitchClass& token);
                                    
                                    bool operator!=(const Letter& rhs) const;
                                    
                                    friend bool operator < (const Letter& lhs, const Letter& rhs);
                                    friend bool operator <= (const Letter& lhs, const Letter& rhs);
                                    friend bool operator > (const Letter& lhs, const Letter& rhs);
                                    friend bool operator >= (const Letter& lhs, const Letter& rhs);
                                    
                                    friend bool operator == (const Letter& lhs, const Letter& rhs);
                                    friend bool operator == (const LetterType& lhs, const Letter& rhs);
                                    friend bool operator == (const Letter& lhs, const LetterType& rhs);
                                    
                                    friend bool operator != (const Letter& lhs, const Letter& rhs);
                                    friend bool operator != (const LetterType& lhs, const Letter& rhs);
                                    friend bool operator != (const Letter& lhs, const LetterType& rhs);
                                    
                                    const LetterType& ID() const;
                                    operator const LetterType() const;
                                    
                                    PitchClass& GenerateToken(const Accidental& source);
                                    
                                    
                                    void Next();
                                    void Previous();
                            //
                            /////////////////////////////////////////////////////////////////////////////////
                        };

                        extern Letter Letter_Buffer;

                        bool operator < (const Letter& lhs, const Letter& rhs);
                        bool operator <= (const Letter& lhs, const Letter& rhs);
                        bool operator > (const Letter& lhs, const Letter& rhs);
                        bool operator >= (const Letter& lhs, const Letter& rhs);
                        
                        bool operator == (const Letter& lhs, const Letter& rhs);
                        bool operator == (const Letter::LetterType& lhs, const Letter& rhs);
                        bool operator == (const Letter& lhs, const Letter::LetterType& rhs);
                        
                        bool operator != (const Letter& lhs, const Letter& rhs);
                        bool operator != (const Letter::LetterType& lhs, const Letter& rhs);
                        bool operator != (const Letter& lhs, const Letter::LetterType& rhs);
                    }
                }
            }
        }
    }

#endif//MCC_NOTE_LETTER_CLASS_H
