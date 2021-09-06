#include <MCC.h>

using namespace MCC_MusicalNoteFlash;


void setup()
{
	Serial.begin(115200);

	MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::Format myFormat; 
    
    const char* Text = GetAccidentalName( MCC_MusicalNote::Pitch::Accidental::Sharp , myFormat );
    Serial.println(Text);

}

void loop()
{
	
}