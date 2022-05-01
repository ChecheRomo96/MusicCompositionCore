#include <MCC.h>

using namespace MCC_UtilityCore;

void setup()
{
	MCC::Start();
	Serial.begin(115200);

	CPVector::vector<uint8_t> Vect;

	Vect.resize(5000);

	for(unsigned int i = 0; i < Vect.size(); i++)
	{
		Vect[i] = rand()%16;

		if(i < Vect.size() - 1)
		{
			Serial.print( (unsigned int)Vect[i] );
			Serial.print( F(", ") );
		}
		else	
		{
			Serial.print( (unsigned int)Vect[i] );
			Serial.print( F(".\n\n") );
		}
	}

	Accumulator<uint8_t, uint16_t> Acc(Vect);

	for(unsigned int i = 0; i < Acc.ElementCount(); ++i)
	{
		Serial.print( (unsigned int)Acc[i].Data() );
		Serial.print( F(" -> ") );
		Serial.print( (unsigned int)Acc[i].Counter() );
		Serial.print( F(".\n") );
	}
}

void loop()
{

}