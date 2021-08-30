#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNote;

int main()
{
	MCC::Start();
    
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalNote::Note( PitchClass, Octave )

        Note myNote( Pitch::C_Natural, -2 );
        std::cout<<myNote.Name()<<std::endl;
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Pitch::PitchClass( Pitch::Letter::LetterClass, Pitch::Accidental::AccidentalClass )
    // MusicalNote::Note( PitchClass, Octave )

        auto Pitch = Pitch::PitchClass( Pitch::Letter::C, Pitch::Accidental::Sharp );
        myNote = Note( Pitch ); 
        std::cout<<myNote.Name()<<std::endl;
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Pitch::LetterType
    // Pitch::AccidentalType
    // Pitch::PitchClass( LetterType, AccidentalType )
    // MusicalNote::Note( PitchClass, Octave )
    
        Pitch::LetterType letter = Pitch::Letter::B;
        Pitch::AccidentalType accidental = Pitch::Accidental::Flat;
        Pitch = Pitch::PitchClass( letter, accidental );
        myNote = Note( Pitch, 1 );
        std::cout<<myNote.Name()<<std::endl;
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    
	return 0;
}
