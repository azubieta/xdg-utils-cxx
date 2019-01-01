#include <gtest/gtest.h>

#include <Comment.h>

using namespace XdgUtils::DesktopEntry::AST;

TEST(TestComment, create) {
    Comment comment1("# Test", " Test");

    ASSERT_EQ(" Test", comment1.getValue());
}

TEST(TestComment, setValue) {
    Comment comment1("# Test", " Test");

    comment1.setValue(" More Tests!");
    ASSERT_EQ(" More Tests!", comment1.getValue());

    std::stringstream out;
    comment1.write(out);

    ASSERT_EQ("# More Tests!", out.str());
}

TEST(TestComment, setValueToEmpty) {
    Comment comment1("", "");
    comment1.setValue(" More Tests!");
    ASSERT_EQ(" More Tests!", comment1.getValue());

    std::stringstream out;
    comment1.write(out);

    ASSERT_EQ("# More Tests!", out.str());
}

TEST(TestComment, compare) {
    ASSERT_EQ(Comment("", ""), Comment("", ""));
    ASSERT_EQ(Comment("# ", " Random Rocker"), Comment("# ", " Random Rocker"));
    ASSERT_EQ(Comment("# ", " Random Rocker"), Comment("#", " Random Rocker"));
    ASSERT_NE(Comment("# ", " Random Blocker"), Comment("#", " Random Rocker"));
    ASSERT_NE(Comment("", ""), Comment("#", " Random Rocker"));
}
