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

        TextFormat::FormatClass myFormat;

        myFormat.Accidental_Symbol();
        myFormat.Octave_Disabled();
        myFormat.Spacing_Disabled();
        myFormat.Natural_Enabled();

        std::cout << "Note A: " << Flash::GetName(NoteA, myFormat) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB, myFormat) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC, myFormat) << std::endl;
        std::cout << std::endl;
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print as Note Symbol

        myFormat.Accidental_Symbol();
        myFormat.Octave_Enabled();
        myFormat.Spacing_Enabled();
        myFormat.Natural_Enabled();

        std::cout << "Note A: " << Flash::GetName(NoteA, myFormat) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB, myFormat) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC, myFormat) << std::endl;
        std::cout << std::endl;
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print as Text

        myFormat.Accidental_Text();
        myFormat.Octave_Enabled();
        myFormat.Spacing_Enabled();
        myFormat.Natural_Enabled();

        std::cout << "Note A: " << Flash::GetName(NoteA, myFormat) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB, myFormat) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC, myFormat) << std::endl;
        std::cout << std::endl;
        
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print Symbols Justified

        myFormat.Accidental_Symbol();
        myFormat.Octave_Enabled();
        myFormat.Spacing_Justified();
        myFormat.Natural_Enabled();

        std::cout << "Note A: " << Flash::GetName(NoteA, myFormat) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB, myFormat) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC, myFormat) << std::endl;
        std::cout << std::endl;

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	return 0;
}