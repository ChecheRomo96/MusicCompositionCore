#ifndef MCC_NOTE_FORMAT_CLASS_H
#define MCC_NOTE_FORMAT_CLASS_H

	#include <MCC_BuildSettings.h>

	#include "TextFormat.h"

	namespace MusicCompositionCore::MusicalCore::MusicalNote
	{
		class TextFormat
		{
			public:
				/////////////////////////////////////////////////////////////////////////
				// Constants and Bitmasks

					static constexpr uint8_t BitNumbering_AccidentalMode = 0;
					static constexpr uint8_t BitNumbering_OctaveMode = 1;
					static constexpr uint8_t BitNumbering_SpacingMode = 2;
					static constexpr uint8_t BitNumbering_NaturalMode = 4;

					static constexpr bool Accidental_Symbol = 1;
					static constexpr bool Accidental_Text = 0;
					static constexpr uint8_t Accidental_SymbolMask = 0b00000001;
					static constexpr uint8_t Accidental_TextMask = 0;

					static constexpr bool Octave_Enabled = 1;
					static constexpr bool Octave_Disabled = 0;
					static constexpr uint8_t Octave_EnabledMask = 0b000010;
					static constexpr uint8_t Octave_DisabledMask = 0;

					static constexpr uint8_t Spacing_Enabled = 0b10;
					static constexpr uint8_t Spacing_Justified = 0b01;
					static constexpr uint8_t Spacing_Disabled = 0;

					static constexpr uint8_t Spacing_EnabledMask = 0b000001000;
					static constexpr uint8_t Spacing_JustifiedMask = 0b000000100;
					static constexpr uint8_t Spacing_DisabledMask = 0;

					static constexpr bool Natural_Disabled = 1;
					static constexpr bool Natural_Enabled = 0;
					static constexpr uint8_t Natural_DisabledMask = 0b00010000;
					static constexpr uint8_t Natural_EnabledMask = 0;
				//
				/////////////////////////////////////////////////////////////////////////
			private:
				/////////////////////////////////////////////////////////////////////////
				// Fields

					uint8_t data;
				//
				/////////////////////////////////////////////////////////////////////////
			public:
				/////////////////////////////////////////////////////////////////////////
				// Constructors, Destructors and Clear Function

					TextFormat();
				//
				/////////////////////////////////////////////////////////////////////////
				// Copy Constructor and assignment operator

					TextFormat(const TextFormat& source);
					TextFormat(uint8_t data);
					TextFormat(bool AccidentalMode, bool OctaveEnabled, uint8_t Spacing, bool NaturalMode = Natural_Disabled);
					TextFormat& operator=(const TextFormat& src);
				//
				/////////////////////////////////////////////////////////////////////////
				// API

					/////////////////////////////////////////////////////////////////////
					// Raw Data 

						const uint8_t RawData() const;
						void SetRawData(uint8_t RawData);
					//
					/////////////////////////////////////////////////////////////////////
					// Accidental Mode

						const bool AccidentalMode() const;
						void SetAccidentalMode(bool x);
						void SetAccidental_Symbol();
						void SetAccidental_Text();
					//
					/////////////////////////////////////////////////////////////////////
					// Octave Mode

						const bool OctaveMode() const;
						void SetOctaveMode(bool x);
						void SetOctave_Enabled();
						void SetOctave_Disabled();
					//
					/////////////////////////////////////////////////////////////////////
					// Spacing Mode

						const uint8_t SpacingMode() const;
						void SetSpacingMode(uint8_t x);
						void SetSpacing_Enabled();
						void SetSpacing_Disabled();
						void SetSpacing_Justified();
					//
					/////////////////////////////////////////////////////////////////////
					// Natural Mode

						const bool NaturalMode() const;
						void SetNaturalMode(bool x);
						void SetNatural_Enabled();
						void SetNatural_Disabled();
					//
					/////////////////////////////////////////////////////////////////////
				//
				/////////////////////////////////////////////////////////////////////////
		};

		extern TextFormat DefaultFormat;
	}

#endif//MCC_NOTE_FORMAT_CLASS_H
