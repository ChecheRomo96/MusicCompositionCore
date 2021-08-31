#include <iostream>
#include <MCC.h>

using namespace MCC_UtilityCore;

int main()
{
	MCC::Start();

	CPVector::vector<uint8_t> Vect;

	Vect.resize(5000);

	for(unsigned int i = 0; i < Vect.size(); i++)
	{
		Vect[i] = rand()%16;

		if(i < Vect.size() - 1)
		{
			std::cout<<(unsigned int)Vect[i]<<", ";
		}
		else	
		{
			std::cout<<(unsigned int)Vect[i]<<".\n\n";
		}
	}

	Accumulator<uint8_t, uint16_t> Acc(Vect);

	for(unsigned int i = 0; i < Acc.ElementCount(); ++i)
	{
		std::cout<<(unsigned int)Acc[i].Data()<<" -> "<<(unsigned int)Acc[i].Counter()<<".\n";
	}

	return 0;
}