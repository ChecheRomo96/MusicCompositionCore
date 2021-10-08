#include <MCC.h>

using namespace MCC_MusicalNoteFlash;


void setup()
{
    Serial.begin(115200);

    MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::FormatClass myFormat; 
    
    const char* Text = GetLetterText( MCC_MusicalNote::Pitch::Letter::C );
    Serial.println(Text);

}

void loop()
{
    
}