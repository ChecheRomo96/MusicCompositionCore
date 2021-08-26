#include "NoteFormat.h"
#include <MCC.h>

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

/////////////////////////////////////////////////////////////////////////
//    Declarations

	/////////////////////////////////////////////////////////////////////
	//    Default Format

		NoteFormat::Format NoteFormat::DefaultFormat;
	//
	/////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////
// Constructors, Destructors and Clear Function

	NoteFormat::Format::Format()
	{
	    data =     NoteFormat::AccidentalShort_Mask |
	    NoteFormat::SpaceDisabled_Mask |
	    NoteFormat::OctaveEnabled_Mask | NoteFormat::NaturalDisabled_Mask;
	}

	NoteFormat::Format::~Format()
	{
	    
	}

	void NoteFormat::Format::Clear()
	{
	    
	}
//
/////////////////////////////////////////////////////////////////////////
// Copy Constructor and assignment operator

	NoteFormat::Format::Format(const Format& source)
	{
		data = source.Data();
	}

	NoteFormat::Format::Format(uint8_t data)
	{
	    data = (data & 0x0F);
	}

	NoteFormat::Format::Format(bool AccidentalMode, bool OctaveEnabled, uint8_t SpacingMode, bool NaturalMode)
	{
	    Set_AccidentalMode(AccidentalMode);
	    Set_SpacingMode(SpacingMode);
	    Set_OctaveMode(OctaveEnabled);
	    Set_NaturalMode(NaturalMode);
	}

	NoteFormat::Format& NoteFormat::Format::operator=(const NoteFormat::Format& src)
	{
		data = src.Data();
		return *this;
	}
//
/////////////////////////////////////////////////////////////////////////
// Operators

	NoteFormat::Format::operator uint8_t() const
	{
	    return data;
	}
//
/////////////////////////////////////////////////////////////////////////
// Const Return Functions
	const uint8_t NoteFormat::Format::Data() const
	{
	    return data;
	}

	const uint8_t NoteFormat::Format::SpaceMode() const
	{
	    return (data>>NoteFormat::SpaceMode_Bit)&0b11;
	}

	const bool NoteFormat::Format::OctaveEnabled() const
	{
	    return (data>>NoteFormat::OctaveEnabled_Bit)&1u;
	}

	const bool NoteFormat::Format::AccidentalMode() const
	{
	    return (data>>NoteFormat::AccidentalMode_Bit)&1u;
	}

	const bool NoteFormat::Format::NaturalMode() const
	{
	    return (data>>NoteFormat::NaturalMode_Bit)&1u;
	}
//
/////////////////////////////////////////////////////////////////////////
// Setters

	void NoteFormat::Format::Set_SpacingMode(uint8_t x)
	{
	    if((x&0b11)==0b11){return;}
	    
	    data &= ~(0b11<<NoteFormat::SpaceMode_Bit);
	    x &= 0b11;
	    data |= (x<<NoteFormat::SpaceMode_Bit);
	}

	void NoteFormat::Format::Set_SpaceEnabled()
	{
	    data &= ~(0b11<<NoteFormat::SpaceMode_Bit);
	    data |= NoteFormat::SpaceEnabled_Mask;
	}

	void NoteFormat::Format::Set_SpaceDisabled()
	{
	    data &= ~(0b11<<NoteFormat::SpaceMode_Bit);
	    data |= NoteFormat::SpaceDisabled_Mask;
	}

	void NoteFormat::Format::Set_SpaceJustified()
	{
	    data &= ~(0b11<<NoteFormat::SpaceMode_Bit);
	    data |= NoteFormat::SpaceJustified_Mask;
	}


	void NoteFormat::Format::Set_OctaveMode(bool x)
	{
	    if(x == 1)
	    {
	        data |= (1u<<NoteFormat::OctaveEnabled_Bit);
	    }
	    else
	    {
	        data &= ~(1u<<NoteFormat::OctaveEnabled_Bit);
	    }
	}

	void NoteFormat::Format::Set_OctaveEnabled()
	{
	    data |= (1u<<NoteFormat::OctaveEnabled_Bit);
	}

	void NoteFormat::Format::Set_OctaveDisabled()
	{
	    data &= ~(1u<<NoteFormat::OctaveEnabled_Bit);
	}

	void NoteFormat::Format::Set_AccidentalMode(bool x)
	{
	    if(x == 1)
	    {
	        data |= (1u<<NoteFormat::AccidentalMode_Bit);
	    }
	    else
	    {
	        data &= ~(1u<<NoteFormat::AccidentalMode_Bit);
	    }
	}

	void NoteFormat::Format::Set_AccidentalShort()
	{
	    data |= (1u<<NoteFormat::AccidentalMode_Bit);
	}

	void NoteFormat::Format::Set_AccidentalLong()
	{
	    data &= ~(1u<<NoteFormat::AccidentalMode_Bit);
	}



	void NoteFormat::Format::Set_NaturalMode(bool x)
	{
	    if(x == 1)
	    {
	        data |= (1u<<NoteFormat::NaturalMode_Bit);
	    }
	    else
	    {
	        data &= ~(1u<<NoteFormat::NaturalMode_Bit);
	    }
	}

	void NoteFormat::Format::Set_NaturalEnabled()
	{
	    data &= ~(1u<<NoteFormat::NaturalMode_Bit);
	}

	void NoteFormat::Format::Set_NaturalDisabled()
	{
	    data |= (1u<<NoteFormat::NaturalMode_Bit);
	}

	//
	/////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////