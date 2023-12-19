#include "NotePitch.h"

#include "NotePitch_Definitions.h"

#include "../Note_Class.h"
#include "../TextFormat/TextFormat.h"

#if defined(MCC_MUSICAL_INTERVAL_ENABLED)
    #include "../../MusicalInterval/MusicalInterval.h"
#endif

using namespace MusicCompositionCore::Core::MusicalCore;
using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

/////////////////////////////////////////////////////////////////////////
//  Buffers
    
    Pitch MusicalNote::PitchBuffer;
    Pitch::Type MusicalNote::TypeBuffer;
//
/////////////////////////////////////////////////////////////////////////
//  Notes Array

    const int8_t MusicalNote::NotesArray[7] = {0,2,4,5,7,9,11};
//
/////////////////////////////////////////////////////////////////////////
// Pitch Definitions

    constexpr Pitch::Type Pitch::A_QuadrupleFlat;
    constexpr Pitch::Type Pitch::A_TripleFlat;
    constexpr Pitch::Type Pitch::A_DoubleFlat;
    constexpr Pitch::Type Pitch::A_Flat;
    constexpr Pitch::Type Pitch::A_Natural;
    constexpr Pitch::Type Pitch::A_Sharp;
    constexpr Pitch::Type Pitch::A_DoubleSharp;
    constexpr Pitch::Type Pitch::A_TripleSharp;
    constexpr Pitch::Type Pitch::A_QuadrupleSharp;

    constexpr Pitch::Type Pitch::B_QuadrupleFlat;
    constexpr Pitch::Type Pitch::B_TripleFlat;
    constexpr Pitch::Type Pitch::B_DoubleFlat;
    constexpr Pitch::Type Pitch::B_Flat;
    constexpr Pitch::Type Pitch::B_Natural;
    constexpr Pitch::Type Pitch::B_Sharp;
    constexpr Pitch::Type Pitch::B_DoubleSharp;
    constexpr Pitch::Type Pitch::B_TripleSharp;
    constexpr Pitch::Type Pitch::B_QuadrupleSharp;

    constexpr Pitch::Type Pitch::C_QuadrupleFlat;
    constexpr Pitch::Type Pitch::C_TripleFlat;
    constexpr Pitch::Type Pitch::C_DoubleFlat;
    constexpr Pitch::Type Pitch::C_Flat;
    constexpr Pitch::Type Pitch::C_Natural;
    constexpr Pitch::Type Pitch::C_Sharp;
    constexpr Pitch::Type Pitch::C_DoubleSharp;
    constexpr Pitch::Type Pitch::C_TripleSharp;
    constexpr Pitch::Type Pitch::C_QuadrupleSharp;

    constexpr Pitch::Type Pitch::D_QuadrupleFlat;
    constexpr Pitch::Type Pitch::D_TripleFlat;
    constexpr Pitch::Type Pitch::D_DoubleFlat;
    constexpr Pitch::Type Pitch::D_Flat;
    constexpr Pitch::Type Pitch::D_Natural;
    constexpr Pitch::Type Pitch::D_Sharp;
    constexpr Pitch::Type Pitch::D_DoubleSharp;
    constexpr Pitch::Type Pitch::D_TripleSharp;
    constexpr Pitch::Type Pitch::D_QuadrupleSharp;

    constexpr Pitch::Type Pitch::E_QuadrupleFlat;
    constexpr Pitch::Type Pitch::E_TripleFlat;
    constexpr Pitch::Type Pitch::E_DoubleFlat;
    constexpr Pitch::Type Pitch::E_Flat;
    constexpr Pitch::Type Pitch::E_Natural;
    constexpr Pitch::Type Pitch::E_Sharp;
    constexpr Pitch::Type Pitch::E_DoubleSharp;
    constexpr Pitch::Type Pitch::E_TripleSharp;
    constexpr Pitch::Type Pitch::E_QuadrupleSharp;

    constexpr Pitch::Type Pitch::F_QuadrupleFlat;
    constexpr Pitch::Type Pitch::F_TripleFlat;
    constexpr Pitch::Type Pitch::F_DoubleFlat;
    constexpr Pitch::Type Pitch::F_Flat;
    constexpr Pitch::Type Pitch::F_Natural;
    constexpr Pitch::Type Pitch::F_Sharp;
    constexpr Pitch::Type Pitch::F_DoubleSharp;
    constexpr Pitch::Type Pitch::F_TripleSharp;
    constexpr Pitch::Type Pitch::F_QuadrupleSharp;

    constexpr Pitch::Type Pitch::G_QuadrupleFlat;
    constexpr Pitch::Type Pitch::G_TripleFlat;
    constexpr Pitch::Type Pitch::G_DoubleFlat;
    constexpr Pitch::Type Pitch::G_Flat;
    constexpr Pitch::Type Pitch::G_Natural;
    constexpr Pitch::Type Pitch::G_Sharp;
    constexpr Pitch::Type Pitch::G_DoubleSharp;
    constexpr Pitch::Type Pitch::G_TripleSharp;
    constexpr Pitch::Type Pitch::G_QuadrupleSharp;
