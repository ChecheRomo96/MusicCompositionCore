#ifndef MCC_EXAMPLES_KEY_KEYS_SHARED_H
#define MCC_EXAMPLES_KEY_KEYS_SHARED_H

namespace MCCExamples::Key::Keys {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the key and notation walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace MCCExamples::Key::Keys

#endif // MCC_EXAMPLES_KEY_KEYS_SHARED_H
