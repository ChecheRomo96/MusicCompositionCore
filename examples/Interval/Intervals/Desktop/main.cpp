#include "../Shared.h"

#include <iostream>

int main() {
    MCCExamples::Interval::Intervals::Run(
        [](const char* text) { std::cout << text; });
    return 0;
}
