#ifndef MCC_NOTE_FORMAT_CLASS_H
#define MCC_NOTE_FORMAT_CLASS_H

	#include <MCC_BuildSettings.h>

	#include "TextFormat.h"

	namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::TextFormat
	{
		class FormatClass
		{
			private:
				uint8_t data;

			public:
				/////////////////////////////////////////////////////////////////////////
				// Constructors, Destructors and Clear Function

					FormatClass();
				//
				/////////////////////////////////////////////////////////////////////////
				// Copy Constructor and assignment operator

					FormatClass(const FormatClass& source);
					FormatClass(uint8_t data);
					FormatClass(bool AccidentalMode, bool OctaveEnabled, uint8_t Spacing, bool NaturalMode = TextFormat::NaturalMode::Disabled);
					FormatClass& operator=(const FormatClass& src);
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
						void Accidental_Symbol();
						void Accidental_Text();
					//
					/////////////////////////////////////////////////////////////////////
					// Octave Mode

						const bool OctaveMode() const;
						void SetOctaveMode(bool x);
						void Octave_Enabled();
						void Octave_Disabled();
					//
					/////////////////////////////////////////////////////////////////////
					// Spacing Mode

						const uint8_t SpacingMode() const;
						void SetSpacingMode(uint8_t x);
						void Spacing_Enabled();
						void Spacing_Disabled();
						void Spacing_Justified();
					//
					/////////////////////////////////////////////////////////////////////
					// Natural Mode

						const bool NaturalMode() const;
						void SetNaturalMode(bool x);
						void Natural_Enabled();
						void Natural_Disabled();
					//
					/////////////////////////////////////////////////////////////////////
				//
				/////////////////////////////////////////////////////////////////////////
		};

		extern FormatClass DefaultFormat;
	}

#endif//MCC_NOTE_FORMAT_CLASS_H
