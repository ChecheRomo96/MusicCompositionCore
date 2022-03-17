#include <MCC.h>

using namespace MCC_MusicalNoteFlash;


void setup()
{
	Serial.begin(115200);

	MCC::Start();
    
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalNote::Pitch::PitchClass( Letter::LetterClass, Accidental::AccidentalClass )

        PitchClass Pitch( Letter::C, Accidental::Natural);
        Serial.println(Pitch.Name());
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Pitch::PitchClass( Pitch::Letter::LetterClass, Pitch::Accidental::AccidentalClass )

        Pitch = PitchClass( Letter::C, Accidental::Sharp );
        Serial.println(Pitch.Name());
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Class Modifiers

        Pitch.SetLetter(Letter::B);
        Pitch.SetAccidental(Accidental::Flat); 
        Serial.println(Pitch.Name());
    //
    ///////////////////////////////////////////////////////////////////////////////////////////

}

void loop()
{
	
}