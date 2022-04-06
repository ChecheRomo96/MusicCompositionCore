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

        auto myPitch = Pitch( Pitch::Letter::C, Pitch::Accidental::Natural );
        myNote = Note( myPitch ); 
        Serial.println( myNote.Name() );
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Pitch::Accidental::AccidentalClass( ID )
    // Pitch::Letter::LetterClass( ID )
    // Pitch::PitchClass( Pitch::Letter::LetterClass, Pitch::Accidental::AccidentalClass )
    // MusicalNote::Note( PitchClass, Octave )

        auto accidental = Pitch::Accidental::Flat;
        auto letter = Pitch::Letter::B;
        myPitch = Pitch( letter, accidental );
        myNote = Note( myPitch, 1 );
        Serial.println( myNote.Name() );
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
}

void loop()
{

}