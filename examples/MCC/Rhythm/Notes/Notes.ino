#include <MCC_Rhythm.h>

#include "Shared.h"

void setup() {
    Serial.begin(115200);
    while(!Serial) {}

    MCCExamples::Rhythm::Notes::Run(
        [](const char* text) { Serial.print(text); });
}

void loop() {}
