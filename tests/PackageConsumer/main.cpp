#include <Foundation/Math/Arithmetic.h>
#include <MCC/Core/Version.h>

#include <iostream>

int main() {
    const auto gcd = Foundation::Math::GCD(12, 8);

    std::cout << "MCC: " << MCC::Core::Version() << '\n';
    std::cout << "Foundation: " << MCC::Core::FoundationVersion() << '\n';
    std::cout << "Foundation::Math::GCD(12, 8): " << gcd << '\n';

    return gcd == 4U ? 0 : 1;
}
