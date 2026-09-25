#include <Foundation/Math/Arithmetic.h>
#include <MCC.h>

#include <iostream>

#ifndef MCC_PITCH
    #error "The installed MCC package must export MCC_PITCH"
#endif

int main() {
    const auto gcd = Foundation::Math::GCD(12, 8);

    constexpr MCC::PitchClass cSharp(MCC::Letter::C, MCC::Accidental::Sharp());
    constexpr MCC::PitchClass dFlat(MCC::Letter::D, MCC::Accidental::Flat());
    static_assert(cSharp != dFlat && MCC::IsEnharmonic(cSharp, dFlat));

    const int chromaticClass = cSharp.ChromaticClass().Value();

    std::cout << "MCC: " << MCC::Core::Version() << '\n';
    std::cout << "Foundation: " << MCC::Core::FoundationVersion() << '\n';
    std::cout << "Foundation::Math::GCD(12, 8): " << gcd << '\n';
    std::cout << "C# chromatic class: " << chromaticClass << '\n';

    return (gcd == 4U && chromaticClass == 1) ? 0 : 1;
}