//
/////////////////////////////////////////////////////////////////////////
// Pitch::Letter Definitions

    constexpr Pitch::Letter::LetterType Pitch::Letter::A;
    constexpr Pitch::Letter::LetterType Pitch::Letter::B;
    constexpr Pitch::Letter::LetterType Pitch::Letter::C;
    constexpr Pitch::Letter::LetterType Pitch::Letter::D;
    constexpr Pitch::Letter::LetterType Pitch::Letter::E;
    constexpr Pitch::Letter::LetterType Pitch::Letter::F;
    constexpr Pitch::Letter::LetterType Pitch::Letter::G;
    constexpr Pitch::Letter::LetterType Pitch::Letter::InvalidID;

    constexpr uint8_t Pitch::Letter::MaxIterator;
    constexpr uint8_t Pitch::Letter::MinIterator;
//
/////////////////////////////////////////////////////////////////////////
// Pitch::Accidental Definitions

    constexpr Pitch::Accidental::AccidentalType Pitch::Accidental::QuadrupleFlat;
    constexpr Pitch::Accidental::AccidentalType Pitch::Accidental::TripleFlat;
    constexpr Pitch::Accidental::AccidentalType Pitch::Accidental::DoubleFlat;
    constexpr Pitch::Accidental::AccidentalType Pitch::Accidental::Flat;
    constexpr Pitch::Accidental::AccidentalType Pitch::Accidental::Natural;
    constexpr Pitch::Accidental::AccidentalType Pitch::Accidental::Sharp;
    constexpr Pitch::Accidental::AccidentalType Pitch::Accidental::DoubleSharp;
    constexpr Pitch::Accidental::AccidentalType Pitch::Accidental::TripleSharp;
    constexpr Pitch::Accidental::AccidentalType Pitch::Accidental::QuadrupleSharp;
    constexpr Pitch::Accidental::AccidentalType Pitch::Accidental::InvalidID;

    constexpr int8_t Pitch::Accidental::MaxIterator;
    constexpr int8_t Pitch::Accidental::MinIterator;
//
////////////////////////////////////////////////////////////////////////

Pitch::Pitch()
{
    _Letter = Letter::InvalidID;
    _Accidental = Accidental::InvalidID;
}

Pitch::Pitch(Type token)
{
    if(token < Pitch::MaxIterator)
    {
        _Letter = Pitch::Letter(token/9);
        _Accidental = Pitch::Accidental((token%9) - 4);
    }
    else
    {
        _Letter = Letter::InvalidID;
        _Accidental = Accidental::InvalidID;
    }
}

Pitch& Pitch::operator=(Type token)
{
    if(token < Pitch::MaxIterator)
    {
        _Letter = Pitch::Letter(token/9);
        _Accidental = Pitch::Accidental((token%9) - 4);
    }
    else
    {
        _Letter = Letter::InvalidID;
        _Accidental = Accidental::InvalidID;
    }
    return (*this);
}

