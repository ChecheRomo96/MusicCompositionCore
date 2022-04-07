#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNote;
using namespace MCC_MusicalNote::TextFormat;

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

        DefaultFormat.Accidental_Symbol();
        DefaultFormat.Octave_Disabled();
        DefaultFormat.Spacing_Disabled();
        DefaultFormat.Natural_Enabled();

        std::cout << "Note A: " << Flash::GetName(NoteA) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC) << std::endl;
        std::cout << std::endl;
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print as Note Symbol

        DefaultFormat.Accidental_Symbol();
        DefaultFormat.Octave_Enabled();
        DefaultFormat.Spacing_Enabled();
        DefaultFormat.Natural_Enabled();

        std::cout << "Note A: " << Flash::GetName(NoteA) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC) << std::endl;
        std::cout << std::endl;
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print as Text

        DefaultFormat.Accidental_Text();
        DefaultFormat.Octave_Enabled();
        DefaultFormat.Spacing_Enabled();
        DefaultFormat.Natural_Enabled();

        std::cout << "Note A: " << Flash::GetName(NoteA) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC) << std::endl;
        std::cout << std::endl;
        
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print Symbols Justified

        DefaultFormat.Accidental_Symbol();
        DefaultFormat.Octave_Enabled();
        DefaultFormat.Spacing_Justified();
        DefaultFormat.Natural_Enabled();

        std::cout << "Note A: " << Flash::GetName(NoteA) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC) << std::endl;
        std::cout << std::endl;

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	return 0;
}