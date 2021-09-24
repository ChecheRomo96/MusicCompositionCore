#include "TextFormat.h"
#include <MCC.h>

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

/////////////////////////////////////////////////////////////////////////
//    Declarations

	/////////////////////////////////////////////////////////////////////
	//    Default Format

		TextFormat::FormatClass TextFormat::DefaultFormat;
	//
	/////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////
// Constructors, Destructors and Clear Function

	TextFormat::FormatClass::FormatClass()
	{
	    data = 
	    TextFormat::AccidentalMode::Symbol_Mask |
	    TextFormat::SpacingMode::Disabled_Mask |
	    TextFormat::OctaveMode::Enabled_Mask | 
	    TextFormat::NaturalMode::Disabled_Mask;
	}
//
/////////////////////////////////////////////////////////////////////////
// Copy Constructor and assignment operator

	TextFormat::FormatClass::FormatClass(const FormatClass& source)
	{
		data = source.RawData();
	}

	TextFormat::FormatClass::FormatClass(uint8_t data)
	{
	    data = (data & 0x0F);
	}

	TextFormat::FormatClass::FormatClass(bool AccidentalMode, bool OctaveEnabled, uint8_t SpacingMode, bool NaturalMode)
	{
	    SetAccidentalMode(AccidentalMode);
	    SetSpacingMode(SpacingMode);
	    SetOctaveMode(OctaveEnabled);
	    SetNaturalMode(NaturalMode);
	}

	TextFormat::FormatClass& TextFormat::FormatClass::operator=(const TextFormat::FormatClass& src)
	{
		data = src.RawData();
		return *this;
	}
//
/////////////////////////////////////////////////////////////////////////
// API

	/////////////////////////////////////////////////////////////////////////
	// Raw Data

		const uint8_t TextFormat::FormatClass::RawData() const
		{
		    return data;
		}

		void TextFormat::FormatClass::SetRawData(uint8_t RawData)
		{
		    data = RawData;
		}
	//
	/////////////////////////////////////////////////////////////////////////
	// Accidental Mode

		const bool TextFormat::FormatClass::AccidentalMode() const
		{
		    return (data>>TextFormat::BitNumbering::AccidentalMode)&1u;
		}

		void TextFormat::FormatClass::SetAccidentalMode(bool Mode)
		{
			data &=  ~(1u<<TextFormat::BitNumbering::AccidentalMode);
		    data |= (Mode<<TextFormat::BitNumbering::AccidentalMode);
		}

		void TextFormat::FormatClass::Accidental_Symbol()
		{
		    SetAccidentalMode(TextFormat::AccidentalMode::Symbol);
		}

		void TextFormat::FormatClass::Accidental_Text()
		{
		    SetAccidentalMode(TextFormat::AccidentalMode::Text);
		}
	//
	/////////////////////////////////////////////////////////////////////////
	// Octave Mode


		const bool TextFormat::FormatClass::OctaveMode() const
		{
		    return (data>>TextFormat::BitNumbering::OctaveMode)&1u;
		}

		void TextFormat::FormatClass::SetOctaveMode(bool Mode)
		{
			data &=  ~(1u<<TextFormat::BitNumbering::OctaveMode);
		    data |= (Mode<<TextFormat::BitNumbering::OctaveMode);
		}

		void TextFormat::FormatClass::Octave_Enabled()
		{
		    SetOctaveMode(TextFormat::OctaveMode::Enabled);
		}

		void TextFormat::FormatClass::Octave_Disabled()
		{
		    SetOctaveMode(TextFormat::OctaveMode::Disabled);
		}
	//
	/////////////////////////////////////////////////////////////////////////
	// Spacing Mode

		const uint8_t TextFormat::FormatClass::SpacingMode() const
		{
		    return (data>>TextFormat::BitNumbering::SpacingMode)&0b11;
		}

		void TextFormat::FormatClass::SetSpacingMode(uint8_t Mode)
		{
		    if(Mode>=0b11){return;}
		    
			data &= ~(0b11<<TextFormat::BitNumbering::SpacingMode);
		    data |=  (Mode<<TextFormat::BitNumbering::SpacingMode);
		}

		void TextFormat::FormatClass::Spacing_Enabled()
		{
		    SetSpacingMode(TextFormat::SpacingMode::Enabled);
		}

		void TextFormat::FormatClass::Spacing_Disabled()
		{
		    SetSpacingMode(TextFormat::SpacingMode::Disabled);
		}

		void TextFormat::FormatClass::Spacing_Justified()
		{
		    SetSpacingMode(TextFormat::SpacingMode::Justified);
		}
	//
	/////////////////////////////////////////////////////////////////////////
	// Natural Mode

		const bool TextFormat::FormatClass::NaturalMode() const
		{
		    return (data>>TextFormat::BitNumbering::NaturalMode)&1u;
		}

		void TextFormat::FormatClass::SetNaturalMode(bool Mode)
		{
			data &=  ~(1u<<TextFormat::BitNumbering::NaturalMode);
		    data |= (Mode<<TextFormat::BitNumbering::NaturalMode);
		}

		void TextFormat::FormatClass::Natural_Enabled()
		{
		    SetNaturalMode(TextFormat::NaturalMode::Enabled);
		}

		void TextFormat::FormatClass::Natural_Disabled()
		{
		    SetNaturalMode(TextFormat::NaturalMode::Disabled);
		}

	//
	/////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////
