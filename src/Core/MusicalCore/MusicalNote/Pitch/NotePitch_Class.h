#ifndef MCC_NOTE_PITCH_CLASS_H
#define MCC_NOTE_PITCH_CLASS_H

    #include <MCC_BuildSettings.h>

    #include "../Pitch/NotePitch.h"
    #include "../TextFormat/TextFormat.h"

    #include "NotePitch_Definitions.h"

    namespace MusicCompositionCore
    {
        namespace Core
        {
            namespace MusicalCore
            {
                namespace MusicalInterval
                {
                    class Interval;
                }
                namespace MusicalNote
                {
                    namespace Pitch
                    {
                        class PitchClass
                        {
                            Letter _Letter;
                            Accidental _Accidental;
                            
                            public:
                                
                                PitchClass();
                                PitchClass(PitchType token);
                                PitchClass& operator=(PitchType token);
                                
                                PitchClass(const Letter& note, const Accidental& accidental);
                                
                                PitchClass(const PitchClass& source);
                                PitchClass& operator=(const PitchClass& source);
                                
                                PitchClass(const Letter& source);
                                PitchClass& operator=(const Letter& source);
                                
                                PitchClass(const Accidental& source);
                                PitchClass& operator=(const Accidental& source);
                                
                                
                                PitchClass& operator+=(const MusicalInterval::Interval &rhs);
                                PitchClass operator+(const MusicalInterval::Interval &rhs) const;
                                
                                PitchClass& operator-=(const MusicalInterval::Interval &rhs);
                                PitchClass operator-(const MusicalInterval::Interval &rhs) const;
                                
                                operator uint8_t() const;
                                
                                void SetLetter(const Letter& source);
                                const Letter& Letter() const;
                                
                                void SetAccidental(const Accidental& source);
                                const Accidental& Accidental() const;
                                
                                const char* Name(MusicalNote::TextFormat::FormatClass& Format = MusicalNote::TextFormat::DefaultFormat)const;
                                char* Name(char* buff, MusicalNote::TextFormat::FormatClass& Format = MusicalNote::TextFormat::DefaultFormat) const;
                            
                                const uint8_t NotePitch() const;
                                const uint8_t MidiPitch() const;
                                
                                bool Sharp();
                                bool Flat();
                                
                                void Next();
                                void Previous();
                                
                                friend bool operator < (const PitchClass& lhs, const PitchClass& rhs);
                                friend bool operator <= (const PitchClass& lhs, const PitchClass& rhs);
                                friend bool operator > (const PitchClass& lhs, const PitchClass& rhs);
                                friend bool operator >= (const PitchClass& lhs, const PitchClass& rhs);
                                friend bool operator == (const PitchClass& lhs, const PitchClass& rhs);
                                friend bool operator == (const PitchType& lhs, const PitchClass& rhs);
                                friend bool operator == (const PitchClass& lhs, const PitchType& rhs);
                                friend bool operator != (const PitchClass& lhs, const PitchClass& rhs);
                        };
                        
                        extern PitchClass PitchClass_Buffer;

                        bool operator < (const PitchClass& lhs, const PitchClass& rhs);
                        bool operator <= (const PitchClass& lhs, const PitchClass& rhs);
                        bool operator > (const PitchClass& lhs, const PitchClass& rhs);
                        bool operator >= (const PitchClass& lhs, const PitchClass& rhs);
                        bool operator == (const PitchClass& lhs, const PitchClass& rhs);
                        bool operator == (const PitchType& lhs, const PitchClass& rhs);
                        bool operator == (const PitchClass& lhs, const PitchType& rhs);
                        bool operator != (const PitchClass& lhs, const PitchClass& rhs);
                    }
                }
            }
        }
    }


#endif//MCC_NOTE_PITCH_CLASS_H
