#include <MCC.h>

using namespace MCC_MusicalNoteFlash;


void setup()
{
	Serial.begin(115200);

	MCC::Start();
    
    const char* Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Natural );
    
    Serial.println(Text);
}

void loop()
{
	
}