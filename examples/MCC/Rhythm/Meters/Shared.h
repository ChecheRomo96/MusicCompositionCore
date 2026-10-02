#ifndef MCC_EXAMPLES_RHYTHM_METERS_SHARED_H
#define MCC_EXAMPLES_RHYTHM_METERS_SHARED_H

namespace MCCExamples {
namespace Rhythm {
namespace Meters {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the meter walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace Meters
} // namespace Rhythm
} // namespace MCCExamples

#endif // MCC_EXAMPLES_RHYTHM_METERS_SHARED_H
