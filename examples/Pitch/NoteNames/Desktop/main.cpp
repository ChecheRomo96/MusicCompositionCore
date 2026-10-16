#include "../Shared.h"

#include <iostream>

int main() {
    MCCExamples::Pitch::NoteNames::Run(
        [](const char* text) { std::cout << text; });
    return 0;
}
