#ifndef MCC_EXAMPLES_SCALE_SCALES_SHARED_H
#define MCC_EXAMPLES_SCALE_SCALES_SHARED_H

namespace MCCExamples::Scale::Scales {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the scale walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace MCCExamples::Scale::Scales

#endif // MCC_EXAMPLES_SCALE_SCALES_SHARED_H
