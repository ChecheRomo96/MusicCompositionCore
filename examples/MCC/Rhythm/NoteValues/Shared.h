#ifndef MCC_EXAMPLES_RHYTHM_NOTE_VALUES_SHARED_H
#define MCC_EXAMPLES_RHYTHM_NOTE_VALUES_SHARED_H

namespace MCCExamples {
namespace Rhythm {
namespace NoteValues {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the exact note-value walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace NoteValues
} // namespace Rhythm
} // namespace MCCExamples

#endif // MCC_EXAMPLES_RHYTHM_NOTE_VALUES_SHARED_H
