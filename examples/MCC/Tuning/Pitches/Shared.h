#ifndef MCC_EXAMPLES_TUNING_PITCHES_SHARED_H
#define MCC_EXAMPLES_TUNING_PITCHES_SHARED_H

namespace MCCExamples::Tuning::Pitches {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the pitch and frequency walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace MCCExamples::Tuning::Pitches

#endif // MCC_EXAMPLES_TUNING_PITCHES_SHARED_H
