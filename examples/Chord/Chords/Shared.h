#ifndef MCC_EXAMPLES_CHORD_CHORDS_SHARED_H
#define MCC_EXAMPLES_CHORD_CHORDS_SHARED_H

namespace MCCExamples {
namespace Chord {
namespace Chords {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the chord walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace Chords
} // namespace Chord
} // namespace MCCExamples

#endif // MCC_EXAMPLES_CHORD_CHORDS_SHARED_H
