#include <MCC_Core.h>

#include "Shared.h"

void setup() {
    Serial.begin(115200);
    while(!Serial) {}

    MCCExamples::Core::Version::Run(
        [](const char* text) { Serial.print(text); });
}

void loop() {}
