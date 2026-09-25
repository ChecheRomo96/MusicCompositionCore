#ifndef MCC_CORE_VERSION_H
#define MCC_CORE_VERSION_H

namespace MCC::Core {

/** @brief Returns the MCC semantic version compiled into the library. */
const char* Version() noexcept;

/** @brief Returns the Foundation semantic version used to build MCC. */
const char* FoundationVersion() noexcept;

} // namespace MCC::Core

#endif // MCC_CORE_VERSION_H
