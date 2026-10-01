#ifndef MCC_EXAMPLES_SCALE_SCALES_SHARED_H
#define MCC_EXAMPLES_SCALE_SCALES_SHARED_H

namespace MCCExamples {
namespace Scale {
namespace Scales {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the scale walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace Scales
} // namespace Scale
} // namespace MCCExamples

#endif // MCC_EXAMPLES_SCALE_SCALES_SHARED_H
