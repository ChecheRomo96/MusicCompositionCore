#include <MCC.h>

using namespace MCC_MusicalNote;

void setup()
{
	MCC::Start();
    Serial.begin(115200);

    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalNote::Note( PitchClass, Octave )

        Note myNote( Pitch::C_Natural, 0 );
        Serial.println( myNote.Name() );
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Pitch::PitchClass( Pitch::Letter::LetterClass, Pitch::Accidental::AccidentalClass )
    // MusicalNote::Note( PitchClass, Octave )

        auto Pitch = Pitch::PitchClass( Pitch::Letter::C, Pitch::Accidental::Natural );
        myNote = Note( Pitch ); 
        Serial.println( myNote.Name() );
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Pitch::Accidental::AccidentalClass( ID )
    // Pitch::Letter::LetterClass( ID )
    // Pitch::PitchClass( Pitch::Letter::LetterClass, Pitch::Accidental::AccidentalClass )
    // MusicalNote::Note( PitchClass, Octave )

        auto accidental = Pitch::Accidental::Flat;
        letter = Pitch::Letter::B;
        Pitch = Pitch::PitchClass( letter, accidental );
        myNote = Note( Pitch, 1 );
        Serial.println( myNote.Name() );
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
}

void loop()
{

}