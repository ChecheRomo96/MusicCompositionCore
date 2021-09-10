#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNote;

int main()
{
	MCC::Start();
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create Note Objects

        MCC_MusicalNote::Note NoteA(Pitch::C_Natural, 3);
        MCC_MusicalNote::Note NoteB(Pitch::C_Flat, 3);
        MCC_MusicalNote::Note NoteC(Pitch::C_Sharp, 3);
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create TextFormat::FormatClass Object and set it to print as Note Symbol

        auto AccidentalMode = TextFormat::AccidentalMode::Symbol;
        auto OctaveMode     = TextFormat::OctaveMode::Enabled;
        auto SpacingMode    = TextFormat::SpacingMode::Enabled;
        auto NaturalMode    = TextFormat::NaturalMode::Disabled;

        TextFormat::FormatClass myFormat(AccidentalMode, OctaveMode, SpacingMode, NaturalMode);

        std::cout << "Note A: " << Flash::GetName(NoteA, myFormat) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB, myFormat) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC, myFormat) << std::endl;
        std::cout << std::endl;
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	return 0;
}
