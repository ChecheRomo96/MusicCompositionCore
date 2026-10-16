#include "../Shared.h"

#include <iostream>

int main() {
    MCCExamples::Core::Version::Run(
        [](const char* text) { std::cout << text; });
    return 0;
}
