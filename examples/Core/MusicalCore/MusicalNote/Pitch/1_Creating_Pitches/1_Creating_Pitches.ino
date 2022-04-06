#include <MCC.h>

using namespace MCC_MusicalNote;


void setup()
{
    Serial.begin(115200);

    MCC::Start();
    
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalNote::Pitch::PitchClass( Letter::LetterClass, Accidental::AccidentalClass )

        Pitch myPitch( Pitch::Letter::C, Pitch::Accidental::Natural);
        Serial.println(myPitch.Name());
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Pitch::PitchClass( Pitch::Letter::LetterClass, Pitch::Accidental::AccidentalClass )

        myPitch = Pitch( Pitch::Letter::C, Pitch::Accidental::Sharp );
        Serial.println(myPitch.Name());
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Class Modifiers

        myPitch.SetLetter(Pitch::Letter::B);
        myPitch.SetAccidental(Pitch::Accidental::Flat); 
        Serial.println(myPitch.Name());
    //
    ///////////////////////////////////////////////////////////////////////////////////////////

}

void loop()
{
    
}