Pitch::Pitch(const Pitch::Letter& note, const Pitch::Accidental& accidental)
{
    _Letter = note;
    _Accidental = accidental;
}

Pitch::Pitch(const Pitch& source)
{
    _Letter = source.GetLetter();
    _Accidental = source.GetAccidental();
}

Pitch& Pitch::operator=(const Pitch& source)
{
    _Letter = source.GetLetter();
    _Accidental = source.GetAccidental();
    return (*this);
}


#if defined(MCC_MUSICAL_INTERVAL_ENABLED)

    Pitch& Pitch::operator+=(const MusicalInterval::Interval &rhs)
    {
        PitchBuffer = (*this)+rhs;
        (*this) = PitchBuffer;
        return (*this);
    }

    Pitch Pitch::operator+(const MusicalInterval::Interval &rhs) const
    {
        Pitch tmp = (*this);
        
        int16_t base = NotePitch();
        
        if(rhs.Semitones() == MCC_MusicalInterval::InvalidInterval){return tmp;}

        for(uint8_t i = 0; i < rhs.Number()%7; i++)
        {
            tmp.Next();
        }
        
        int16_t destination_pitch = (base + rhs.Semitones())%12;
        int16_t current_pitch = tmp.NotePitch()%12;
        
        int8_t distance = current_pitch-destination_pitch;
        bool flag = 0;
        
        if(distance < 0){distance+=12;}
        if(distance>=6)
        {
            flag = 1;
            distance = destination_pitch-current_pitch;
            if(distance < 0){distance+=12;}
        }
        
        if(distance == 0){return tmp;}
        
        else if(destination_pitch<current_pitch)
        {
            if((destination_pitch+distance)%12 == current_pitch)
            {
                while( distance != 0 )
                {
                    if(tmp.Flat() == 0)
                    {
                        tmp = (*this);
                        return tmp;
                    }
                    current_pitch = tmp.NotePitch()%12;
                    
                    distance = current_pitch-destination_pitch;
                    if(distance < 0){distance+=12;}
                }
                return tmp;
            }
            else if((current_pitch+distance)%12 == destination_pitch)
            {
                while( distance != 0 )
                {
                    if(tmp.Sharp() == 0)
                    {
                        tmp = (*this);
                        return tmp;
                    }
                    current_pitch = tmp.NotePitch()%12;
                    
                    distance = current_pitch-destination_pitch;
                    if(distance < 0){distance+=12;}
                }
                return tmp;
            }
        }
        
        else if(destination_pitch>current_pitch)
        {
            if((destination_pitch+distance)%12 == current_pitch)
            {
                while( distance != 0 )
                {
                    if(tmp.Flat() == 0)
                    {
                        tmp = (*this);
                        return tmp;
                    }
                    current_pitch = tmp.NotePitch()%12;
                    
                    distance = current_pitch-destination_pitch;
                    if(distance < 0){distance+=12;}
                }
                return tmp;
            }
            else if((current_pitch+distance)%12 == destination_pitch)
            {
                while( distance != 0 )
                {
                    if(tmp.Sharp() == 0)
                    {
                        tmp = (*this);
                        return tmp;
                    }
                    current_pitch = tmp.NotePitch()%12;
                    
                    distance = current_pitch-destination_pitch;
                    if(distance < 0){distance+=12;}
                }
                return tmp;
            }
        }

        return tmp;
    }


    Pitch& Pitch::operator-=(const MusicalInterval::Interval &rhs)
    {
        PitchBuffer = (*this)-rhs;
        (*this) = PitchBuffer;
        return (*this);
    }

    Pitch Pitch::operator-(const MusicalInterval::Interval &rhs) const
    {
        // Checking if the provided interval is valid, else return the note as is
        if(rhs.Semitones() == MCC_MusicalInterval::InvalidInterval){return (*this);}

        // Make a copy of this instance into an object called tmp
        Pitch tmp = (*this);
        
        // Storing the base Pitch
        int16_t base = NotePitch();

        // Changing Note Letter to finish the Generic Interval Conversion
        for(uint8_t i = 0; i < rhs.Number()%7; i++)
        {
            tmp.Previous();
        }
        
        int16_t destination_pitch = base - rhs.Semitones();
        int16_t current_pitch = tmp.NotePitch();
        
        int8_t distance = destination_pitch - current_pitch;

        if(distance == 0){return tmp;}

        else if(destination_pitch<current_pitch)
        {
            if((destination_pitch-distance) == current_pitch)
            {
                while( distance != 0 )
                {
                    if(tmp.Flat() == 0)
                    {
                        tmp = (*this);
                        return tmp;
                    }
                    current_pitch = tmp.NotePitch();
                    
                    distance = destination_pitch-current_pitch;
                    
                    if(distance > 0){distance-=12;}
                }
                return tmp;
            }
            else if((current_pitch-distance)%12 == destination_pitch)
            {
                while( distance != 0 )
                {
                    if(tmp.Sharp() == 0)
                    {
                        tmp = (*this);
                        return tmp;
                    }
                    current_pitch = tmp.NotePitch()%12;
                    
                    distance = current_pitch-destination_pitch;
                    if(distance < 0){distance+=12;}
                }
                return tmp;
            }
        }
        



        
        else if(destination_pitch>current_pitch)
        {
            if((destination_pitch-distance) == current_pitch)
            {
                while( distance != 0 )
                {
                    if(tmp.Sharp() == 0)
                    {
                        tmp = (*this);
                        return tmp;
                    }
                    current_pitch = tmp.NotePitch();
                    
                    distance = current_pitch-destination_pitch;
                    if(distance < 0){distance+=12;}
                }
                return tmp;
            }
            else if((current_pitch-distance) == destination_pitch)
            {
                while( distance != 0 )
                {
                    if(tmp.Flat() == 0)
                    {
                        tmp = (*this);
                        return tmp;
                    }
                    current_pitch = tmp.NotePitch();
                    
                    distance = current_pitch-destination_pitch;
                    if(distance < 0){distance+=12;}
                }
                return tmp;
            }
        }

        return tmp;
    }
