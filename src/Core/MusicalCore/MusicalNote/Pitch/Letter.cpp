#include "NotePitch_Class.h"
#include "../Flash/NoteFlash.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

Pitch::Letter MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::Buffer;

Pitch::Letter::Letter()
{
    _ID = InvalidID;
}

Pitch::Letter::Letter(LetterType id)
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

Pitch::Letter& Pitch::Letter::operator=(LetterType id)
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

Pitch::Letter::Letter(const Letter& source)
{
    _ID = source.ID();
}

Pitch::Letter& Pitch::Letter::operator=(const Pitch::Letter& source)
{
    _ID = source.ID();
    return (*this);
}

Pitch::Letter::Letter(const Pitch& NewPitch)
{
    _ID = NewPitch.GetLetter().ID();
}

Pitch::Letter& Pitch::Letter::operator=(const Pitch& token)
{
    _ID = token.GetLetter().ID();
    return (*this);
}

bool Pitch::Letter::operator!=(const Letter& rhs) const
{
    if(_ID==rhs.ID()){return 0;}
    else{return 1;}
}

MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Letter::operator const LetterType() const{return _ID;}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator < (const Pitch::Letter &lhs, const Pitch::Letter &rhs)
{
    if(lhs.ID() < rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator <= (const Pitch::Letter &lhs, const Pitch::Letter &rhs)
{
    if(lhs.ID() <= rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator > (const Pitch::Letter &lhs, const Pitch::Letter &rhs)
{
    if(lhs.ID() > rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator >= (const Pitch::Letter &lhs, const Pitch::Letter &rhs)
{
    if(lhs.ID() >= rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator == (const Pitch::Letter &lhs, const Pitch::Letter &rhs)
{
    if(lhs.ID() == rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator == (const Pitch::Letter::LetterType &lhs, const Pitch::Letter &rhs)
{
    if(Pitch::Letter(lhs).ID() == rhs.ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator == (const Pitch::Letter &lhs, const Pitch::Letter::LetterType &rhs)
{
    if(lhs.ID() == Pitch::Letter(rhs).ID()){return 1;}
    return 0;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator != (const Pitch::Letter &lhs, const Pitch::Letter &rhs)
{
    if(lhs.ID() == rhs.ID()){return 0;}
    return 1;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator != (const Pitch::Letter::LetterType &lhs, const Pitch::Letter &rhs)
{
    if(Pitch::Letter(lhs).ID() == rhs.ID()){return 0;}
    return 1;
}

bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator != (const Pitch::Letter &lhs, const Pitch::Letter::LetterType &rhs)
{
    if(lhs.ID() == Pitch::Letter(rhs).ID()){return 0;}
    return 1;
}


char* Pitch::Letter::Name(char* buff)
{
    return MusicalNote::Flash::GetLetterText(buff,*this);
}

const char* Pitch::Letter::Name() const
{
    return MusicalNote::Flash::GetLetterText(*this);
}

const Pitch::Letter::LetterType& Pitch::Letter::ID() const
{
    return _ID;
}

MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch& Pitch::Letter::GenerateToken(const Pitch::Accidental& source)
{
    PitchBuffer = Pitch(ID(), source.ID());
    return PitchBuffer;
}

void Pitch::Letter::Next()
{
    if(++_ID > Letter::MaxIterator)
    {
        _ID = Letter::MinIterator;
    }
}

void Pitch::Letter::Previous()
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
