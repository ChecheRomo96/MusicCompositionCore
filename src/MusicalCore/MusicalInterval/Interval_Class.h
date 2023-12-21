#ifndef MCC_MUSIC_INTERVAL_CLASS_H
#define MCC_MUSIC_INTERVAL_CLASS_H

    #include <MCC_BuildSettings.h>
    #include <CPvector.h>    

    #include "MusicalInterval_Definitions.h"

    #include "../MusicalNote/MusicalNote.h"

    namespace MusicCompositionCore::MusicalCore
    {
        namespace MusicalNote
        {
            class Note;
        }
        namespace MusicalInterval
        {
            class Interval
            { 
                NumberType _Number;
                QualityType _Quality;

                public:

                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Constructors and Assignment operators

                        Interval();
                        
                        Interval(const QualityType& quality, const NumberType& number);
                        Interval(int16_t _NotePitch_A, int16_t _NotePitch_B, uint8_t _GenericInterval);

                        Interval(const MCC_MusicalNote::Note &source_a, const MCC_MusicalNote::Note &source_b);
                        Interval(const MCC_MusicalNote::Pitch& source_a, const MCC_MusicalNote::Pitch& source_b);

                        Interval(const Interval& src);
                        Interval& operator=(const Interval& src);
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // API

                        const char* Name() const;
                        char* Name(char* buff) const;

                        const uint8_t Semitones() const;
                        Interval Inverse() const;

                        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Generic Interval

                            void SetNumber(NumberType id);
                            const NumberType Number() const;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        // Interval Quality

                            void SetQuality(QualityType id);
                            const QualityType Quality() const;
                        //
                        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    
                
                private:

                    cpstd::vector<Interval> PossibleIntervals(int16_t _NotePitch_A, int16_t _NotePitch_B);
            };

            extern Interval IntervalBuffer;
        }
    }


#endif//MCC_MUSIC_INTERVAL_CLASS_H
