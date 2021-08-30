#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNoteFlash;

int main()
{
	MCC::Start();
    
    char* Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Natural );
    
    std::cout<<Text<<std::endl;

	return 0;
}
