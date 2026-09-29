#ifndef MCC_EXAMPLES_INTERVAL_INTERVALS_SHARED_H
#define MCC_EXAMPLES_INTERVAL_INTERVALS_SHARED_H

namespace MCCExamples::Interval::Intervals {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the interval walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace MCCExamples::Interval::Intervals

#endif // MCC_EXAMPLES_INTERVAL_INTERVALS_SHARED_H
