#include <MCC.h>
#include <math.h>

int main()
{
	MCC::Start();

    MCC_MusicalScale::Scale myScale(MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::C_Natural, 3), MCC_MusicalScaleFlash::Scales::Lydian);
    std::cout << myScale.Name() << std::endl;

	MCC_MusicalNote::Note targetNote;
    
    MCC_MusicalNote::TextFormat::DefaultFormat.Set_SpaceJustified();

	for (uint8_t i = 0; myScale.Note(i).NotePitch() < 128; i++)
	{
		targetNote = myScale.Note(i);
		std::cout << targetNote.Name() << " Frequency = " << targetNote.Frequency() << std::endl;
	}
}
