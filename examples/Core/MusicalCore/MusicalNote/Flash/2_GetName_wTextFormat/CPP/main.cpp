#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNoteFlash;

int main()
{
	MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::Format myFormat; 
    
    const char* Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Natural, 3, myFormat );
    std::cout<<Text<<std::endl;

    myFormat.Set_OctaveDisabled();

    Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Natural, 3, myFormat );
    std::cout<<Text<<std::endl;

    myFormat.Set_AccidentalLong();
    myFormat.Set_SpaceEnabled();

    Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Natural, 3, myFormat );
    std::cout<<Text<<std::endl;

	return 0;
}
