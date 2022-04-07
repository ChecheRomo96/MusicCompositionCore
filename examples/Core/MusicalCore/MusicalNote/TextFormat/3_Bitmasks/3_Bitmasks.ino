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

        uint8_t FormatData = 0; 

        FormatData |= AccidentalMode::Symbol_Mask;
        FormatData |= OctaveMode::Disabled_Mask;
        FormatData |= SpacingMode::Disabled_Mask;
        FormatData |= NaturalMode::Enabled_Mask;

        TextFormat::FormatClass myFormat(FormatData);

        Serial.print("Note A: "); Serial.print(Flash::GetName(NoteA, myFormat)); Serial.println();
        Serial.print("Note B: "); Serial.print(Flash::GetName(NoteB, myFormat)); Serial.println();
        Serial.print("Note C: "); Serial.print(Flash::GetName(NoteC, myFormat)); Serial.println();
        Serial.println();
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print as Note Symbol

        FormatData = 0; 

        FormatData |= AccidentalMode::Symbol_Mask;
        FormatData |= OctaveMode::Enabled_Mask;
        FormatData |= SpacingMode::Enabled_Mask;
        FormatData |= NaturalMode::Enabled_Mask;

        myFormat = TextFormat::FormatClass(FormatData);

        Serial.print("Note A: "); Serial.print(Flash::GetName(NoteA, myFormat)); Serial.println();
        Serial.print("Note B: "); Serial.print(Flash::GetName(NoteB, myFormat)); Serial.println();
        Serial.print("Note C: "); Serial.print(Flash::GetName(NoteC, myFormat)); Serial.println();
        Serial.println();
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print as Text

        FormatData = 0; 

        FormatData |= AccidentalMode::Text_Mask;
        FormatData |= OctaveMode::Enabled_Mask;
        FormatData |= SpacingMode::Enabled_Mask;
        FormatData |= NaturalMode::Enabled_Mask;

        myFormat = TextFormat::FormatClass(FormatData);

        Serial.print("Note A: "); Serial.print(Flash::GetName(NoteA, myFormat)); Serial.println();
        Serial.print("Note B: "); Serial.print(Flash::GetName(NoteB, myFormat)); Serial.println();
        Serial.print("Note C: "); Serial.print(Flash::GetName(NoteC, myFormat)); Serial.println();
        Serial.println();
        
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modify TextFormat::FormatClass Object and set it to print Symbols Justified

        FormatData = 0; 

        FormatData |= AccidentalMode::Symbol_Mask;
        FormatData |= OctaveMode::Enabled_Mask;
        FormatData |= SpacingMode::Justified_Mask;
        FormatData |= NaturalMode::Enabled_Mask;

        myFormat = TextFormat::FormatClass(FormatData);

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