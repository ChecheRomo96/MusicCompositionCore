#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNoteFlash;

int main()
{
	MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::Format myFormat;
    myFormat.Set_AccidentalShort();
    
    const char* Text = GetAccidentalName( MCC_MusicalNote::Pitch::Accidental::Sharp , myFormat );
    std::cout << "Accidental Short: " << Text << std::endl;

    myFormat.Set_AccidentalLong();

    Text = GetAccidentalName(MCC_MusicalNote::Pitch::Accidental::Sharp, myFormat);
    std::cout << "Accidental Long: " << Text << std::endl;
    
    return 0;
}