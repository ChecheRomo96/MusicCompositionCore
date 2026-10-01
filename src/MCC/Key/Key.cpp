#include <MCC/Key/Key.h>

#include <Foundation/Utils/Flash.h>

namespace MCC {

namespace {

    // Catalog scale of each KeyMode, in program memory on AVR: a switch
    // would be turned into a RAM lookup table by the compiler.
    constexpr Scales::Id ModeScales[] FOUNDATION_FLASH = {
        Scales::Id::Lydian, Scales::Id::Major, Scales::Id::Mixolydian,
        Scales::Id::Dorian, Scales::Id::Minor, Scales::Id::Phrygian,
        Scales::Id::Locrian};

} // namespace

Scales::Id Key::ScaleId() const noexcept {
    return IsValid()
        ? Foundation::Utils::Flash::Read(&ModeScales[static_cast<uint8_t>(_mode)])
        : Scales::Id::Invalid;
}

} // namespace MCC
