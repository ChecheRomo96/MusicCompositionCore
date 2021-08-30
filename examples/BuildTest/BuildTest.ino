#include <MCC.h>

void setup()
{

    Serial.begin(115200);

    Serial.print(F("This project uses CPString version:"));
    Serial.println(CPSTRING_VERSION);

    Serial.print(F("This project uses CPVector version:"));
    Serial.println(CPVECTOR_VERSION);

    Serial.print(F("This project uses MCC version:"));
    Serial.println(MCC_VERSION);

}

void loop()
{

}