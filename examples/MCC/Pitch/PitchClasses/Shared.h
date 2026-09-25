#ifndef MCC_EXAMPLES_PITCH_PITCH_CLASSES_SHARED_H
#define MCC_EXAMPLES_PITCH_PITCH_CLASSES_SHARED_H

namespace MCCExamples::Pitch::PitchClasses {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the pitch-class walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace MCCExamples::Pitch::PitchClasses

#endif // MCC_EXAMPLES_PITCH_PITCH_CLASSES_SHARED_H
