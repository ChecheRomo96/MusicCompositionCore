#ifndef MCC_MUSICAL_NOTE_TEXT_FORMAT_DEFINITIONS_H
#define MCC_MUSICAL_NOTE_TEXT_FORMAT_DEFINITIONS_H

	#include <MCC_BuildSettings.h>

	namespace MusicCompositionCore::Core::MusicalCore::MusicalNote::TextFormat
	{
		namespace BitNumbering
		{
			static constexpr uint8_t AccidentalMode = 0;
			static constexpr uint8_t OctaveMode = 1;
			static constexpr uint8_t SpacingMode = 2;
			static constexpr uint8_t NaturalMode = 4;
		}

		namespace AccidentalMode
		{
			static constexpr bool Symbol = 1;
			static constexpr bool Text = 0;

			static constexpr uint8_t Symbol_Mask = 0b00000001;
			static constexpr uint8_t Text_Mask = 0;
		}

		namespace OctaveMode
		{
			static constexpr bool Enabled = 1;
			static constexpr bool Disabled = 0;

			static constexpr uint8_t Enabled_Mask = 0b000010;
			static constexpr uint8_t Disabled_Mask = 0;
		}

		namespace SpacingMode
		{
			static constexpr uint8_t Enabled = 0b10;
			static constexpr uint8_t Justified = 0b01;
			static constexpr uint8_t Disabled = 0;

			static constexpr uint8_t Enabled_Mask = 0b000001000;
			static constexpr uint8_t Justified_Mask = 0b000000100;
			static constexpr uint8_t Disabled_Mask = 0;
		}

		namespace NaturalMode
		{
			static constexpr bool Disabled = 1;
			static constexpr bool Enabled = 0;

			static constexpr uint8_t Disabled_Mask = 0b00010000;
			static constexpr uint8_t Enabled_Mask = 0;
		}
	}

#endif//MCC_MUSICAL_NOTE_TEXT_FORMAT_DEFINITIONS_H