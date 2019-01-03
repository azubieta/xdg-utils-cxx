// libraries
#include <gtest/gtest.h>

// local
#include <DesktopEntry/DesktopEntryStringList.h>

using namespace XdgUtils::DesktopEntry;

TEST(TestDesktopEntryStringList, create) {
    DesktopEntryStringList stringList("one;two;three");
}

TEST(TestDesktopEntryStringList, size) {
    DesktopEntryStringList stringList("part one;part two;three\\;;four;");
    ASSERT_EQ(stringList.size(), 4);
}

TEST(TestDesktopEntryStringList, access) {
    DesktopEntryStringList stringList("part one;part two;three\\;;four;;");
    ASSERT_EQ(stringList.size(), 5);

    std::vector<std::string> expected = {"part one", "part two", "three;", "four", ""};
    ASSERT_EQ(stringList.size(), expected.size());
    for (int i = 0; i < stringList.size(); ++i)
        ASSERT_EQ(stringList[i], expected[i]);
}

TEST(TestDesktopEntryStringList, dump) {
    auto str = "part one;part two;three\\;;four;";
    DesktopEntryStringList stringList(str);
    ASSERT_EQ(stringList.dump(), str);
}

TEST(TestDesktopEntryStringList, set) {
    auto str = "part one;part two;three\\;;four;";
    DesktopEntryStringList stringList(str);

    stringList[0] = "1";
    stringList[1] = "2";
    stringList[2] = "3";
    stringList[3] = "4";

    ASSERT_EQ(stringList.dump(), "1;2;3;4;");
}
