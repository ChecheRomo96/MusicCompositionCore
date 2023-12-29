#ifndef MCC_NOTE_PITCH_CLASS_H
#define MCC_NOTE_PITCH_CLASS_H

    #include <MCC_BuildSettings.h>

    #include "../TextFormat/TextFormat.h"

    #include "NotePitch_Definitions.h"

    namespace MusicCompositionCore
    {
        #if defined(MCC_MUSICAL_INTERVAL_ENABLED)
            namespace MusicalInterval
            {
                class Interval;
            }
        #endif

        namespace MusicalNote
        {
            class Pitch
            {
                /////////////////////////////////////////////////////////////////////////////////
                // typrdef and constants declaration
                    public:
                        
                        typedef uint8_t Type;
                  
                        static constexpr Type C_QuadrupleFlat = 0u;
                        static constexpr Type C_TripleFlat = 1u;
                        static constexpr Type C_DoubleFlat = 2u;
                        static constexpr Type C_Flat = 3u;
                        static constexpr Type C_Natural = 4u;
                        static constexpr Type C_Sharp = 5u;
                        static constexpr Type C_DoubleSharp = 6u;
                        static constexpr Type C_TripleSharp = 7u;
                        static constexpr Type C_QuadrupleSharp = 8u;

                        static constexpr Type D_QuadrupleFlat = 9u;
                        static constexpr Type D_TripleFlat = 10u;
                        static constexpr Type D_DoubleFlat = 11u;
                        static constexpr Type D_Flat = 12u;
                        static constexpr Type D_Natural = 13u;
                        static constexpr Type D_Sharp = 14u;
                        static constexpr Type D_DoubleSharp = 15u;
                        static constexpr Type D_TripleSharp = 16u;
                        static constexpr Type D_QuadrupleSharp = 17u;

                        static constexpr Type E_QuadrupleFlat = 18u;
                        static constexpr Type E_TripleFlat = 19u;
                        static constexpr Type E_DoubleFlat = 20u;
                        static constexpr Type E_Flat = 21u;
                        static constexpr Type E_Natural = 22u;
                        static constexpr Type E_Sharp = 23u;
                        static constexpr Type E_DoubleSharp = 24u;
                        static constexpr Type E_TripleSharp = 25u;
                        static constexpr Type E_QuadrupleSharp = 26u;

                        static constexpr Type F_QuadrupleFlat = 27u;
                        static constexpr Type F_TripleFlat = 28u;
                        static constexpr Type F_DoubleFlat = 29u;
                        static constexpr Type F_Flat = 30u;
                        static constexpr Type F_Natural = 31u;
                        static constexpr Type F_Sharp = 32u;
                        static constexpr Type F_DoubleSharp = 33u;
                        static constexpr Type F_TripleSharp = 34u;
                        static constexpr Type F_QuadrupleSharp = 35u;

                        static constexpr Type G_QuadrupleFlat = 36u;
                        static constexpr Type G_TripleFlat = 37u;
                        static constexpr Type G_DoubleFlat = 38u;
                        static constexpr Type G_Flat = 39u;
                        static constexpr Type G_Natural = 40u;
                        static constexpr Type G_Sharp = 41u;
                        static constexpr Type G_DoubleSharp = 42u;
                        static constexpr Type G_TripleSharp = 43u;
                        static constexpr Type G_QuadrupleSharp = 44u;

                        static constexpr Type A_QuadrupleFlat = 45u;
                        static constexpr Type A_TripleFlat = 46u;
                        static constexpr Type A_DoubleFlat = 47u;
                        static constexpr Type A_Flat = 48u;
                        static constexpr Type A_Natural = 49u;
                        static constexpr Type A_Sharp = 50u;
                        static constexpr Type A_DoubleSharp = 51u;
                        static constexpr Type A_TripleSharp = 52u;
                        static constexpr Type A_QuadrupleSharp = 53u;

                        static constexpr Type B_QuadrupleFlat = 54u;
                        static constexpr Type B_TripleFlat = 55u;
                        static constexpr Type B_DoubleFlat = 56u;
                        static constexpr Type B_Flat = 57u;
                        static constexpr Type B_Natural = 58u;
                        static constexpr Type B_Sharp = 59u;
                        static constexpr Type B_DoubleSharp = 60u;
                        static constexpr Type B_TripleSharp = 61u;
                        static constexpr Type B_QuadrupleSharp = 62u;

                        static constexpr Type InvaildPitch = 63u;
                        static constexpr uint8_t MinIterator = 0u;
                        static constexpr uint8_t MaxIterator = 63u;
                //
                /////////////////////////////////////////////////////////////////////////////////
                // Variable Definitions

                    /////////////////////////////////////////////////////////////////////////////
                    // Letter Class

                        public:

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

                                        Letter(const Pitch& token);
                                        Letter& operator=(const Pitch& token);

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

                                        char* Name(char* buff);
                                        const char* Name() const;
                                        
                                        const LetterType& ID() const;
                                        operator const LetterType() const;

                                        Pitch& GenerateToken(const Accidental& source);

                                        void Next();
                                        void Previous();
                                //
                                /////////////////////////////////////////////////////////////////////////////////
                            };

                        private:
                            
                            Letter _Letter;
                    //
                    /////////////////////////////////////////////////////////////////////////////
                    // Accidental Class

                        public:

                            class Accidental
                            {

                                /////////////////////////////////////////////////////////////////////////////////
                                // typrdef and constants declaration

                                    public:

                                        static Accidental Buffer;

                                        typedef int8_t AccidentalType;

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
                                    
                                        Accidental(const Pitch& source);
                                        Accidental& operator=(const Pitch& source);
                                        
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
                                    
                                        Pitch& GenerateToken(const Letter& source);
                                    
                                        bool AddSharp();
                                        bool AddFlat();

                                        int8_t Sort_Ascending(const Pitch::Accidental& Element, const Pitch::Accidental& Pivot);
                                        int8_t Sort_Descending(const Pitch::Accidental& Element, const Pitch::Accidental& Pivot);
                            };

                        private:

                            Accidental _Accidental;
                    //
                    /////////////////////////////////////////////////////////////////////////////
                //
                /////////////////////////////////////////////////////////////////////////////////
                // Method Declaration

                    public:
                        
                        Pitch();
                        Pitch(Type token);
                        Pitch& operator=(Type token);
                        
                        Pitch(const Letter& note, const Accidental& accidental);
                        
                        Pitch(const Pitch& source);
                        Pitch& operator=(const Pitch& source);
                        
                        Pitch(const Letter& source);
                        Pitch& operator=(const Letter& source);
                        
                        Pitch(const Accidental& source);
                        Pitch& operator=(const Accidental& source);
                      
                        #if defined (MCC_MUSICAL_INTERVAL_ENABLED)  
                            Pitch& operator+=(const MusicalInterval::Interval &rhs);
                            Pitch operator+(const MusicalInterval::Interval &rhs) const;
                            
                            Pitch& operator-=(const MusicalInterval::Interval &rhs);
                            Pitch operator-(const MusicalInterval::Interval &rhs) const;
                        #endif

                        operator uint8_t() const;

                        const Type GetType() const;
                        
                        void SetLetter(const Letter& source);
                        const Letter& GetLetter() const;
                        
                        void SetAccidental(const Accidental& source);
                        const Accidental& GetAccidental() const;
                        
                        const char* Name(MusicalNote::TextFormat& Format = MusicalNote::DefaultFormat) const;
                        char* Name(char* buff, MusicalNote::TextFormat& Format = MusicalNote::DefaultFormat) const;
                    
                        const uint8_t NotePitch() const;
                        const uint8_t MidiPitch() const;

                        const Type& ID() const;
                        operator const Type() const;
                        
                        bool Sharp();
                        bool Flat();
                        
                        void Next();
                        void Previous();
                //
                /////////////////////////////////////////////////////////////////////////////////

            };
            
            extern Pitch PitchBuffer;
            extern Pitch::Type TypeBuffer;

            bool operator < (const Pitch& lhs, const Pitch& rhs);
            bool operator <= (const Pitch& lhs, const Pitch& rhs);
            bool operator > (const Pitch& lhs, const Pitch& rhs);
            bool operator >= (const Pitch& lhs, const Pitch& rhs);
            bool operator == (const Pitch& lhs, const Pitch& rhs);
            bool operator == (const Pitch::Type& lhs, const Pitch& rhs);
            bool operator == (const Pitch& lhs, const Pitch::Type& rhs);
            bool operator != (const Pitch& lhs, const Pitch& rhs);



            bool operator < (const Pitch::Letter& lhs, const Pitch::Letter& rhs);
            bool operator <= (const Pitch::Letter& lhs, const Pitch::Letter& rhs);
            bool operator > (const Pitch::Letter& lhs, const Pitch::Letter& rhs);
            bool operator >= (const Pitch::Letter& lhs, const Pitch::Pitch::Letter& rhs);
            
            bool operator == (const Pitch::Letter& lhs, const Pitch::Letter& rhs);
            bool operator == (const Pitch::Letter::LetterType& lhs, const Pitch::Letter& rhs);
            bool operator == (const Pitch::Letter& lhs, const Pitch::Letter::LetterType& rhs);
            
            bool operator != (const Pitch::Letter& lhs, const Pitch::Letter& rhs);
            bool operator != (const Pitch::Letter::LetterType& lhs, const Pitch::Letter& rhs);
            bool operator != (const Pitch::Letter& lhs, const Pitch::Letter::LetterType& rhs);



            bool operator < (const Pitch::Accidental& lhs, const Pitch::Accidental& rhs);
            bool operator < (const Pitch::Accidental::AccidentalType& lhs, const Pitch::Accidental& rhs);
            bool operator < (const Pitch::Accidental& lhs, const Pitch::Accidental::AccidentalType& rhs);

            bool operator <= (const Pitch::Accidental& lhs, const Pitch::Accidental& rhs);
            bool operator <= (const Pitch::Accidental::AccidentalType& lhs, const Pitch::Accidental& rhs);
            bool operator <= (const Pitch::Accidental& lhs, const Pitch::Accidental::AccidentalType& rhs);

            bool operator > (const Pitch::Accidental& lhs, const Pitch::Accidental& rhs);
            bool operator > (const Pitch::Accidental::AccidentalType& lhs, const Pitch::Accidental& rhs);
            bool operator > (const Pitch::Accidental& lhs, const Pitch::Accidental::AccidentalType& rhs);
            
            bool operator >= (const Pitch::Accidental& lhs, const Pitch::Accidental& rhs);
            bool operator >= (const Pitch::Accidental::AccidentalType& lhs, const Pitch::Accidental& rhs);
            bool operator >= (const Pitch::Accidental& lhs, const Pitch::Accidental::AccidentalType& rhs);

            bool operator == (const Pitch::Accidental& lhs, const Pitch::Accidental& rhs);
            bool operator == (const Pitch::Accidental::AccidentalType& lhs, const Pitch::Accidental& rhs);
            bool operator == (const Pitch::Accidental& lhs, const Pitch::Accidental::AccidentalType& rhs);

            bool operator != (const Pitch::Accidental& lhs, const Pitch::Accidental& rhs);
            bool operator != (const Pitch::Accidental::AccidentalType& lhs, const Pitch::Accidental& rhs);
            bool operator != (const Pitch::Accidental& lhs, const Pitch::Accidental::AccidentalType& rhs);
        }
    }


#endif//MCC_NOTE_PITCH_CLASS_H