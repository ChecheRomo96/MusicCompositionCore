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

        auto myPitch = Pitch( Pitch::Letter::C, Pitch::Accidental::Sharp );
        myNote = Note(myPitch);
        std::cout<<myNote.Name()<<std::endl;
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Pitch::LetterType
    // Pitch::AccidentalType
    // Pitch::PitchClass( LetterType, AccidentalType )
    // MusicalNote::Note( PitchClass, Octave )
    
        auto letter = Pitch::Letter::B;
        auto accidental = Pitch::Accidental::Flat;
        myPitch = Pitch( letter, accidental );
        myNote = Note(myPitch, 1 );
        std::cout<<myNote.Name()<<std::endl;
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    
	return 0;
}
