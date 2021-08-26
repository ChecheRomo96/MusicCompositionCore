#include "NotePitch.h"

#include "Letter/Letter.h"
#include "Accidental/Accidental.h"
#include "../Note_Class.h"
#include "../Format/NoteFormat.h"
//#include "../../MusicalInterval/MusicalInterval.h"

/////////////////////////////////////////////////////////////////////////
//  Notes Array

    const int8_t MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::NotesArray[7] = {0,2,4,5,7,9,11};
//
/////////////////////////////////////////////////////////////////////////
using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch;
using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

PitchClass MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::PitchClass_Buffer;

PitchClass::PitchClass()
{
    _Letter = Letter::InvalidID;
    _Accidental = Accidental::InvalidID;
}

PitchClass::PitchClass(PitchType token)
{
    if(token < Pitch::Count)
    {
        _Letter = Letter::LetterClass(token/9);
        _Accidental = Accidental::AccidentalClass((token%9) - 4);
    }
    else
    {
        _Letter = Letter::InvalidID;
        _Accidental = Accidental::InvalidID;
    }
}

PitchClass& PitchClass::operator=(PitchType token)
{
    if(token < Pitch::Count)
    {
        _Letter = Letter::LetterClass(token/9);
        _Accidental = Accidental::AccidentalClass((token%9) - 4);
    }
    else
    {
        _Letter = Letter::InvalidID;
        _Accidental = Accidental::InvalidID;
    }
    return (*this);
}

PitchClass::PitchClass(const Letter::LetterClass& note, const Accidental::AccidentalClass& accidental)
{
    _Letter = note;
    _Accidental = accidental;
}

PitchClass::PitchClass(const PitchClass& source)
{
    _Letter = source.Letter();
    _Accidental = source.Accidental();
}

PitchClass& PitchClass::operator=(const PitchClass& source)
{
    _Letter = source.Letter();
    _Accidental = source.Accidental();
    return (*this);
}


/*
PitchClass& PitchClass::operator+=(const MusicalInterval::Interval &rhs)
{
    PitchClass_Buffer = (*this)+rhs;
    (*this) = PitchClass_Buffer;
    return (*this);
}

PitchClass PitchClass::operator+(const MusicalInterval::Interval &rhs) const
{
    PitchClass tmp = (*this);
    
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


PitchClass& PitchClass::operator-=(const MusicalInterval::Interval &rhs)
{
    PitchClass_Buffer = (*this)-rhs;
    (*this) = PitchClass_Buffer;
    return (*this);
}

PitchClass PitchClass::operator-(const MusicalInterval::Interval &rhs) const
{
    // Checking if the provided interval is valid, else return the note as is
    if(rhs.Semitones() == MCC_MusicalInterval::InvalidInterval){return (*this);}

    // Make a copy of this instance into an object called tmp
    PitchClass tmp = (*this);
    
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
}*/


PitchClass::PitchClass(const Letter::LetterClass& source)
{
    _Letter = source;
    _Accidental = Accidental::InvalidID;
}

PitchClass& PitchClass::operator=(const Letter::LetterClass& source)
{
    _Letter = source;
    return (*this);
}

PitchClass::PitchClass(const Accidental::AccidentalClass& source)
{
    _Accidental = source;
    _Letter = Letter::InvalidID;
}

PitchClass& PitchClass::operator=(const Accidental::AccidentalClass& source)
{
    _Accidental = source;
    return(*this);
}

PitchClass::operator uint8_t() const
{
    if((_Letter == Letter::InvalidID)||(_Accidental == Accidental::InvalidID))
    {
        return Count;
    }
    return (_Letter.ID() * 5) + _Accidental.ID();
}

void PitchClass::Set_Letter(const Letter::LetterClass& source)
{
    _Letter = source;
}

const Letter::LetterClass& PitchClass::Letter() const
{
    return _Letter;
}

void PitchClass::Set_Accidental(const Accidental::AccidentalClass& source)
{
    _Accidental = source;
}

const Accidental::AccidentalClass& PitchClass::Accidental() const
{
    return _Accidental;
}

bool PitchClass::Sharp()
{
    return _Accidental.Sharp();
}

bool PitchClass::Flat()
{
    return _Accidental.Flat();
}

void PitchClass::Next()
{
    return _Letter.Next();
}

void PitchClass::Previous()
{
    return _Letter.Previous();
}

