// libraries
#include <gtest/gtest.h>

// local
#include <XdgUtils/DesktopEntry/DesktopEntryExecValue.h>

using namespace XdgUtils::DesktopEntry;

TEST(TestDesktopDesktopEntryExecValue, create) {
    DesktopEntryExecValue value("fooview %F");
}

TEST(TestDesktopDesktopEntryExecValue, size) {
    ASSERT_EQ(DesktopEntryExecValue("fooview %F").size(), 2);
    ASSERT_EQ(DesktopEntryExecValue("\"spaced dir/run\" %F").size(), 2);
}


TEST(TestDesktopDesktopEntryExecValue, access) {
    DesktopEntryExecValue value("\"spaced dir/run\" %F");

    std::vector<std::string> expected = {"spaced dir/run", "%F"};
    ASSERT_EQ(value.size(), expected.size());
    for (int i = 0; i < value.size(); ++i)
        ASSERT_EQ(value[i], expected[i]);
}

TEST(TestDesktopDesktopEntryExecValue, dump) {
    const auto str = "\"spaced dir/run\" %F";
    DesktopEntryExecValue value(str);

    ASSERT_EQ(value.dump(), str);
}

TEST(TestDesktopDesktopEntryExecValue, set) {
    const auto str = "\"spaced dir/run\" %F";
    DesktopEntryExecValue value(str);

    value[0] = "random/$PWD/bin";
    ASSERT_EQ(value.dump(), "\"random/\\$PWD/bin\" %F");
}

TEST(TestDesktopDesktopEntryExecValue, append) {
    DesktopEntryExecValue stringList;
    stringList.append("1");

    ASSERT_EQ(stringList.size(), 1);
    ASSERT_EQ(stringList[0], "1");
}

TEST(TestDesktopDesktopEntryExecValue, remove) {
    DesktopEntryExecValue stringList("1 2");
    stringList.remove(0);

    ASSERT_EQ(stringList.size(), 1);
    ASSERT_EQ(stringList[0], "2");
}
