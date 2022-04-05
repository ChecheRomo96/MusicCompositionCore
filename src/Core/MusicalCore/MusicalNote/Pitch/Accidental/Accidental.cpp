#include "Accidental.h"

#include "../Letter/Letter.h"
#include "../NotePitch_Class.h"
#include "../../Flash/NoteFlash.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch;

Accidental MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::Buffer;

Accidental::Accidental()
{
	_ID = InvalidID;
}

Accidental::Accidental(AccidentalType id)
{
    if((id<=Accidental::MaxIterator)&&(id>=Accidental::MinIterator))
	{
		_ID = id;
	}
	else
	{
		_ID = InvalidID;
	}
}

Accidental& Accidental::operator=(AccidentalType id)
{
    if((id<=MaxIterator)&&(id>=MinIterator))
	{
		_ID = id;
	}
	else
	{
		_ID = InvalidID;
	}
	return (*this);
}

Accidental::Accidental(const Accidental& source)
{
	_ID = source.ID();
}

Accidental& Accidental::operator=(const Accidental& source)
{
	_ID = source.ID();
	return (*this);
}

Accidental::Accidental(const PitchClass& Pitch)
{
	_ID = Pitch.Accidental().ID();
}

Accidental& Accidental::operator=(const PitchClass& Pitch)
{
	_ID = Pitch.Accidental().ID();
	return (*this);
}

bool Accidental::operator!=(const Accidental& rhs) const
{
	if(_ID==rhs.ID()){return 0;}
	else{return 1;}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operadores

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator < (const Accidental &lhs, const Accidental &rhs)
		{
		    if(lhs.ID() < rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator < (const Accidental::AccidentalType &lhs, const Accidental &rhs)
		{
		    if(lhs < rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator < (const Accidental &lhs, const Accidental::AccidentalType &rhs)
		{
		    if(lhs.ID() < rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator <= (const Accidental &lhs, const Accidental &rhs)
		{
		    if(lhs.ID() <= rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator <= (const Accidental::AccidentalType &lhs, const Accidental &rhs)
		{
		    if(lhs <= rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator <= (const Accidental &lhs, const Accidental::AccidentalType &rhs)
		{
		    if(lhs.ID() <= rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator > (const Accidental &lhs, const Accidental &rhs)
		{
		    if(lhs.ID() > rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator > (const Accidental::AccidentalType &lhs, const Accidental &rhs)
		{
		    if(lhs > rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator > (const Accidental &lhs, const Accidental::AccidentalType &rhs)
		{
		    if(lhs.ID() > rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator >= (const Accidental &lhs, const Accidental &rhs)
		{
		    if(lhs.ID() >= rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator >= (const Accidental::AccidentalType &lhs, const Accidental &rhs)
		{
		    if(lhs >= rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator >= (const Accidental &lhs, const Accidental::AccidentalType &rhs)
		{
		    if(lhs.ID() >= rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator == (const Accidental &lhs, const Accidental &rhs)
		{
		    if(lhs.ID() == rhs.ID()){return 1;}
		    return 0;
		}


		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator == (const Accidental::AccidentalType &lhs, const Accidental &rhs)
		{
		    if(lhs == rhs.ID()){return 1;}
		    return 0;
		}


		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator == (const Accidental &lhs, const Accidental::AccidentalType &rhs)
		{
		    if(lhs.ID() == rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator != (const Accidental &lhs, const Accidental &rhs)
		{
		    if(lhs.ID() == rhs.ID()){return 0;}
		    return 1;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator != (const Accidental::AccidentalType &lhs, const Accidental &rhs)
		{
		    if(lhs == rhs.ID()){return 0;}
		    return 1;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::operator != (const Accidental &lhs, const Accidental::AccidentalType &rhs)
		{
		    if(lhs.ID() == rhs){return 0;}
		    return 1;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* Accidental::Name(char* buff)
{
    return MusicalNote::Flash::GetAccidentalText(buff,*this);
}

const char* Accidental::Name() const
{
    return MusicalNote::Flash::GetAccidentalText(*this);
}

void Accidental::Set_ID(const AccidentalType& source)
{
	if ((source >= Accidental::MinIterator) && (source <= Accidental::MaxIterator))
	{
		_ID = source;
	}
	else
	{
		_ID = InvalidPitch;
	}
}

const Accidental::AccidentalType& Accidental::ID() const
{
	return _ID;
}

MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::PitchClass& Accidental::GenerateToken(const Pitch::Letter& source)
{
    return Pitch::PitchClass_Buffer = PitchClass(source,(*this));
}

bool Accidental::AddSharp()
{
	if(_ID != QuadrupleSharp)
	{	
		_ID++;
		return 1;
	}
	return 0;
}

bool Accidental::AddFlat()
{
	if(_ID != QuadrupleFlat)
	{	
		_ID--;
		return 1;
	}
	return 0;
}