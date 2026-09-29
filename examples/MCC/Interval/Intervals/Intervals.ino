#include "Shared.h"

void setup() {
    Serial.begin(115200);
    while(!Serial) {}

    MCCExamples::Interval::Intervals::Run(
        [](const char* text) { Serial.print(text); });
}

void loop() {}
