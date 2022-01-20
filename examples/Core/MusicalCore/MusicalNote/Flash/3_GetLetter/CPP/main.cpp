#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNoteFlash;

int main()
{
	MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::FormatClass myFormat; 
    
    const char* Text = GetLetterText( MCC_MusicalNote::Pitch::Letter::C );
    std::cout<<Text<<std::endl;

	return 0;
}
