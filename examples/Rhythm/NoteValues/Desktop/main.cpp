#include "../Shared.h"

#include <iostream>

int main() {
    MCCExamples::Rhythm::NoteValues::Run(
        [](const char* text) { std::cout << text; });
    return 0;
}
