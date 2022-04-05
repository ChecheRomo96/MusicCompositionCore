#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNote;

int main()
{
	MCC::Start();
    
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalNote::Pitch::PitchClass( Letter::LetterClass, Accidental::AccidentalClass )

        Pitch myPitch(Pitch::Letter::C, Pitch::Accidental::Natural);
        std::cout<< myPitch.Name()<<std::endl;
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Pitch::PitchClass( Pitch::Letter::LetterClass, Pitch::Accidental::AccidentalClass )

        myPitch = Pitch(Pitch::Letter::C, Pitch::Accidental::Sharp );
        std::cout<< myPitch.Name()<<std::endl;
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Class Modifiers

        myPitch.SetLetter(Pitch::Letter::B);
        myPitch.SetAccidental(Pitch::Accidental::Flat);
        std::cout<< myPitch.Name()<<std::endl;
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    
	return 0;
}
