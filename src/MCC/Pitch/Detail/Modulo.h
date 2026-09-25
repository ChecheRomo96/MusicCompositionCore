#ifndef MCC_PITCH_DETAIL_MODULO_H
#define MCC_PITCH_DETAIL_MODULO_H

/** @cond */
namespace MCC::Detail {

// Floored modulo for a positive modulus: the result is always in
// [0, modulus - 1], also for negative values. Generic arithmetic kept private
// until Foundation::Math provides an equivalent.
constexpr int FloorMod(int value, int modulus) noexcept {
    const int remainder = value % modulus;
    return (remainder < 0) ? remainder + modulus : remainder;
}

} // namespace MCC::Detail
/** @endcond */

#endif // MCC_PITCH_DETAIL_MODULO_H
