#include <MCC.h>

using namespace MCC_MusicalNoteFlash;


void setup()
{
    Serial.begin(115200);

    MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::FormatClass myFormat; 
    
    const char* Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Sharp, 3, myFormat );
    Serial.println(Text);

    myFormat.Octave_Disabled();

    Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Sharp, 3, myFormat );
    Serial.println(Text);

    myFormat.Octave_Enabled();
    myFormat.Accidental_Symbol();
    myFormat.Spacing_Enabled();

    Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Sharp, 3, myFormat );
    Serial.println(Text);
    
    myFormat.Accidental_Text();
    myFormat.Octave_Enabled();
    myFormat.Spacing_Enabled();

    Text = GetName( MCC_MusicalNote::Pitch::Letter::C, MCC_MusicalNote::Pitch::Accidental::Sharp, 3, myFormat );
    Serial.println(Text);

}

void loop()
{
    
}