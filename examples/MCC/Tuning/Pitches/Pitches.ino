#include <MCC_Tuning.h>

#include "Shared.h"

void setup() {
    Serial.begin(115200);
    while(!Serial) {}

    MCCExamples::Tuning::Pitches::Run(
        [](const char* text) { Serial.print(text); });
}

void loop() {}
