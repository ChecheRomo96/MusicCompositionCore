#include "../Shared.h"

#include <iostream>

int main() {
    MCCExamples::Pitch::PitchClasses::Run(
        [](const char* text) { std::cout << text; });
    return 0;
}
