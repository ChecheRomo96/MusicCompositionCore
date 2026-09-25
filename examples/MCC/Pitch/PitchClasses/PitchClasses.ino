#include "Shared.h"

void setup() {
    Serial.begin(115200);
    while(!Serial) {}

    MCCExamples::Pitch::PitchClasses::Run(
        [](const char* text) { Serial.print(text); });
}

void loop() {}
