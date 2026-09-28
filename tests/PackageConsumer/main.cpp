#include <Foundation/Math/Arithmetic.h>
#include <MCC.h>

#include <iostream>

#ifndef MCC_PITCH
    #error "The installed MCC package must export MCC_PITCH"
#endif

#ifndef MCC_TUNING
    #error "The installed MCC package must export MCC_TUNING"
#endif

int main() {
    const auto gcd = Foundation::Math::GCD(12, 8);

    constexpr MCC::PitchClass cSharp(MCC::Letter::C, MCC::Accidental::Sharp());
    constexpr MCC::PitchClass dFlat(MCC::Letter::D, MCC::Accidental::Flat());
    static_assert(cSharp != dFlat && MCC::IsEnharmonic(cSharp, dFlat));

    const int chromaticClass = cSharp.ChromaticClass().Value();

    constexpr MCC::Pitch a4(MCC::Letter::A, 4);
    const float a4Frequency = MCC::EqualTemperament::Standard().Frequency(a4);

    std::cout << "MCC: " << MCC::Core::Version() << '\n';
    std::cout << "Foundation: " << MCC::Core::FoundationVersion() << '\n';
    std::cout << "Foundation::Math::GCD(12, 8): " << gcd << '\n';
    std::cout << "C# chromatic class: " << chromaticClass << '\n';
    std::cout << "A4 chromatic index: " << a4.ChromaticIndex().Value() << '\n';
    std::cout << "A4 frequency: " << a4Frequency << " Hz\n";

    return (gcd == 4U && chromaticClass == 1 &&
            a4.ChromaticIndex().Value() == 69 && a4Frequency == 440.0f) ? 0 : 1;
}
