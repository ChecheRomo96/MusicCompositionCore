#include <MCC/Core/Version.h>

#include <Foundation_BuildSettings.h>
#include <MCC_BuildSettings.h>

namespace MCC {
namespace Core {

const char* Version() noexcept {
    return MCC_VERSION;
}

const char* FoundationVersion() noexcept {
    return FOUNDATION_VERSION;
}

} // namespace Core
} // namespace MCC