#endif


Pitch::Pitch(const Pitch::Letter& source)
{
    _Letter = source;
    _Accidental = Accidental::InvalidID;
}

Pitch& Pitch::operator=(const Pitch::Letter& source)
{
    _Letter = source;
    return (*this);
}

Pitch::Pitch(const Pitch::Accidental& source)
{
    _Accidental = source;
    _Letter = Letter::InvalidID;
}

Pitch& Pitch::operator=(const Pitch::Accidental& source)
{
    _Accidental = source;
    return(*this);
}

Pitch::operator uint8_t() const
{
    if((_Letter == Letter::InvalidID)||(_Accidental == Accidental::InvalidID))
    {
        return Pitch::InvaildPitch;
    }
    return (_Letter.ID() * 5) + _Accidental.ID();
}

void Pitch::SetLetter(const Pitch::Letter& source)
{
    _Letter = source;
}

const Pitch::Letter& Pitch::GetLetter() const
{
    return _Letter;
}

void Pitch::SetAccidental(const Pitch::Accidental& source)
{
    _Accidental = source;
}

const Pitch::Accidental& Pitch::GetAccidental() const
{
    return _Accidental;
}

bool Pitch::Sharp()
{
    return _Accidental.AddSharp();
}

bool Pitch::Flat()
{
    return _Accidental.AddFlat();
}

void Pitch::Next()
{
    return _Letter.Next();
}

void Pitch::Previous()
{
    return _Letter.Previous();
}

