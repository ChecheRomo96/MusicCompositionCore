#include <MCC.h>

using namespace MCC_MusicalNoteFlash;


void setup()
{
    Serial.begin(115200);

    MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::FormatClass myFormat; 
    
    const char* Text = GetAccidentalText( MCC_MusicalNote::Pitch::Accidental::DoubleFlat , myFormat );
    Serial.print("Accidental Symbol: ");
    Serial.print(Text);

    myFormat.Accidental_Text();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::DoubleFlat, myFormat);
    Serial.print(", Accidental Text: ");
    Serial.println(Text);

    myFormat.Accidental_Symbol();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Flat, myFormat);
    Serial.print("Accidental Symbol: ");
    Serial.print(Text);

    myFormat.Accidental_Text();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Flat, myFormat);
    Serial.print(" , Accidental Text: ");
    Serial.println(Text);

    myFormat.Accidental_Symbol();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Natural, myFormat);
    Serial.print("Accidental Symbol: ");
    Serial.print(Text);

    myFormat.Accidental_Text();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Natural, myFormat);
    Serial.print("  , Accidental Text: ");
    Serial.println(Text);

    myFormat.Accidental_Symbol();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Sharp, myFormat);
    Serial.print("Accidental Symbol: ");
    Serial.print(Text);

    myFormat.Accidental_Text();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Sharp, myFormat);
    Serial.print(" , Accidental Text: ");
    Serial.println(Text);

    myFormat.Accidental_Symbol();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::DoubleSharp, myFormat);
    Serial.print("Accidental Symbol: ");
    Serial.print(Text);

    myFormat.Accidental_Text();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::DoubleSharp, myFormat);
    Serial.print(", Accidental Text: ");
    Serial.println(Text);

}

void loop()
{
    
}