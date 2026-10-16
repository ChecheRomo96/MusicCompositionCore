#include "../Shared.h"

#include <iostream>

int main() {
    MCCExamples::Rhythm::RhythmPatterns::Run(
        [](const char* text) { std::cout << text; });
    return 0;
}
