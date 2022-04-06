#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNoteFlash;

int main()
{
	MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::FormatClass myFormat;
    
    const char* Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Sharp, 3, myFormat );
    std::cout<<Text<<std::endl;

    myFormat.Octave_Disabled();

    Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Sharp, 3, myFormat );
    std::cout<<Text<<std::endl;

    myFormat.Octave_Enabled();
    myFormat.Accidental_Symbol();
    myFormat.Spacing_Enabled();

    Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Sharp, 3, myFormat );
    std::cout<<Text<<std::endl;

    myFormat.Accidental_Text();
    myFormat.Octave_Enabled();
    myFormat.Spacing_Enabled();

    Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Sharp, 3, myFormat );
    std::cout<<Text<<std::endl;

	return 0;
}
