#ifndef MCC_EXAMPLES_RHYTHM_RHYTHM_PATTERNS_SHARED_H
#define MCC_EXAMPLES_RHYTHM_RHYTHM_PATTERNS_SHARED_H

namespace MCCExamples {
namespace Rhythm {
namespace RhythmPatterns {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the rhythm pattern walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace RhythmPatterns
} // namespace Rhythm
} // namespace MCCExamples

#endif // MCC_EXAMPLES_RHYTHM_RHYTHM_PATTERNS_SHARED_H
