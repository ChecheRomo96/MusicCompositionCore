#include <MCC.h>

using namespace MCC_MusicalNoteFlash;


void setup()
{
    Serial.begin(115200);

    MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::FormatClass myFormat; 
    
    const char* Text = GetAccidentalText( MCC_MusicalNote::Pitch::Accidental::Flat , myFormat );
    Serial.println(Text);

    myFormat.Accidental_Text();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Flat, myFormat);
    Serial.println(Text);

    myFormat.Accidental_Symbol();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Natural, myFormat);
    
    Serial.println(Text);

    myFormat.Accidental_Text();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Natural, myFormat);
    Serial.println(Text);

    myFormat.Accidental_Symbol();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Sharp, myFormat);
    Serial.println(Text);

    myFormat.Accidental_Text();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Sharp, myFormat);
    Serial.println(Text);

}

void loop()
{
    
}