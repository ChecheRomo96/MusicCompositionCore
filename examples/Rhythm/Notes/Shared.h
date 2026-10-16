#ifndef MCC_EXAMPLES_RHYTHM_NOTES_SHARED_H
#define MCC_EXAMPLES_RHYTHM_NOTES_SHARED_H

namespace MCCExamples {
namespace Rhythm {
namespace Notes {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the note-construction walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace Notes
} // namespace Rhythm
} // namespace MCCExamples

#endif // MCC_EXAMPLES_RHYTHM_NOTES_SHARED_H
