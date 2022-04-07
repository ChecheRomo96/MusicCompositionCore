#include <MCC.h>

using namespace MCC_MusicalNote;
using namespace MCC_MusicalNote::TextFormat;

void setup()
{
    Serial.begin(115200);
    MCC::Start();
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create Note Objects

        MCC_MusicalNote::Note NoteA(Pitch::C_Natural, 3);
        MCC_MusicalNote::Note NoteB(Pitch::C_Flat, 3);
        MCC_MusicalNote::Note NoteC(Pitch::C_Sharp, 3);
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create TextFormat::FormatClass Object and set it to print as Note Symbol

        DefaultFormat.Accidental_Symbol();
        DefaultFormat.Octave_Disabled();
        DefaultFormat.Spacing_Disabled();
        DefaultFormat.Natural_Enabled();

        Serial.print("Note A: "); Serial.print(Flash::GetName(NoteA)); Serial.println();
        Serial.print("Note B: "); Serial.print(Flash::GetName(NoteB)); Serial.println();
        Serial.print("Note C: "); Serial.print(Flash::GetName(NoteC)); Serial.println();
        Serial.println();
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print as Note Symbol

        DefaultFormat.Accidental_Symbol();
        DefaultFormat.Octave_Enabled();
        DefaultFormat.Spacing_Enabled();
        DefaultFormat.Natural_Enabled();

        Serial.print("Note A: "); Serial.print(Flash::GetName(NoteA)); Serial.println();
        Serial.print("Note B: "); Serial.print(Flash::GetName(NoteB)); Serial.println();
        Serial.print("Note C: "); Serial.print(Flash::GetName(NoteC)); Serial.println();
        Serial.println();
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print as Text

        DefaultFormat.Accidental_Text();
        DefaultFormat.Octave_Enabled();
        DefaultFormat.Spacing_Enabled();
        DefaultFormat.Natural_Enabled();

        Serial.print("Note A: "); Serial.print(Flash::GetName(NoteA)); Serial.println();
        Serial.print("Note B: "); Serial.print(Flash::GetName(NoteB)); Serial.println();
        Serial.print("Note C: "); Serial.print(Flash::GetName(NoteC)); Serial.println();
        Serial.println();
        
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print Symbols Justified

        DefaultFormat.Accidental_Symbol();
        DefaultFormat.Octave_Enabled();
        DefaultFormat.Spacing_Justified();
        DefaultFormat.Natural_Enabled();

        Serial.print("Note A: "); Serial.print(Flash::GetName(NoteA)); Serial.println();
        Serial.print("Note B: "); Serial.print(Flash::GetName(NoteB)); Serial.println();
        Serial.print("Note C: "); Serial.print(Flash::GetName(NoteC)); Serial.println();
        Serial.println();

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    return 0;
}

void loop()
{

}