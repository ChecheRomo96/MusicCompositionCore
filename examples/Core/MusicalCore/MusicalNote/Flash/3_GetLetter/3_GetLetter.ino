#include <MCC.h>

using namespace MCC_MusicalNoteFlash;


void setup()
{
	Serial.begin(115200);

	MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::Format myFormat; 
    
    const char* Text = GetLetterName( MCC_MusicalNote::Pitch::Letter::C , myFormat );
    Serial.println(Text);

}

void loop()
{
	
}