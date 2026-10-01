#include "../Shared.h"

#include <iostream>

int main() {
    MCCExamples::Scale::Scales::Run(
        [](const char* text) { std::cout << text; });
    return 0;
}
