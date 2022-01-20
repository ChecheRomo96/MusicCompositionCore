#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNoteFlash;

int main()
{
	MCC::Start();
    
    // Default initializator, contents of TextFormat::DefaultFormat are copyied
    MCC_MusicalNote::TextFormat::FormatClass myFormat;
    myFormat.Accidental_Symbol();

    const char* Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Flat, myFormat);
    std::cout << "Accidental Symbol: " << Text << std::endl;

    myFormat.Accidental_Text();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Flat, myFormat);
    std::cout << "Accidental Text: " << Text << std::endl;

    myFormat.Accidental_Symbol();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Natural, myFormat);
    std::cout << "Accidental Symbol: " << Text << std::endl;

    myFormat.Accidental_Text();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Natural, myFormat);
    std::cout << "Accidental Text: " << Text << std::endl;

    myFormat.Accidental_Symbol();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Sharp, myFormat);
    std::cout << "Accidental Symbol: " << Text << std::endl;

    myFormat.Accidental_Text();

    Text = GetAccidentalText(MCC_MusicalNote::Pitch::Accidental::Sharp, myFormat);
    std::cout << "Accidental Text: " << Text << std::endl;
    
    return 0;
}