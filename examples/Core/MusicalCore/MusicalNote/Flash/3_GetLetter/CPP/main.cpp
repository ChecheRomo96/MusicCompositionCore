#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNoteFlash;

int main()
{
	MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::Format myFormat; 
    
    const char* Text = GetLetterName( MCC_MusicalNote::Pitch::Letter::C , myFormat );
    std::cout<<Text<<std::endl;

	return 0;
}
