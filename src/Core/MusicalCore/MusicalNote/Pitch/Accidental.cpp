
#include "NotePitch_Class.h"
#include "../Flash/NoteFlash.h"
#include <CPVector.h>

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

Pitch::Accidental MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::Buffer;

Pitch::Accidental::Accidental()
{
	_ID = InvalidID;
}

Pitch::Accidental::Accidental(Pitch::Accidental::AccidentalType id)
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

Pitch::Accidental& Pitch::Accidental::operator=(Pitch::Accidental::AccidentalType id)
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

Pitch::Accidental::Accidental(const Pitch::Accidental& source)
{
	_ID = source.ID();
}

Pitch::Accidental& Pitch::Accidental::operator=(const Pitch::Accidental& source)
{
	_ID = source.ID();
	return (*this);
}

Pitch::Accidental::Accidental(const Pitch& Pitch)
{
	_ID = Pitch.GetAccidental().ID();
}

Pitch::Accidental& Pitch::Accidental::operator=(const Pitch& Pitch)
{
	_ID = Pitch.GetAccidental().ID();
	return (*this);
}

bool Pitch::Accidental::operator!=(const Pitch::Accidental& rhs) const
{
	if(_ID==rhs.ID()){return 0;}
	else{return 1;}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operadores

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator < (const Pitch::Accidental &lhs, const Pitch::Accidental &rhs)
		{
		    if(lhs.ID() < rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator < (const Pitch::Accidental::AccidentalType &lhs, const Pitch::Accidental &rhs)
		{
		    if(lhs < rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator < (const Pitch::Accidental &lhs, const Pitch::Accidental::AccidentalType &rhs)
		{
		    if(lhs.ID() < rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator <= (const Pitch::Accidental &lhs, const Pitch::Accidental &rhs)
		{
		    if(lhs.ID() <= rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator <= (const Pitch::Accidental::AccidentalType &lhs, const Pitch::Accidental &rhs)
		{
		    if(lhs <= rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator <= (const Pitch::Accidental &lhs, const Pitch::Accidental::AccidentalType &rhs)
		{
		    if(lhs.ID() <= rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator > (const Pitch::Accidental &lhs, const Pitch::Accidental &rhs)
		{
		    if(lhs.ID() > rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator > (const Pitch::Accidental::AccidentalType &lhs, const Pitch::Accidental &rhs)
		{
		    if(lhs > rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator > (const Pitch::Accidental &lhs, const Pitch::Accidental::AccidentalType &rhs)
		{
		    if(lhs.ID() > rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator >= (const Pitch::Accidental &lhs, const Pitch::Accidental &rhs)
		{
		    if(lhs.ID() >= rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator >= (const Pitch::Accidental::AccidentalType &lhs, const Pitch::Accidental &rhs)
		{
		    if(lhs >= rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator >= (const Pitch::Accidental &lhs, const Pitch::Accidental::AccidentalType &rhs)
		{
		    if(lhs.ID() >= rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator == (const Pitch::Accidental &lhs, const Pitch::Accidental &rhs)
		{
		    if(lhs.ID() == rhs.ID()){return 1;}
		    return 0;
		}


		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator == (const Pitch::Accidental::AccidentalType &lhs, const Pitch::Accidental &rhs)
		{
		    if(lhs == rhs.ID()){return 1;}
		    return 0;
		}


		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator == (const Pitch::Accidental &lhs, const Pitch::Accidental::AccidentalType &rhs)
		{
		    if(lhs.ID() == rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator != (const Pitch::Accidental &lhs, const Pitch::Accidental &rhs)
		{
		    if(lhs.ID() == rhs.ID()){return 0;}
		    return 1;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator != (const Pitch::Accidental::AccidentalType &lhs, const Pitch::Accidental &rhs)
		{
		    if(lhs == rhs.ID()){return 0;}
		    return 1;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::operator != (const Pitch::Accidental &lhs, const Pitch::Accidental::AccidentalType &rhs)
		{
		    if(lhs.ID() == rhs){return 0;}
		    return 1;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* Pitch::Accidental::Name(char* buff)
{
    return MusicalNote::Flash::GetAccidentalText(buff,*this);
}

const char* Pitch::Accidental::Name() const
{
    return MusicalNote::Flash::GetAccidentalText(*this);
}

void Pitch::Accidental::Set_ID(const AccidentalType& source)
{
	if ((source >= Accidental::MinIterator) && (source <= Accidental::MaxIterator))
	{
		_ID = source;
	}
	else
	{
		_ID = Accidental::InvalidID;
	}
}

const Pitch::Accidental::AccidentalType& Pitch::Accidental::ID() const
{
	return _ID;
}

Pitch& Pitch::Accidental::GenerateToken(const Pitch::Letter& source)
{
    return Pitch::PitchBuffer = Pitch(source,(*this));
}

bool Pitch::Accidental::AddSharp()
{
	if(_ID != Accidental::QuadrupleSharp)
	{	
		_ID++;
		return 1;
	}
	return 0;
}

bool Pitch::Accidental::AddFlat()
{
	if(_ID != QuadrupleFlat)
	{	
		_ID--;
		return 1;
	}
	return 0;
}