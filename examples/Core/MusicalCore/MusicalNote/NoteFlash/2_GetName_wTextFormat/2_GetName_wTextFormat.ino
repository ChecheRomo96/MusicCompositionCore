#include <MCC.h>

using namespace MCC_MusicalNoteFlash;


void setup()
{
	Serial.begin(115200);

	MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::Format myFormat; 
    
    const char* Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Natural, 3, myFormat );
    Serial.println(Text);

    myFormat.Set_OctaveDisabled();

    Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Natural, 3, myFormat );
    Serial.println(Text);
    
    myFormat.Set_AccidentalLong();
    myFormat.Set_SpaceEnabled();

    Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Natural, 3, myFormat );
    Serial.println(Text);

}

void loop()
{
	
}