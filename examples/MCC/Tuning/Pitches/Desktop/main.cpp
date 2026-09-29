#include "../Shared.h"

#include <iostream>

int main() {
    MCCExamples::Tuning::Pitches::Run(
        [](const char* text) { std::cout << text; });
    return 0;
}
