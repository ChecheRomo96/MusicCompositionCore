#include "TextFormat.h"
#include <MCC.h>

using namespace MusicCompositionCore::Core::MusicalCore::MusicalNote;

/////////////////////////////////////////////////////////////////////////
//    Declarations

	/////////////////////////////////////////////////////////////////////
	//    Default Format

		TextFormat MCC_MusicalNote::DefaultFormat;
	//
	/////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////
// Constructors, Destructors and Clear Function

	TextFormat::TextFormat()
	{
	    data = 
	    Accidental_SymbolMask |
	    Spacing_DisabledMask |
	    Octave_EnabledMask | 
	    Natural_DisabledMask;
	}
//
/////////////////////////////////////////////////////////////////////////
// Copy Constructor and assignment operator

	TextFormat::TextFormat(const TextFormat& source)
	{
		data = source.RawData();
	}

	TextFormat::TextFormat(uint8_t newData)
	{
	    data = newData;
	}

	TextFormat::TextFormat(bool AccidentalMode, bool OctaveEnabled, uint8_t SpacingMode, bool NaturalMode)
	{
	    SetAccidentalMode(AccidentalMode);
	    SetSpacingMode(SpacingMode);
	    SetOctaveMode(OctaveEnabled);
	    SetNaturalMode(NaturalMode);
	}

	TextFormat& TextFormat::operator=(const TextFormat& src)
	{
		data = src.RawData();
		return *this;
	}
//
/////////////////////////////////////////////////////////////////////////
// API

	/////////////////////////////////////////////////////////////////////////
	// Raw Data

		const uint8_t TextFormat::RawData() const
		{
		    return data;
		}

		void TextFormat::SetRawData(uint8_t RawData)
		{
		    data = RawData;
		}
	//
	/////////////////////////////////////////////////////////////////////////
	// Accidental Mode

		const bool TextFormat::AccidentalMode() const
		{
		    return (data>>BitNumbering_AccidentalMode)&1u;
		}

		void TextFormat::SetAccidentalMode(bool Mode)
		{
			data &=  ~(1u<<BitNumbering_AccidentalMode);
		    data |= (Mode<<BitNumbering_AccidentalMode);
		}

		void TextFormat::SetAccidental_Symbol()
		{
		    SetAccidentalMode(TextFormat::Accidental_Symbol);
		}

		void TextFormat::SetAccidental_Text()
		{
		    SetAccidentalMode(TextFormat::Accidental_Text);
		}
	//
	/////////////////////////////////////////////////////////////////////////
	// Octave Mode


		const bool TextFormat::OctaveMode() const
		{
		    return (data>>BitNumbering_OctaveMode)&1u;
		}

		void TextFormat::SetOctaveMode(bool Mode)
		{
			data &=  ~(1u<<BitNumbering_OctaveMode);
		    data |= (Mode<<BitNumbering_OctaveMode);
		}

		void TextFormat::SetOctave_Enabled()
		{
		    SetOctaveMode(TextFormat::Octave_Enabled);
		}

		void TextFormat::SetOctave_Disabled()
		{
		    SetOctaveMode(TextFormat::Octave_Disabled);
		}
	//
	/////////////////////////////////////////////////////////////////////////
	// Spacing Mode

		const uint8_t TextFormat::SpacingMode() const
		{
		    return (data>>BitNumbering_SpacingMode)&0b11;
		}

		void TextFormat::SetSpacingMode(uint8_t Mode)
		{
		    if(Mode>=0b11){return;}
		    
			data &= ~(0b11<<BitNumbering_SpacingMode);
		    data |=  (Mode<<BitNumbering_SpacingMode);
		}

		void TextFormat::SetSpacing_Enabled()
		{
		    SetSpacingMode(TextFormat::SpacingMode::Enabled);
		}

		void TextFormat::SetSpacing_Disabled()
		{
		    SetSpacingMode(TextFormat::SpacingMode::Disabled);
		}

		void TextFormat::SetSpacing_Justified()
		{
		    SetSpacingMode(TextFormat::SpacingMode::Justified);
		}
	//
	/////////////////////////////////////////////////////////////////////////
	// Natural Mode

		const bool TextFormat::NaturalMode() const
		{
		    return (data>>BitNumbering_NaturalMode)&1u;
		}

		void TextFormat::SetNaturalMode(bool Mode)
		{
			data &=  ~(1u<<BitNumbering_NaturalMode);
		    data |= (Mode<<BitNumbering_NaturalMode);
		}

		void TextFormat::SetNatural_Enabled()
		{
		    SetNaturalMode(TextFormat::NaturalMode::Enabled);
		}

		void TextFormat::SetNatural_Disabled()
		{
		    SetNaturalMode(TextFormat::NaturalMode::Disabled);
		}

	//
	/////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////
