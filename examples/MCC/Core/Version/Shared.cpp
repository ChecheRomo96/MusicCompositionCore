#include "Shared.h"

#include <MCC/Core/Version.h>

namespace MCCExamples {
namespace Core {
namespace Version {

const char* MCCVersion() noexcept {
    return MCC::Core::Version();
}

const char* FoundationVersion() noexcept {
    return MCC::Core::FoundationVersion();
}

} // namespace Version
} // namespace Core
} // namespace MCCExamples
