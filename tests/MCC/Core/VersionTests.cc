#include <gtest/gtest.h>

#include <Foundation/Math/Arithmetic.h>
#include <MCC.h>
#include <MCC/Core/Version.h>
#include <MCC_Core.h>

TEST(MCCCoreTests, ReportsMCCVersion) {
    EXPECT_STREQ(MCC::Core::Version(), MCC_VERSION);
}

TEST(MCCCoreTests, ReportsFoundationVersion) {
    EXPECT_STREQ(MCC::Core::FoundationVersion(), FOUNDATION_VERSION);
}

TEST(MCCCoreTests, PropagatesFoundationDependency) {
    EXPECT_EQ(Foundation::Math::GCD(12, 8), 4U);
}
