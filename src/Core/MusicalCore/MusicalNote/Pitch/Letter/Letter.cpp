#include "Letter_Class.h"
#include "../Accidental/Accidental.h"
#include "../NotePitch_Class.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch;

Letter MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::Buffer;

Letter::Letter()
{
    _ID = InvalidID;
}

Letter::Letter(LetterType id)
{
    if( (id <= Letter::MaxIterator) && (id >= Letter::MinIterator) )
    {
        _ID = id;
    }
    else
    {
        _ID = InvalidID;
    }
}

Letter& Letter::operator=(LetterType id)
{
    if ((id <= Letter::MaxIterator) && (id >= Letter::MinIterator))
    {
        _ID = id;
    }
    else
    {
        _ID = InvalidID;
    }
    return (*this);
}

Letter::Letter(const Letter& source)
{
    _ID = source.ID();
}

Letter& Letter::operator=(const Letter& source)
{
    _ID = source.ID();
    return (*this);
}

Letter::Letter(const PitchClass& token)
{
    _ID = token.Letter().ID();
}

Letter& Letter::operator=(const PitchClass& token)
{
    _ID = token.Letter().ID();
    return (*this);
}

bool Letter::operator!=(const Letter& rhs) const
{
    if(_ID==rhs.ID()){return 0;}
    else{return 1;}
}

MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::operator const LetterType() const{return _ID;}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator < (const Letter &lhs, const Letter &rhs)
{
    if(lhs.ID() < rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator <= (const Letter &lhs, const Letter &rhs)
{
    if(lhs.ID() <= rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator > (const Letter &lhs, const Letter &rhs)
{
    if(lhs.ID() > rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator >= (const Letter &lhs, const Letter &rhs)
{
    if(lhs.ID() >= rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator == (const Letter &lhs, const Letter &rhs)
{
    if(lhs.ID() == rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator == (const Letter::LetterType &lhs, const Letter &rhs)
{
    if(Letter(lhs).ID() == rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator == (const Letter &lhs, const Letter::LetterType &rhs)
{
    if(lhs.ID() == Letter(rhs).ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator != (const Letter &lhs, const Letter &rhs)
{
    if(lhs.ID() == rhs.ID()){return 0;}
    return 1;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator != (const Letter::LetterType &lhs, const Letter &rhs)
{
    if(Letter(lhs).ID() == rhs.ID()){return 0;}
    return 1;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator != (const Letter &lhs, const Letter::LetterType &rhs)
{
    if(lhs.ID() == Letter(rhs).ID()){return 0;}
    return 1;
}

const Letter:: LetterType& Letter::ID() const
{
    return _ID;
}

MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::PitchClass& Letter::GenerateToken(const Accidental::AccidentalClass& source)
{
    PitchClass_Buffer = (*this);
    PitchClass_Buffer = source;
    return PitchClass_Buffer;
}

void Letter::Next()
{
    if(++_ID > Letter::MaxIterator)
    {
        _ID = Letter::MinIterator;
    }
}

void Letter::Previous()
{
    if(_ID == Letter::MinIterator)
    {
        _ID = Letter::MaxIterator;
    }
    else
    {
        _ID--;
    }
}