const char* PitchClass::Name(MusicalNote::NoteFormat::Format& Format)const
{
    bool flag = 0;
    if(Format.OctaveEnabled())
    {
        flag = 1;
        Format.Set_OctaveDisabled();
    }
    
    if(Format.AccidentalMode() == MusicalNote::NoteFormat::AccidentalShort)
    {
        if(Format.SpaceMode() != NoteFormat::SpaceDisabled)
        {
            uint8_t space_mode = Format.SpaceMode();
            Format.Set_SpaceDisabled();
            Flash::GetName(MusicalNote::Flash::Buffer,MusicalNote::Note(*this),Format);
            Format.Set_SpacingMode(space_mode);
        }
        else
        {
            Flash::GetName(Flash::Buffer,MusicalNote::Note(*this),Format);
        }
    }
    else
    {
        if(Format.SpaceMode() != NoteFormat::SpaceEnabled)
        {
            uint8_t space_mode = Format.SpaceMode();
            Format.Set_SpaceEnabled();
            Flash::GetName(Flash::Buffer,MusicalNote::Note(*this),Format);
            Format.Set_SpacingMode(space_mode);
        }
        else
        {
            Flash::GetName(Flash::Buffer,MusicalNote::Note(*this),Format);
        }
    }
    
    if(flag){Format.Set_OctaveEnabled();}
    
    return Flash::Buffer;
}

char* PitchClass::Name(char* buff, MusicalNote::NoteFormat::Format& Format)const
{
    bool flag = 0;
    if(Format.OctaveEnabled())
    {
        flag = 1;
        Format.Set_OctaveDisabled();
    }
    
    if(Format.AccidentalMode() == MusicalNote::NoteFormat::AccidentalShort)
    {
        if(Format.SpaceMode() != NoteFormat::SpaceDisabled)
        {
            uint8_t space_mode = Format.SpaceMode();
            Format.Set_SpaceDisabled();
            Flash::GetName(buff,MusicalNote::Note(*this),Format);
            Format.Set_SpacingMode(space_mode);
        }
        else
        {
            Flash::GetName(buff,MusicalNote::Note(*this),Format);
        }
    }
    else
    {
        if(Format.SpaceMode() != NoteFormat::SpaceEnabled)
        {
            uint8_t space_mode = Format.SpaceMode();
            Format.Set_SpaceEnabled();
            Flash::GetName(buff,MusicalNote::Pitch::PitchClass(*this),Format);
            Format.Set_SpacingMode(space_mode);
        }
        else
        {
            Flash::GetName(buff,MusicalNote::Pitch::PitchClass(*this),Format);
        }
    }
    
    if(flag){Format.Set_OctaveEnabled();}
    
    return buff;
}

const uint8_t PitchClass::NotePitch() const
{
    if((_Letter == Letter::InvalidID)||(_Accidental == Accidental::InvalidID))
    {
        return INT8_MAX;
    }
    else
    {
        int8_t note_pitch = (MusicalNote::Pitch::NotesArray[_Letter.ID()] + _Accidental.ID())%12;
        
        if(note_pitch<0){note_pitch+=12;}
        
        return note_pitch;
    }
}

const uint8_t PitchClass::MidiPitch() const
{
    return NotePitch();
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator < (const PitchClass &lhs, const PitchClass &rhs)
{
    if(lhs.NotePitch() < rhs.NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator <= (const PitchClass &lhs, const PitchClass &rhs)
{
    if(lhs.NotePitch() <= rhs.NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator > (const PitchClass &lhs, const PitchClass &rhs)
{
    if(lhs.NotePitch() > rhs.NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator >= (const PitchClass &lhs, const PitchClass &rhs)
{
    if(lhs.NotePitch() >= rhs.NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator == (const PitchClass &lhs, const PitchClass &rhs)
{
    if(lhs.NotePitch() == rhs.NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator == (const PitchType &lhs, const PitchClass &rhs)
{
    if(PitchClass(lhs).NotePitch() == rhs.NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator == (const PitchClass &lhs, const PitchType &rhs)
{
    if(lhs.NotePitch() == PitchClass(rhs).NotePitch()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator != (const PitchClass &lhs, const PitchClass &rhs)
{
    if(lhs.NotePitch() == rhs.NotePitch()){return 0;}
    return 1;
}
/*
PitchClass& PitchClass::operator+=(const MCC_MusicalInterval::Interval &rhs)
{
    
    PitchClass buffer = (*this)+rhs;
    (*this) = buffer;

    return (*this);
}

PitchClass PitchClass::operator+(const MCC_MusicalInterval::Interval &rhs)
{
    PitchClass tmp = (*this);
    
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


PitchClass& PitchClass::operator-=(const MCC_MusicalInterval::Interval &rhs)
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

PitchClass PitchClass::operator-(const MCC_MusicalInterval::Interval &rhs)
{
    PitchClass tmp = (*this);
    
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
