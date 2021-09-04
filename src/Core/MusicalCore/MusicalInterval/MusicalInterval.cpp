#include "MusicalInterval.h"
#include "../MusicalNote/MusicalNote.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Setup

    using namespace MCC_MusicalInterval;

//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definitions

    Interval MCC_MusicalInterval::IntervalBuffer;
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructors

    Interval::Interval()
    {
        _Number = Numbers::InvalidNumber;
        _Quality = Qualities::InvalidQuality;
    }

    Interval::Interval(const QualityType& quality, const NumberType& number)
    {
        _Number = number;
        _Quality = quality;
    }

    Interval::Interval(int16_t _NotePitch_A, int16_t _NotePitch_B, uint8_t _GenericInterval)
    {
        uint8_t i = 0;
        _Number = Numbers::InvalidNumber;
        _Quality = Qualities::InvalidQuality;
        
        CPVector::vector<MCC_MusicalInterval::Interval> possibleIntervals = PossibleIntervals(_NotePitch_A, _NotePitch_B);
        
        while(i < possibleIntervals.size())
        {
            if(possibleIntervals[i].Number() == _GenericInterval)
            {
                _Number = _GenericInterval;
                _Quality = possibleIntervals[i].Quality();
            }
            i++;
        }
    }

    Interval::Interval(const MCC_MusicalNote::Note &source_a, const MCC_MusicalNote::Note &source_b)
    {
        _Number = 0;
        if(source_a.NotePitch() == source_b.NotePitch())
        {
            // Pitch(A) == Pitch(B)
            
            if(source_a.Pitch().Letter().ID() == source_b.Pitch().Letter().ID())
            {
                // Note(A) == Note(B)
                _Number = 0;
            }
            else if(source_a.Pitch().Letter().ID() < source_b.Pitch().Letter().ID())
            {
                // Note(A) < Note(B)
                _Number = source_b.Pitch().Letter().ID() - source_a.Pitch().Letter().ID();
            }
            else
            {
                // Note(A) > Note(B)
                _Number = 7 + source_b.Pitch().Letter().ID() - source_a.Pitch().Letter().ID();
            }
        }
        else if(source_a.NotePitch() < source_b.NotePitch())
        {
            // Pitch(A) < Pitch(B)
            int OctaveOffsetting = 7 * ((source_b.NotePitch() - source_a.NotePitch())/12);
            
            if(source_a.Pitch().Letter().ID() == source_b.Pitch().Letter().ID())
            {
                // Note(A) == Note(B)
                _Number = OctaveOffsetting;
            }
            else if(source_a.Pitch().Letter().ID() < source_b.Pitch().Letter().ID())
            {
                // Note(A) < Note(B)
                _Number = OctaveOffsetting + source_b.Pitch().Letter().ID() - source_a.Pitch().Letter().ID();
            }
            else
            {
                // Note(A) > Note(B)
                _Number = 7 + OctaveOffsetting + source_b.Pitch().Letter().ID() - source_a.Pitch().Letter().ID();
            }
            
        }
        else
        {
            // Pitch(A) > Pitch(B)
            
            if(source_a.Pitch().Letter().ID() == source_b.Pitch().Letter().ID())
            {
                // Note(A) == Note(B)
                _Number = 7;
            }
            else if(source_a.Pitch().Letter().ID() < source_b.Pitch().Letter().ID())
            {
                // Note(A) < Note(B)
                _Number = source_b.Pitch().Letter().ID() - source_a.Pitch().Letter().ID();
            }
            else
            {
                // Note(A) > Note(B)
                _Number = 7 - (source_a.Pitch().Letter().ID() - source_b.Pitch().Letter().ID());
            }
        }

        _Quality = Qualities::InvalidQuality;
        
        int8_t sem;
        
        if(source_a.NotePitch() == source_b.NotePitch())
        {
            sem = 0;
        }
        else if(source_a.NotePitch() < source_b.NotePitch())
        {
            sem = source_b.NotePitch() - source_a.NotePitch();
        }
        else
        {
            sem = 12 + ((source_b.NotePitch() - source_a.NotePitch())%12);
        }
        

        for(uint8_t i = 0; i < Qualities::Count; i++)
        {
            if(sem == Flash::GetIntervalSemitones(_Number, i))
            {
                _Quality = i;
            }
        }
    }

    Interval::Interval(const MCC_MusicalNote::Pitch::PitchClass &source_a, const MCC_MusicalNote::Pitch::PitchClass& source_b)
    {
        if(source_a.Letter().ID() == source_b.Letter().ID())
        {
            if(source_a.Accidental().ID() > source_b.Accidental().ID())
            {
                // A > B
                _Number = source_b.Letter().ID() - source_a.Letter().ID()+7;
            }
            else if(source_a.Accidental().ID() == source_b.Accidental().ID())
            {
                // A = B
                _Number = 0;
            }
            else
            {
                // A < B
                _Number = source_b.Letter().ID() - source_a.Letter().ID();
            }
        }
        else if(source_a.Letter().ID() > source_b.Letter().ID())
        {
            // A > B
            _Number = source_b.Letter().ID() - source_a.Letter().ID()+7;
        }
        else if(source_a.Letter().ID() < source_b.Letter().ID())
        {
            // A < B
            _Number = source_b.Letter().ID() - source_a.Letter().ID();
        }
        
        _Quality = Qualities::InvalidQuality;
        
        uint8_t sem;
        if(source_a.Letter().ID() == source_b.Letter().ID())
        {
            if(source_a.Accidental().ID() > source_b.Accidental().ID())
            {
                // A > B
                sem = abs(source_b.NotePitch()-source_a.NotePitch()+12);
            }
            else
            {
                // A <= B
                sem = abs(source_b.NotePitch()-source_a.NotePitch());
            }
        }
        else if(source_a.Letter().ID() > source_b.Letter().ID())
        {
            // A > B
            sem = abs(source_b.NotePitch()-source_a.NotePitch()+12);
        }
        else
        {
            // A <= B
            sem = abs(source_b.NotePitch()-source_a.NotePitch());
        }
        
        for(uint8_t i = 0; i < Qualities::Count; i++)
        {
            if(sem == Flash::GetIntervalSemitones(_Number, i))
            {
                _Quality = i;
            }
        }
    }

    Interval::Interval(const Interval& src)
    {
        _Number = src.Number();
        _Quality = src.Quality();
    }

    Interval& Interval::operator=(const Interval& src)
    {
        _Number = src.Number();
        _Quality = src.Quality();

        return (*this);
    }
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// API
 
    const char* Interval::Name() const
    {
        return Flash::GetIntervalName(_Number, _Quality);
    }

    char* Interval::Name(char* buff) const
    {
        return Flash::GetIntervalName(buff, _Number, _Quality);
    }

    const uint8_t Interval::Semitones() const
    {
        return Flash::GetIntervalSemitones(_Number,_Quality);
    }

    Interval Interval::Inverse() const
    {
        Interval buff;

        buff.SetNumber(7 - (Number()%7));
        buff.SetQuality(Qualities::Perfect - (Quality() - Qualities::Perfect));
        
        return buff;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Interval Number

        void Interval::SetNumber(uint8_t id)
        {
            if(id < Numbers::Count)
            {
                _Number = id;
            }
        }

        const uint8_t Interval::Number() const
        {
            return _Number;
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Interval Quality

        void Interval::SetQuality(uint8_t id)
        {
            if(id < Qualities::Count)
            {
                _Quality = id;
            }
        }

        const uint8_t Interval::Quality() const
        {
            return _Quality;
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods

    CPVector::vector<MCC_MusicalInterval::Interval> Interval::PossibleIntervals(int16_t _NotePitch_A, int16_t _NotePitch_B)
    {
        CPVector::vector<MCC_MusicalInterval::Interval> vect;
        
        uint16_t semitones = abs(_NotePitch_A-_NotePitch_B);
        
        if(semitones > 24)
        {
            semitones%=12;
            semitones+=12;
        }
        
        for(uint8_t i = 0; i < MCC_MusicalInterval::Numbers::Count; i++)
        {
            for(uint8_t j = 0; j < MCC_MusicalInterval::Qualities::Count; j++)
            {
                if(Flash::GetIntervalSemitones(i, j) == semitones)
                {
                    vect.push_back(MCC_MusicalInterval::Interval(j,i));
                }
            }
        }
            
        return vect;
    }
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
