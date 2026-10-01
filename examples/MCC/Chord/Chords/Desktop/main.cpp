#include "../Shared.h"

#include <iostream>

int main() {
    MCCExamples::Chord::Chords::Run(
        [](const char* text) { std::cout << text; });
    return 0;
}
