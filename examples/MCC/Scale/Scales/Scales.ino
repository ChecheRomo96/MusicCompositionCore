#include <MCC_Scale.h>

#include "Shared.h"

void setup() {
    Serial.begin(115200);
    while(!Serial) {}

    MCCExamples::Scale::Scales::Run(
        [](const char* text) { Serial.print(text); });
}

void loop() {}
