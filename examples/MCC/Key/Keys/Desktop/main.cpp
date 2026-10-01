#include "../Shared.h"

#include <iostream>

int main() {
    MCCExamples::Key::Keys::Run(
        [](const char* text) { std::cout << text; });
    return 0;
}
