#include <MCC.h>

int main()
{
	MCC::Start();
	/*
	MCC_MusicalInterval::Interval myInterval(MCC_MusicalInterval::Qualities::Perfect, MCC_MusicalInterval::Numbers::Fourth);

	std::cout << myInterval.Name() << std::endl;

	auto a = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::C_Natural, 3);
	auto b = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::G_Natural, 3);

	myInterval = MCC_MusicalInterval::Interval(a, b);
	std::cout << myInterval.Name() << std::endl;

	myInterval = MCC_MusicalInterval::Interval(b, a);
	std::cout << myInterval.Name() << std::endl;

	b = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::G_Natural, 4);

	myInterval = MCC_MusicalInterval::Interval(a, b);
	std::cout << myInterval.Name() << std::endl;
	*/


    MCC_MusicalScale::Scale myScale;
    std::cout << myScale.Name() << std::endl;
}
