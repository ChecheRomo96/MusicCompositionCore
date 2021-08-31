#include "NoteFormat.h"
#include <MCC.h>

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

/////////////////////////////////////////////////////////////////////////
//    Declarations

	/////////////////////////////////////////////////////////////////////
	//    Default Format

		TextFormat::Format TextFormat::DefaultFormat;
	//
	/////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////
// Constructors, Destructors and Clear Function

	TextFormat::Format::Format()
	{
	    data =     TextFormat::AccidentalShort_Mask |
	    TextFormat::SpaceDisabled_Mask |
	    TextFormat::OctaveEnabled_Mask | TextFormat::NaturalDisabled_Mask;
	}

	TextFormat::Format::~Format()
	{
	    
	}

	void TextFormat::Format::Clear()
	{
	    
	}
//
/////////////////////////////////////////////////////////////////////////
// Copy Constructor and assignment operator

	TextFormat::Format::Format(const Format& source)
	{
		data = source.Data();
	}

	TextFormat::Format::Format(uint8_t data)
	{
	    data = (data & 0x0F);
	}

	TextFormat::Format::Format(bool AccidentalMode, bool OctaveEnabled, uint8_t SpacingMode, bool NaturalMode)
	{
	    Set_AccidentalMode(AccidentalMode);
	    Set_SpacingMode(SpacingMode);
	    Set_OctaveMode(OctaveEnabled);
	    Set_NaturalMode(NaturalMode);
	}

	TextFormat::Format& TextFormat::Format::operator=(const TextFormat::Format& src)
	{
		data = src.Data();
		return *this;
	}
//
/////////////////////////////////////////////////////////////////////////
// Operators

	TextFormat::Format::operator uint8_t() const
	{
	    return data;
	}
//
/////////////////////////////////////////////////////////////////////////
// Const Return Functions
	const uint8_t TextFormat::Format::Data() const
	{
	    return data;
	}

	const uint8_t TextFormat::Format::SpaceMode() const
	{
	    return (data>>TextFormat::SpaceMode_Bit)&0b11;
	}

	const bool TextFormat::Format::OctaveEnabled() const
	{
	    return (data>>TextFormat::OctaveEnabled_Bit)&1u;
	}

	const bool TextFormat::Format::AccidentalMode() const
	{
	    return (data>>TextFormat::AccidentalMode_Bit)&1u;
	}

	const bool TextFormat::Format::NaturalMode() const
	{
	    return (data>>TextFormat::NaturalMode_Bit)&1u;
	}
//
/////////////////////////////////////////////////////////////////////////
// Setters

	void TextFormat::Format::Set_SpacingMode(uint8_t x)
	{
	    if((x&0b11)==0b11){return;}
	    
	    data &= ~(0b11<<TextFormat::SpaceMode_Bit);
	    x &= 0b11;
	    data |= (x<<TextFormat::SpaceMode_Bit);
	}

	void TextFormat::Format::Set_SpaceEnabled()
	{
	    data &= ~(0b11<<TextFormat::SpaceMode_Bit);
	    data |= TextFormat::SpaceEnabled_Mask;
	}

	void TextFormat::Format::Set_SpaceDisabled()
	{
	    data &= ~(0b11<<TextFormat::SpaceMode_Bit);
	    data |= TextFormat::SpaceDisabled_Mask;
	}

	void TextFormat::Format::Set_SpaceJustified()
	{
	    data &= ~(0b11<<TextFormat::SpaceMode_Bit);
	    data |= TextFormat::SpaceJustified_Mask;
	}


	void TextFormat::Format::Set_OctaveMode(bool x)
	{
	    if(x == 1)
	    {
	        data |= (1u<<TextFormat::OctaveEnabled_Bit);
	    }
	    else
	    {
	        data &= ~(1u<<TextFormat::OctaveEnabled_Bit);
	    }
	}

	void TextFormat::Format::Set_OctaveEnabled()
	{
	    data |= (1u<<TextFormat::OctaveEnabled_Bit);
	}

	void TextFormat::Format::Set_OctaveDisabled()
	{
	    data &= ~(1u<<TextFormat::OctaveEnabled_Bit);
	}

	void TextFormat::Format::Set_AccidentalMode(bool x)
	{
	    if(x == 1)
	    {
	        data |= (1u<<TextFormat::AccidentalMode_Bit);
	    }
	    else
	    {
	        data &= ~(1u<<TextFormat::AccidentalMode_Bit);
	    }
	}

	void TextFormat::Format::Set_AccidentalShort()
	{
	    data |= (1u<<TextFormat::AccidentalMode_Bit);
	}

	void TextFormat::Format::Set_AccidentalLong()
	{
	    data &= ~(1u<<TextFormat::AccidentalMode_Bit);
	}



	void TextFormat::Format::Set_NaturalMode(bool x)
	{
	    if(x == 1)
	    {
	        data |= (1u<<TextFormat::NaturalMode_Bit);
	    }
	    else
	    {
	        data &= ~(1u<<TextFormat::NaturalMode_Bit);
	    }
	}

	void TextFormat::Format::Set_NaturalEnabled()
	{
	    data &= ~(1u<<TextFormat::NaturalMode_Bit);
	}

	void TextFormat::Format::Set_NaturalDisabled()
	{
	    data |= (1u<<TextFormat::NaturalMode_Bit);
	}

	//
	/////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////