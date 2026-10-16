#include "../Shared.h"

#include <iostream>

int main() {
    MCCExamples::Rhythm::Notes::Run(
        [](const char* text) { std::cout << text; });
    return 0;
}
