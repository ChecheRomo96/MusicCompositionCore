#include "Shared.h"

void setup() {
    Serial.begin(115200);
    while(!Serial) {}

    Serial.println("MCC :: Core / Version");
    Serial.print("MCC ........... ");
    Serial.println(MCCExamples::Core::Version::MCCVersion());
    Serial.print("Foundation .... ");
    Serial.println(MCCExamples::Core::Version::FoundationVersion());
}

void loop() {}
