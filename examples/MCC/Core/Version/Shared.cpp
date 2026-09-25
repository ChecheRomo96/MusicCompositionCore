#include "Shared.h"

#include <MCC/Core/Version.h>

namespace MCCExamples::Core::Version {

const char* MCCVersion() noexcept {
    return MCC::Core::Version();
}

const char* FoundationVersion() noexcept {
    return MCC::Core::FoundationVersion();
}

} // namespace MCCExamples::Core::Version
