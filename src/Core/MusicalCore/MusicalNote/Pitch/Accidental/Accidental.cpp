#include "Accidental.h"

#include "../Letter/Letter.h"
#include "../NotePitch_Class.h"
#include "../../Flash/NoteFlash.h"

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental;
using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch;

AccidentalClass MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::AccidentalClass_Buffer;

AccidentalClass::AccidentalClass()
{
	_ID = InvalidID;
}

AccidentalClass::AccidentalClass(AccidentalType id)
{
    if((id<=Accidental::Max)&&(id>=Accidental::Min))
	{
		_ID = id;
	}
	else
	{
		_ID = InvalidID;
	}
}

AccidentalClass& AccidentalClass::operator=(AccidentalType id)
{
    if((id<=Max)&&(id>=Min))
	{
		_ID = id;
	}
	else
	{
		_ID = InvalidID;
	}
	return (*this);
}

AccidentalClass::AccidentalClass(const AccidentalClass& source)
{
	_ID = source.ID();
}

AccidentalClass& AccidentalClass::operator=(const AccidentalClass& source)
{
	_ID = source.ID();
	return (*this);
}

AccidentalClass::AccidentalClass(const PitchClass& Pitch)
{
	_ID = Pitch.Accidental();
}

AccidentalClass& AccidentalClass::operator=(const PitchClass& Pitch)
{
	_ID = Pitch.Accidental();
	return (*this);
}

AccidentalClass::operator AccidentalType() const
{
	return _ID;
}

bool AccidentalClass::operator!=(const AccidentalClass& rhs) const
{
	if(_ID==rhs.ID()){return 0;}
	else{return 1;}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operadores

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator < (const AccidentalClass &lhs, const AccidentalClass &rhs)
		{
		    if(lhs.ID() < rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator < (const AccidentalType &lhs, const AccidentalClass &rhs)
		{
		    if(lhs < rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator < (const AccidentalClass &lhs, const AccidentalType &rhs)
		{
		    if(lhs.ID() < rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator <= (const AccidentalClass &lhs, const AccidentalClass &rhs)
		{
		    if(lhs.ID() <= rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator <= (const AccidentalType &lhs, const AccidentalClass &rhs)
		{
		    if(lhs <= rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator <= (const AccidentalClass &lhs, const AccidentalType &rhs)
		{
		    if(lhs.ID() <= rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator > (const AccidentalClass &lhs, const AccidentalClass &rhs)
		{
		    if(lhs.ID() > rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator > (const AccidentalType &lhs, const AccidentalClass &rhs)
		{
		    if(lhs > rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator > (const AccidentalClass &lhs, const AccidentalType &rhs)
		{
		    if(lhs.ID() > rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator >= (const AccidentalClass &lhs, const AccidentalClass &rhs)
		{
		    if(lhs.ID() >= rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator >= (const AccidentalType &lhs, const AccidentalClass &rhs)
		{
		    if(lhs >= rhs.ID()){return 1;}
		    return 0;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator >= (const AccidentalClass &lhs, const AccidentalType &rhs)
		{
		    if(lhs.ID() >= rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator == (const AccidentalClass &lhs, const AccidentalClass &rhs)
		{
		    if(lhs.ID() == rhs.ID()){return 1;}
		    return 0;
		}


		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator == (const AccidentalType &lhs, const AccidentalClass &rhs)
		{
		    if(lhs == rhs.ID()){return 1;}
		    return 0;
		}


		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator == (const AccidentalClass &lhs, const AccidentalType &rhs)
		{
		    if(lhs.ID() == rhs){return 1;}
		    return 0;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator != (const AccidentalClass &lhs, const AccidentalClass &rhs)
		{
		    if(lhs.ID() == rhs.ID()){return 0;}
		    return 1;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator != (const AccidentalType &lhs, const AccidentalClass &rhs)
		{
		    if(lhs == rhs.ID()){return 0;}
		    return 1;
		}

		bool MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::Accidental::operator != (const AccidentalClass &lhs, const AccidentalType &rhs)
		{
		    if(lhs.ID() == rhs){return 0;}
		    return 1;
		}
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* AccidentalClass::Name(char* buff)
{
    return MusicalNote::Flash::GetAccidentalName(buff,*this);
}

const char* AccidentalClass::Name() const
{
    return MusicalNote::Flash::GetAccidentalName(*this);
}

const AccidentalType& AccidentalClass::ID() const
{
	return _ID;
}

MusicCompositionCore::Core::MusicalCore::MusicalNote::Pitch::PitchClass& AccidentalClass::GenerateToken(const Pitch::Letter::LetterClass& source)
{
    return Pitch::PitchClass_Buffer = PitchClass(source,(*this));
}

bool AccidentalClass::Sharp()
{
	if(_ID != QuadrupleSharp)
	{	
		_ID++;
		return 1;
	}
	return 0;
}

bool AccidentalClass::Flat()
{
	if(_ID != QuadrupleFlat)
	{	
		_ID--;
		return 1;
	}
	return 0;
}