// system
#include <cstdlib>

// library
#include <gtest/gtest.h>

// local
#include <XdgUtils/BaseDir/BaseDir.h>

TEST(TestBaseDir, dataHomeFromEnv) {
    setenv("XDG_DATA_HOME", "/tmp/dataHome", 1);

    const std::string& dataHome = XdgUtils::BaseDir::XdgDataHome();
    ASSERT_EQ(dataHome, "/tmp/dataHome");
}

TEST(TestBaseDir, dataHomeFromFallback) {
    setenv("XDG_DATA_HOME", "", 1);

    std::string dataHome = XdgUtils::BaseDir::XdgDataHome();
    std::string home = XdgUtils::BaseDir::Home();

    ASSERT_EQ(dataHome, home + "/.local/share");
}

