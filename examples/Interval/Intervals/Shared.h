#ifndef MCC_EXAMPLES_INTERVAL_INTERVALS_SHARED_H
#define MCC_EXAMPLES_INTERVAL_INTERVALS_SHARED_H

namespace MCCExamples {
namespace Interval {
namespace Intervals {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the interval walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace Intervals
} // namespace Interval
} // namespace MCCExamples

#endif // MCC_EXAMPLES_INTERVAL_INTERVALS_SHARED_H
