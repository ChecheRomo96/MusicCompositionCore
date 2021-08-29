#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNoteFlash;

int main()
{
	MCC::Start();
    
    std::cout << GetName(MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Natural) << std::endl;
    std::cout << GetName(MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Sharp) << std::endl;
    std::cout << GetName(MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Flat, 3) << std::endl;
    

	return 0;
}
