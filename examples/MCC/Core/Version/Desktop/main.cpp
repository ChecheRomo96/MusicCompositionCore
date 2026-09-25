#include "../Shared.h"

#include <iostream>

int main() {
    std::cout << "========================================\n"
              << " MCC :: Core / Version\n"
              << "========================================\n"
              << " MCC ........... "
              << MCCExamples::Core::Version::MCCVersion() << '\n'
              << " Foundation .... "
              << MCCExamples::Core::Version::FoundationVersion() << '\n'
              << "========================================\n";
    return 0;
}
