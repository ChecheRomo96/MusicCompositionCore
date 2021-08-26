#include "Letter_Class.h"
#include "../Accidental/Accidental.h"
#include "../NotePitch_Class.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter;
using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch;

LetterClass MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::Letter_Buffer;

LetterClass::LetterClass()
{
    _ID = InvalidID;
}

LetterClass::LetterClass(LetterType id)
{
    if(id<Count)
    {
        _ID = id;
    }
    else
    {
        _ID = InvalidID;
    }
}

LetterClass& LetterClass::operator=(LetterType id)
{
    if(id<Count)
    {
        _ID = id;
    }
    else
    {
        _ID = InvalidID;
    }
    return (*this);
}

LetterClass::LetterClass(const LetterClass& source)
{
    _ID = source.ID();
}

LetterClass& LetterClass::operator=(const LetterClass& source)
{
    _ID = source.ID();
    return (*this);
}

LetterClass::LetterClass(const PitchClass& token)
{
    _ID = token.Letter().ID();
}

LetterClass& LetterClass::operator=(const PitchClass& token)
{
    _ID = token.Letter().ID();
    return (*this);
}

bool LetterClass::operator!=(const LetterClass& rhs) const
{
    if(_ID==rhs.ID()){return 0;}
    else{return 1;}
}

MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::LetterClass::operator const LetterType() const{return _ID;}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::operator < (const LetterClass &lhs, const LetterClass &rhs)
{
    if(lhs.ID() < rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::operator <= (const LetterClass &lhs, const LetterClass &rhs)
{
    if(lhs.ID() <= rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::operator > (const LetterClass &lhs, const LetterClass &rhs)
{
    if(lhs.ID() > rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::operator >= (const LetterClass &lhs, const LetterClass &rhs)
{
    if(lhs.ID() >= rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::operator == (const LetterClass &lhs, const LetterClass &rhs)
{
    if(lhs.ID() == rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::operator == (const LetterType &lhs, const LetterClass &rhs)
{
    if(LetterClass(lhs).ID() == rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::operator == (const LetterClass &lhs, const LetterType &rhs)
{
    if(lhs.ID() == LetterClass(rhs).ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::operator != (const LetterClass &lhs, const LetterClass &rhs)
{
    if(lhs.ID() == rhs.ID()){return 0;}
    return 1;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::operator != (const LetterType &lhs, const LetterClass &rhs)
{
    if(LetterClass(lhs).ID() == rhs.ID()){return 0;}
    return 1;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::operator != (const LetterClass &lhs, const LetterType &rhs)
{
    if(lhs.ID() == LetterClass(rhs).ID()){return 0;}
    return 1;
}

const LetterType& LetterClass::ID() const
{
    return _ID;
}

MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::PitchClass& LetterClass::GenerateToken(const Accidental::AccidentalClass& source)
{
    PitchClass_Buffer = (*this);
    PitchClass_Buffer = source;
    return PitchClass_Buffer;
}

void LetterClass::Next()
{
    if(++_ID == Count)
    {
        _ID = 0;
    }
}

void LetterClass::Previous()
{
    if(_ID-- == 0)
    {
        _ID = Count-1;
    }
}
