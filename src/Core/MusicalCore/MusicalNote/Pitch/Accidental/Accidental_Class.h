#ifndef MCC_ACCIDENTAL_CLASS_H
#define MCC_ACCIDENTAL_CLASS_H

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

                        class Letter;

                        class Accidental
                        {

                            /////////////////////////////////////////////////////////////////////////////////
                            // typrdef and constants declaration

                                public:
                                    typedef int8_t AccidentalType;

                                    static Accidental Buffer;

                                    static constexpr AccidentalType QuadrupleFlat = -4;
                                    static constexpr AccidentalType TripleFlat = -3;
                                    static constexpr AccidentalType DoubleFlat = -2;
                                    static constexpr AccidentalType Flat = -1;
                                    static constexpr AccidentalType Natural = 0;
                                    static constexpr AccidentalType Sharp = 1;
                                    static constexpr AccidentalType DoubleSharp = 2;
                                    static constexpr AccidentalType TripleSharp = 3;
                                    static constexpr AccidentalType QuadrupleSharp = 4;

                                    static constexpr AccidentalType InvalidID = 5;
                                    static constexpr int8_t MinIterator = -4;
                                    static constexpr int8_t MaxIterator = 4;
                            //
                            /////////////////////////////////////////////////////////////////////////////////
                            // Variable Definitions

                                private:
                                    AccidentalType _ID;
                            //
                            /////////////////////////////////////////////////////////////////////////////////
                            // Method Declaration

                                public:
                                    Accidental();
                                    Accidental(AccidentalType id);
                                    Accidental& operator=(AccidentalType id);
                                
                                    Accidental(const Accidental& source);
                                    Accidental& operator=(const Accidental& source);
                                
                                    Accidental(const PitchClass& source);
                                    Accidental& operator=(const PitchClass& source);
                                    
                                    // ERASE
                                    bool operator!=(const Accidental& rhs) const;

                                    friend bool operator < (const Accidental& lhs, const Accidental& rhs);
                                    friend bool operator < (const AccidentalType& lhs, const Accidental& rhs);
                                    friend bool operator < (const Accidental& lhs, const AccidentalType& rhs);

                                    friend bool operator <= (const Accidental& lhs, const Accidental& rhs);
                                    friend bool operator <= (const AccidentalType& lhs, const Accidental& rhs);
                                    friend bool operator <= (const Accidental& lhs, const AccidentalType& rhs);
                                    
                                    friend bool operator > (const Accidental& lhs, const Accidental& rhs);
                                    friend bool operator > (const AccidentalType& lhs, const Accidental& rhs);
                                    friend bool operator > (const Accidental& lhs, const AccidentalType& rhs);
                                    
                                    friend bool operator >= (const Accidental& lhs, const Accidental& rhs);
                                    friend bool operator >= (const AccidentalType& lhs, const Accidental& rhs);
                                    friend bool operator >= (const Accidental& lhs, const AccidentalType& rhs);

                                    friend bool operator == (const Accidental& lhs, const Accidental& rhs);
                                    friend bool operator == (const AccidentalType& lhs, const Accidental& rhs);
                                    friend bool operator == (const Accidental& lhs, const AccidentalType& rhs);

                                    friend bool operator != (const Accidental& lhs, const Accidental& rhs);
                                    friend bool operator != (const AccidentalType& lhs, const Accidental& rhs);
                                    friend bool operator != (const Accidental& lhs, const AccidentalType& rhs);
                                    
                                    char* Name(char* buff);
                                    const char* Name() const;

                                    void Set_ID(const AccidentalType& source);
                                    const AccidentalType& ID() const;
                                
                                    PitchClass& GenerateToken(const Letter& source);
                                
                                    bool AddSharp();
                                    bool AddFlat();
                        };

                        bool operator < (const Accidental& lhs, const Accidental& rhs);
                        bool operator < (const Accidental::AccidentalType& lhs, const Accidental& rhs);
                        bool operator < (const Accidental& lhs, const Accidental::AccidentalType& rhs);

                        bool operator <= (const Accidental& lhs, const Accidental& rhs);
                        bool operator <= (const Accidental::AccidentalType& lhs, const Accidental& rhs);
                        bool operator <= (const Accidental& lhs, const Accidental::AccidentalType& rhs);

                        bool operator > (const Accidental& lhs, const Accidental& rhs);
                        bool operator > (const Accidental::AccidentalType& lhs, const Accidental& rhs);
                        bool operator > (const Accidental& lhs, const Accidental::AccidentalType& rhs);
                        
                        bool operator >= (const Accidental& lhs, const Accidental& rhs);
                        bool operator >= (const Accidental::AccidentalType& lhs, const Accidental& rhs);
                        bool operator >= (const Accidental& lhs, const Accidental::AccidentalType& rhs);

                        bool operator == (const Accidental& lhs, const Accidental& rhs);
                        bool operator == (const Accidental::AccidentalType& lhs, const Accidental& rhs);
                        bool operator == (const Accidental& lhs, const Accidental::AccidentalType& rhs);

                        bool operator != (const Accidental& lhs, const Accidental& rhs);
                        bool operator != (const Accidental::AccidentalType& lhs, const Accidental& rhs);
                        bool operator != (const Accidental& lhs, const Accidental::AccidentalType& rhs);
                            
                    }
                    
                }
            }
        }
    }

#endif//MCC_ACCIDENTAL_CLASS_H
