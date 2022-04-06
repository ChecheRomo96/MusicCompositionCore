#include <MCC.h>

using namespace MCC_MusicalNote;

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

        TextFormat::FormatClass myFormat;

        myFormat.Accidental_Symbol();
        myFormat.Octave_Disabled();
        myFormat.Spacing_Disabled();
        myFormat.Natural_Enabled();

        Serial.print("Note A: "); Serial.print(Flash::GetName(NoteA, myFormat)); Serial.println();
        Serial.print("Note B: "); Serial.print(Flash::GetName(NoteB, myFormat)); Serial.println();
        Serial.print("Note C: "); Serial.print(Flash::GetName(NoteC, myFormat)); Serial.println();
        Serial.println();
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print as Note Symbol

        myFormat.Accidental_Symbol();
        myFormat.Octave_Enabled();
        myFormat.Spacing_Enabled();
        myFormat.Natural_Enabled();

        Serial.print("Note A: "); Serial.print(Flash::GetName(NoteA, myFormat)); Serial.println();
        Serial.print("Note B: "); Serial.print(Flash::GetName(NoteB, myFormat)); Serial.println();
        Serial.print("Note C: "); Serial.print(Flash::GetName(NoteC, myFormat)); Serial.println();
        Serial.println();
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print as Text

        myFormat.Accidental_Text();
        myFormat.Octave_Enabled();
        myFormat.Spacing_Enabled();
        myFormat.Natural_Enabled();

        Serial.print("Note A: "); Serial.print(Flash::GetName(NoteA, myFormat)); Serial.println();
        Serial.print("Note B: "); Serial.print(Flash::GetName(NoteB, myFormat)); Serial.println();
        Serial.print("Note C: "); Serial.print(Flash::GetName(NoteC, myFormat)); Serial.println();
        Serial.println();
        
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print Symbols Justified

        myFormat.Accidental_Symbol();
        myFormat.Octave_Enabled();
        myFormat.Spacing_Justified();
        myFormat.Natural_Enabled();

        Serial.print("Note A: "); Serial.print(Flash::GetName(NoteA, myFormat)); Serial.println();
        Serial.print("Note B: "); Serial.print(Flash::GetName(NoteB, myFormat)); Serial.println();
        Serial.print("Note C: "); Serial.print(Flash::GetName(NoteC, myFormat)); Serial.println();
        Serial.println();

    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
	return 0;
}

void loop()
{

}