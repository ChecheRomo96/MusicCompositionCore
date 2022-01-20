#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNote::Pitch;

int main()
{
	MCC::Start();
    
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalNote::Pitch::PitchClass( Letter::LetterClass, Accidental::AccidentalClass )

        PitchClass Pitch( Letter::C, Accidental::Natural);
        std::cout<< Pitch.Name()<<std::endl;
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Pitch::PitchClass( Pitch::Letter::LetterClass, Pitch::Accidental::AccidentalClass )

        Pitch = PitchClass( Letter::C, Accidental::Sharp );
        std::cout<< Pitch.Name()<<std::endl;
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Pitch::LetterType
    // Pitch::AccidentalType
    // Pitch::PitchClass( LetterType, AccidentalType )
    // MusicalNote::Note( PitchClass, Octave )
    
        auto letter = Letter::B;
        auto accidental = Accidental::Flat;
        Pitch = PitchClass( letter, accidental );
        std::cout<< Pitch.Name()<<std::endl;
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    
	return 0;
}
