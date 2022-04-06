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

        auto AccidentalMode = TextFormat::AccidentalMode::Symbol;
        auto OctaveMode = TextFormat::OctaveMode::Enabled;
        auto SpacingMode = TextFormat::SpacingMode::Enabled;
        auto NaturalMode = TextFormat::NaturalMode::Enabled;

        TextFormat::FormatClass myFormat(AccidentalMode, OctaveMode, SpacingMode, NaturalMode);

        Serial.print("Note A: "); Serial.print(Flash::GetName(NoteA, myFormat)); Serial.println();
        Serial.print("Note B: "); Serial.print(Flash::GetName(NoteB, myFormat)); Serial.println();
        Serial.print("Note C: "); Serial.print(Flash::GetName(NoteC, myFormat)); Serial.println();
        Serial.println();
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Create TextFormat::FormatClass Object and set it to print as Note Symbol

        AccidentalMode = TextFormat::AccidentalMode::Text;
        OctaveMode = TextFormat::OctaveMode::Disabled;
        SpacingMode = TextFormat::SpacingMode::Enabled;
        NaturalMode = TextFormat::NaturalMode::Enabled;

        myFormat = TextFormat::FormatClass(AccidentalMode, OctaveMode, SpacingMode, NaturalMode);

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