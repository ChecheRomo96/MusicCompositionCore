#include "../Shared.h"

#include <iostream>

int main() {
    MCCExamples::Rhythm::Meters::Run(
        [](const char* text) { std::cout << text; });
    return 0;
}
