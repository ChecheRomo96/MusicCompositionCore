#include <Foundation/Math/Arithmetic.h>
#include <MCC.h>

#include <iostream>

#ifndef MCC_PITCH
    #error "The installed MCC package must export MCC_PITCH"
#endif

#ifndef MCC_INTERVAL
    #error "The installed MCC package must export MCC_INTERVAL"
#endif

#ifndef MCC_TUNING
    #error "The installed MCC package must export MCC_TUNING"
#endif

int main() {
    const auto gcd = Foundation::Math::GCD(12, 8);

    constexpr MCC::NoteName cSharp(MCC::Letter::C, MCC::Accidental::Sharp());
    constexpr MCC::NoteName dFlat(MCC::Letter::D, MCC::Accidental::Flat());
    static_assert(cSharp != dFlat && MCC::IsEnharmonic(cSharp, dFlat));

    const int pitchClass = cSharp.PitchClass().Value();

    constexpr MCC::Pitch a4(MCC::Letter::A, 4);
    const float a4Frequency = MCC::EqualTemperament::Standard().Frequency(a4);

    constexpr MCC::Interval majorThird(
        MCC::IntervalQuality::Major(), MCC::IntervalNumber(3));
    constexpr MCC::Pitch cSharp5 = a4 + majorThird;
    static_assert(cSharp5 == MCC::Pitch(MCC::Letter::C, MCC::Accidental::Sharp(), 5));

    std::cout << "MCC: " << MCC::Core::Version() << '\n';
    std::cout << "Foundation: " << MCC::Core::FoundationVersion() << '\n';
    std::cout << "Foundation::Math::GCD(12, 8): " << gcd << '\n';
    std::cout << "C# pitch class: " << pitchClass << '\n';
    std::cout << "A4 chromatic index: " << a4.ChromaticIndex().Value() << '\n';
    std::cout << "A4 frequency: " << a4Frequency << " Hz\n";
    std::cout << "A4 + M3 chromatic index: " << cSharp5.ChromaticIndex().Value() << '\n';

    return (gcd == 4U && pitchClass == 1 &&
            a4.ChromaticIndex().Value() == 69 && a4Frequency == 440.0f &&
            cSharp5.ChromaticIndex().Value() == 73) ? 0 : 1;
}