const char* Pitch::Name(MusicalNote::TextFormat& Format) const
{
    bool flag = 0;
    if(Format.OctaveMode() == TextFormat::Octave_Enabled)
    {
        flag = 1;
        Format.SetOctave_Disabled();
    }
    
    if(Format.AccidentalMode() == MusicalNote::TextFormat::AccidentalMode::Symbol)
    {
        if(Format.SpacingMode() != TextFormat::SpacingMode::Disabled)
        {
            uint8_t space_mode = Format.SpacingMode();

            Format.Spacing_Disabled();
            Flash::GetName(MusicalNote::Flash::Buffer,MusicalNote::Note(*this),Format);
            
            Format.SetSpacingMode(space_mode);
        }
        else
        {
            Flash::GetName(Flash::Buffer,MusicalNote::Note(*this),Format);
        }
    }
    else
    {
        if(Format.SpacingMode() != TextFormat::SpacingMode::Enabled)
        {
            uint8_t space_mode = Format.SpacingMode();

            Format.Spacing_Enabled();
            Flash::GetName(Flash::Buffer,MusicalNote::Note(*this),Format);
            
            Format.SetSpacingMode(space_mode);
        }
        else
        {
            Flash::GetName(Flash::Buffer,MusicalNote::Note(*this),Format);
        }
    }
    
    if(flag){Format.SetOctave_Enabled();}
    
    return Flash::Buffer;
}

char* Pitch::Name(char* buff, MusicalNote::TextFormat& Format)const
{
    bool flag = 0;
    if(Format.OctaveMode())
    {
        flag = 1;
        Format.SetOctave_Disabled();
    }
    
    if(Format.AccidentalMode() == MusicalNote::TextFormat::AccidentalMode::Symbol)
    {
        if(Format.SpacingMode() != TextFormat::SpacingMode::Disabled)
        {
            uint8_t space_mode = Format.SpacingMode();

            Format.Spacing_Disabled();
            Flash::GetName(buff,MusicalNote::Note(*this),Format);

            Format.SetSpacingMode(space_mode);
        }
        else
        {
            Flash::GetName(buff,MusicalNote::Note(*this),Format);
        }
    }
    else
    {
        if(Format.SpacingMode() != TextFormat::SpacingMode::Enabled)
        {
            uint8_t space_mode = Format.SpacingMode();
            Format.Spacing_Enabled();
            Flash::GetName(buff,MusicalNote::Pitch(*this),Format);
            Format.SetSpacingMode(space_mode);
        }
        else
        {
            Flash::GetName(buff,MusicalNote::Pitch(*this),Format);
        }
    }
    
    if(flag){Format.SetOctave_Enabled();}
    
    return buff;
}

const uint8_t Pitch::NotePitch() const
{
    if((_Letter == Letter::InvalidID)||(_Accidental == Accidental::InvalidID))
    {
        return INT8_MAX;
    }
    else
    {
        int8_t note_pitch = (MusicalNote::NotesArray[_Letter.ID()] + _Accidental.ID())%12;
        
        if(note_pitch<0){note_pitch+=12;}
        
        return note_pitch;
    }
}

const uint8_t Pitch::MidiPitch() const
{
    return NotePitch();
}

