#include <gtest/gtest.h>

#include <XdgUtils/DesktopEntry/DesktopEntryKeyPath.h>

using namespace XdgUtils::DesktopEntry;


TEST(TestDesktopEntryKeyPath, create) {
    DesktopEntryKeyPath path("Desktop Entry");
    path = "Desktop Entry/Name";
}

TEST(TestDesktopEntryKeyPath, string) {
    DesktopEntryKeyPath path("a");
    path.setGroup("g");
    ASSERT_EQ(path, "g");
    ASSERT_THROW(path.setGroup(""), MalformedPathError);

    path.setKey("k");
    ASSERT_EQ(path, "g/k");

    path.setKey("k_k");
    ASSERT_EQ(path, "g/k_k");

    path.setKey("k-k");
    ASSERT_EQ(path, "g/k-k");
    ASSERT_THROW(path.setKey("@!@#$"), MalformedPathError);

    path.setLocale("l");
    ASSERT_EQ(path, "g/k-k[l]");
}

TEST(TestDesktopEntryKeyPath, parseGroup) {
    // Test group parsing
    ASSERT_EQ(DesktopEntryKeyPath("Desktop Entry"), "Desktop Entry");
    ASSERT_THROW(DesktopEntryKeyPath("Invalid Group["), ParseError);
    ASSERT_THROW(DesktopEntryKeyPath("Invalid Group]"), ParseError);
}

TEST(TestDesktopEntryKeyPath, parseKey) {
    ASSERT_EQ(DesktopEntryKeyPath("G/K"), "G/K");
    ASSERT_EQ(DesktopEntryKeyPath("G/K-K"), "G/K-K");
    ASSERT_EQ(DesktopEntryKeyPath("G/K_K"), "G/K_K");
    ASSERT_THROW(DesktopEntryKeyPath("Invalid/Key]"), ParseError);
    ASSERT_THROW(DesktopEntryKeyPath("Invalid/Key#"), ParseError);
    ASSERT_THROW(DesktopEntryKeyPath("Invalid/#"), ParseError);
}

TEST(TestDesktopEntryKeyPath, parseLocale) {
    ASSERT_EQ(DesktopEntryKeyPath("G/K[l]"), "G/K[l]");
    ASSERT_EQ(DesktopEntryKeyPath("G/K[l_C]"), "G/K[l_C]");
    ASSERT_EQ(DesktopEntryKeyPath("G/K[l@M]"), "G/K[l@M]");
    ASSERT_EQ(DesktopEntryKeyPath("G/K[l_C@M]"), "G/K[l_C@M]");

    ASSERT_THROW(DesktopEntryKeyPath("G/K[l_C@M"), ParseError);
}
