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

        uint8_t FormatData = 0; 

        FormatData |= AccidentalMode::Symbol_Mask;
        FormatData |= OctaveMode::Disabled_Mask;
        FormatData |= SpacingMode::Disabled_Mask;
        FormatData |= NaturalMode::Enabled_Mask;
        std::cout<<"FormatData: "<<FormatData<<std:endl;
        
        TextFormat::FormatClass myFormat(FormatData);

        std::cout << "Note A: " << Flash::GetName(NoteA, myFormat) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB, myFormat) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC, myFormat) << std::endl;
        std::cout << std::endl;
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print as Note Symbol

        FormatData = 0; 

        FormatData |= AccidentalMode::Symbol_Mask;
        FormatData |= OctaveMode::Enabled_Mask;
        FormatData |= SpacingMode::Enabled_Mask;
        FormatData |= NaturalMode::Enabled_Mask;
        std::cout<<"FormatData: "<<FormatData<<std:endl;

        myFormat = TextFormat::FormatClass(FormatData);

        std::cout << "Note A: " << Flash::GetName(NoteA, myFormat) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB, myFormat) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC, myFormat) << std::endl;
        std::cout << std::endl;
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print as Text

        FormatData = 0; 

        FormatData |= AccidentalMode::Text_Mask;
        FormatData |= OctaveMode::Enabled_Mask;
        FormatData |= SpacingMode::Enabled_Mask;
        FormatData |= NaturalMode::Enabled_Mask;
        std::cout<<"FormatData: "<<FormatData<<std:endl;

        myFormat = TextFormat::FormatClass(FormatData);

        std::cout << "Note A: " << Flash::GetName(NoteA, myFormat) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB, myFormat) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC, myFormat) << std::endl;
        std::cout << std::endl;
        
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print Symbols Justified

        FormatData = 0; 

        FormatData |= AccidentalMode::Symbol_Mask;
        FormatData |= OctaveMode::Enabled_Mask;
        FormatData |= SpacingMode::Justified_Mask;
        FormatData |= NaturalMode::Enabled_Mask;
        std::cout<<"FormatData: "<<FormatData<<std:endl;

        myFormat = TextFormat::FormatClass(FormatData);

        std::cout << "Note A: " << Flash::GetName(NoteA, myFormat) << std::endl;
        std::cout << "Note B: " << Flash::GetName(NoteB, myFormat) << std::endl;
        std::cout << "Note C: " << Flash::GetName(NoteC, myFormat) << std::endl;
        std::cout << std::endl;

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	return 0;
}