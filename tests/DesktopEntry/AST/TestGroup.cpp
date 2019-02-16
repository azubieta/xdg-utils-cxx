#include <gtest/gtest.h>

#include <Entry.h>
#include <Comment.h>
#include <Group.h>

using namespace XdgUtils::DesktopEntry::AST;


TEST(TestGroup, create) {
    Group g1("[Desktop Entry]", "Desktop Entry");;
    ASSERT_EQ(g1.getValue(), "Desktop Entry");

    std::vector<std::shared_ptr<Node>> entries1;
    entries1.emplace_back(new Entry(" Name", "Name", "", "", "=My App", "My App"));
    entries1.emplace_back(new Comment("# Test", " Test"));

    g1.setEntries(entries1);

    auto res = g1.getEntries();
    for (int i = 0; i < entries1.size(); ++i)
        ASSERT_EQ(*res[i], *entries1[i]);
}

TEST(TestGroup, compare) {
    Group g1("[Desktop Entry]", "Desktop Entry");;

    std::vector<std::shared_ptr<Node>> entries1;
    entries1.emplace_back(new Entry(" Name", "Name", "", "", "=My App", "My App"));
    entries1.emplace_back(new Comment("# Test", " Test"));
    g1.setEntries(entries1);

    Group g2("[Desktop Entry]", "Desktop Entry");;

    std::vector<std::shared_ptr<Node>> entries2;
    entries2.emplace_back(new Entry(" Name", "Name", "", "", "=My App", "My App"));
    entries2.emplace_back(new Comment("# Test", " Test"));
    g2.setEntries(entries2);

    ASSERT_EQ(g1, g2);

    entries1.emplace_back(new Comment("# Test", " Test"));
    g1.setEntries(entries1);

    ASSERT_NE(g1, g2);
}

TEST(TestGroup, write) {
    Group g1("[Desktop Entry]", "Desktop Entry");;

    std::vector<std::shared_ptr<Node>> entries1;
    entries1.emplace_back(new Entry(" Name", "Name", "", "", "=My App", "My App"));
    entries1.emplace_back(new Comment("# Test", " Test"));
    g1.setEntries(entries1);

    std::stringstream res;
    g1.write(res);

    ASSERT_EQ(res.str(), "[Desktop Entry]\n Name=My App\n# Test");
}

TEST(TestGroup, copy) {
    Group g1("[Desktop Entry]", "Desktop Entry");;

    std::vector<std::shared_ptr<Node>> entries1;
    entries1.emplace_back(new Entry(" Name", "Name", "", "", "=My App", "My App"));
    entries1.emplace_back(new Comment("# Test", " Test"));
    g1.setEntries(entries1);

    Group g2 = g1;
    ASSERT_EQ(g1, g2);

    // Assert each group has a different copy of the entries
    g1.getEntries().front()->setValue("Your App");

    ASSERT_NE(g1, g2);
}

TEST(TestGroup, move) {
    Group g1("[Desktop Entry]", "Desktop Entry");;

    std::vector<std::shared_ptr<Node>> entries1;
    entries1.emplace_back(new Entry(" Name", "Name", "", "", "=My App", "My App"));
    entries1.emplace_back(new Comment("# Test", " Test"));
    g1.setEntries(entries1);

    Group g2 = std::move(g1);
    ASSERT_NE(g2.getEntries(), entries1);
}
