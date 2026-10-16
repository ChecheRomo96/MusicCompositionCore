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

void Run(PrintFunction print) noexcept {
    // These strings come from the linked libraries, not from example labels.
    // Both launchers run this same code; only their print callback differs.
    const char* mccVersion = MCCVersion();
    const char* foundationVersion = FoundationVersion();

    print("========================================\n");
    print(" MCC :: Core / Version\n");
    print("========================================\n");
    print(" MCC ........... ");
    print(mccVersion);
    print("\n Foundation .... ");
    print(foundationVersion);
    print("\n========================================\n");
}

} // namespace Version
} // namespace Core
} // namespace MCCExamples
