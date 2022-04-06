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

    Interval::Interval(int16_t _NotePitch_A, int16_t _NotePitch_B, NumberType _GenericInterval)
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
            // GetPitch(A) == GetPitch(B)
            
            if(source_a.GetPitch().GetLetter().ID() == source_b.GetPitch().GetLetter().ID())
            {
                // Note(A) == Note(B)
                _Number = 0;
            }
            else if(source_a.GetPitch().GetLetter().ID() < source_b.GetPitch().GetLetter().ID())
            {
                // Note(A) < Note(B)
                _Number = source_b.GetPitch().GetLetter().ID() - source_a.GetPitch().GetLetter().ID();
            }
            else
            {
                // Note(A) > Note(B)
                _Number = 7 + source_b.GetPitch().GetLetter().ID() - source_a.GetPitch().GetLetter().ID();
            }
        }
        else if(source_a.NotePitch() < source_b.NotePitch())
        {
            // GetPitch(A) < GetPitch(B)
            int OctaveOffsetting = 7 * ((source_b.NotePitch() - source_a.NotePitch())/12);
            
            if(source_a.GetPitch().GetLetter().ID() == source_b.GetPitch().GetLetter().ID())
            {
                // Note(A) == Note(B)
                _Number = OctaveOffsetting;
            }
            else if(source_a.GetPitch().GetLetter().ID() < source_b.GetPitch().GetLetter().ID())
            {
                // Note(A) < Note(B)
                _Number = OctaveOffsetting + source_b.GetPitch().GetLetter().ID() - source_a.GetPitch().GetLetter().ID();
            }
            else
            {
                // Note(A) > Note(B)
                _Number = 7 + OctaveOffsetting + source_b.GetPitch().GetLetter().ID() - source_a.GetPitch().GetLetter().ID();
            }
            
        }
        else
        {
            // GetPitch(A) > GetPitch(B)
            
            if(source_a.GetPitch().GetLetter().ID() == source_b.GetPitch().GetLetter().ID())
            {
                // Note(A) == Note(B)
                _Number = 7;
            }
            else if(source_a.GetPitch().GetLetter().ID() < source_b.GetPitch().GetLetter().ID())
            {
                // Note(A) < Note(B)
                _Number = source_b.GetPitch().GetLetter().ID() - source_a.GetPitch().GetLetter().ID();
            }
            else
            {
                // Note(A) > Note(B)
                _Number = 7 - (source_a.GetPitch().GetLetter().ID() - source_b.GetPitch().GetLetter().ID());
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

    Interval::Interval(const MCC_MusicalNote::Pitch &source_a, const MCC_MusicalNote::Pitch& source_b)
    {
        if(source_a.GetLetter().ID() == source_b.GetLetter().ID())
        {
            if(source_a.GetAccidental().ID() > source_b.GetAccidental().ID())
            {
                // A > B
                _Number = source_b.GetLetter().ID() - source_a.GetLetter().ID()+7;
            }
            else if(source_a.GetAccidental().ID() == source_b.GetAccidental().ID())
            {
                // A = B
                _Number = 0;
            }
            else
            {
                // A < B
                _Number = source_b.GetLetter().ID() - source_a.GetLetter().ID();
            }
        }
        else if(source_a.GetLetter().ID() > source_b.GetLetter().ID())
        {
            // A > B
            _Number = source_b.GetLetter().ID() - source_a.GetLetter().ID()+7;
        }
        else if(source_a.GetLetter().ID() < source_b.GetLetter().ID())
        {
            // A < B
            _Number = source_b.GetLetter().ID() - source_a.GetLetter().ID();
        }
        
        _Quality = Qualities::InvalidQuality;
        
        uint8_t sem;
        if(source_a.GetLetter().ID() == source_b.GetLetter().ID())
        {
            if(source_a.GetAccidental().ID() > source_b.GetAccidental().ID())
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
        else if(source_a.GetLetter().ID() > source_b.GetLetter().ID())
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

        void Interval::SetNumber(NumberType id)
        {
            if(id < Numbers::Count)
            {
                _Number = id;
            }
        }

        const NumberType Interval::Number() const
        {
            return _Number;
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Interval Quality

        void Interval::SetQuality(QualityType id)
        {
            if(id < Qualities::Count)
            {
                _Quality = id;
            }
        }

        const QualityType Interval::Quality() const
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
