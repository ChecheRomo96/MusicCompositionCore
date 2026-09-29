#ifndef MCC_EXAMPLES_PITCH_NOTE_NAMEES_SHARED_H
#define MCC_EXAMPLES_PITCH_NOTE_NAMEES_SHARED_H

namespace MCCExamples::Pitch::NoteNames {

/** @brief Receives one chunk of text to print. */
using PrintFunction = void (*)(const char* text);

/** @brief Prints the note-name walkthrough through `print`. */
void Run(PrintFunction print) noexcept;

} // namespace MCCExamples::Pitch::NoteNames

#endif // MCC_EXAMPLES_PITCH_NOTE_NAMEES_SHARED_H