const Pitch::Type& Pitch::ID() const
{
    TypeBuffer = 4 + (9 * _Letter.ID()) + _Accidental.ID();
    return TypeBuffer;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator < (const Pitch &lhs, const Pitch &rhs)
{
    if(lhs.NotePitch() < rhs.NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator <= (const Pitch &lhs, const Pitch &rhs)
{
    if(lhs.NotePitch() <= rhs.NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator > (const Pitch &lhs, const Pitch &rhs)
{
    if(lhs.NotePitch() > rhs.NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator >= (const Pitch &lhs, const Pitch &rhs)
{
    if(lhs.NotePitch() >= rhs.NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator == (const Pitch &lhs, const Pitch &rhs)
{
    if(lhs.NotePitch() == rhs.NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator == (const Pitch::Type& lhs, const Pitch& rhs)
{
    if(Pitch(lhs).NotePitch() == rhs.NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator == (const Pitch &lhs, const Pitch::Type &rhs)
{
    if(lhs.NotePitch() == Pitch(rhs).NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator != (const Pitch &lhs, const Pitch &rhs)
{
    if(lhs.NotePitch() == rhs.NotePitch()){return 0;}
    return 1;
}

/*
Pitch& Pitch::operator+=(const MCC_MusicalInterval::Interval &rhs)
{
    
    Pitch buffer = (*this)+rhs;
    (*this) = buffer;

    return (*this);
}

Pitch Pitch::operator+(const MCC_MusicalInterval::Interval &rhs)
{
    Pitch tmp = (*this);
    
    int16_t base = NotePitch();
    
    if(rhs.Semitones() == MCC_MusicalInterval::InvalidInterval){return tmp;}
    
    for(uint8_t i = 0; i < rhs.GenericInterval()%7; i++)
    {
        tmp.Next();
    }

    uint8_t destination_pitch = (base + rhs.Semitones())%12;
    uint8_t current_pitch = tmp.NotePitch()%12;
    
    int8_t distance = current_pitch-destination_pitch;
    bool flag = 0;
    
    if(distance < 0){distance+=12;}
    if(distance>=6)
    {
        flag = 1;
        distance = destination_pitch-current_pitch;
        if(distance < 0){distance+=12;}
    }
    
    if(distance == 0){return tmp;}
    
    else if(destination_pitch<current_pitch)
    {
        if((destination_pitch+distance)%12 == current_pitch)
        {
            while( distance != 0 )
            {
                if(tmp.Flat() == 0)
                {
                    tmp = (*this);
                    return tmp;
                }
                current_pitch = tmp.NotePitch()%12;
                
                distance = current_pitch-destination_pitch;
                if(distance < 0){distance+=12;}
            }
            return tmp;
        }
        else if((current_pitch+distance)%12 == destination_pitch)
        {
            while( distance != 0 )
            {
                if(tmp.Sharp() == 0)
                {
                    tmp = (*this);
                    return tmp;
                }
                current_pitch = tmp.NotePitch()%12;
                
                distance = current_pitch-destination_pitch;
                if(distance < 0){distance+=12;}
            }
            return tmp;
        }
    }
    
    else if(destination_pitch>current_pitch)
    {
        if((destination_pitch+distance)%12 == current_pitch)
        {
            while( distance != 0 )
            {
                if(tmp.Flat() == 0)
                {
                    tmp = (*this);
                    return tmp;
                }
                current_pitch = tmp.NotePitch()%12;
                
                distance = current_pitch-destination_pitch;
                if(distance < 0){distance+=12;}
            }
            return tmp;
        }
        else if((current_pitch+distance)%12 == destination_pitch)
        {
            while( distance != 0 )
            {
                if(tmp.Sharp() == 0)
                {
                    tmp = (*this);
                    return tmp;
                }
                current_pitch = tmp.NotePitch()%12;
                
                distance = current_pitch-destination_pitch;
                if(distance < 0){distance+=12;}
            }
            return tmp;
        }
    }
    
    return tmp;
}


Pitch& Pitch::operator-=(const MCC_MusicalInterval::Interval &rhs)
{
    if(rhs.Semitones() == MCC_MusicalInterval::InvalidInterval){return (*this);}
    
    for(uint8_t i = 0; i < rhs.GenericInterval()%7; i++)
    {
        Previous();
    }
    
    for(uint8_t i = 0; i < rhs.IntervalQuality(); i++)
    {
        Flat();
    }
    
    return (*this);
}

Pitch Pitch::operator-(const MCC_MusicalInterval::Interval &rhs)
{
    Pitch tmp = (*this);
    
    if(rhs.Semitones() == MCC_MusicalInterval::InvalidInterval){return tmp;}
    
    for(uint8_t i = 0; i < rhs.GenericInterval()%7; i++)
    {
        tmp.Previous();
    }
    
    for(uint8_t i = 0; i < rhs.IntervalQuality(); i++)
    {
        tmp.Flat();
    }
    
    return tmp;
}
*/
