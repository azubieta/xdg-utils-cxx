#include <gtest/gtest.h>

#include <AST.h>
#include <Comment.h>
#include <Entry.h>
#include <Group.h>

using namespace XdgUtils::DesktopEntry::AST;


TEST(TestAST, create) {
    AST ast1;

    auto g1 = new Group("[Desktop Entry]", "Desktop Entry");;
    std::vector<std::shared_ptr<Node>> g1Entries = {
        std::shared_ptr<Node>(new Entry(" Name", "Name", "", "", "=My App", "My App")),
        std::shared_ptr<Node>(new Comment("# Test", " Test"))
    };

    g1->setEntries(g1Entries);

    std::vector<std::shared_ptr<Node>> ast1Entries = {
        std::shared_ptr<Node>(new Comment("# Test", " Test")),
        std::shared_ptr<Node>(g1)
    };

    ast1.setEntries(ast1Entries);;
}

TEST(TestAST, compare) {
    AST ast1;

    auto g1 = new Group("[Desktop Entry]", "Desktop Entry");;
    std::vector<std::shared_ptr<Node>> g1Entries = {
        std::shared_ptr<Node>(new Entry(" Name", "Name", "", "", "=My App", "My App")),
        std::shared_ptr<Node>(new Comment("# Test", " Test"))
    };

    g1->setEntries(g1Entries);

    std::vector<std::shared_ptr<Node>> ast1Entries = {
        std::shared_ptr<Node>(new Comment("# Test", " Test")),
        std::shared_ptr<Node>(g1)
    };

    ast1.setEntries(ast1Entries);;

    AST ast2;
    auto g2 = new Group("[Desktop Entry]", "Desktop Entry");;
    std::vector<std::shared_ptr<Node>> g2Entries = {
        std::shared_ptr<Node>(new Entry(" Name", "Name", "", "", "=My App", "My App")),
        std::shared_ptr<Node>(new Comment("# Test", " Test"))
    };

    g2->setEntries(g2Entries);

    std::vector<std::shared_ptr<Node>> ast2Entries = {
        std::shared_ptr<Node>(new Comment("# Test", " Test")),
        std::shared_ptr<Node>(g2)
    };

    ast2.setEntries(ast2Entries);;

    ASSERT_EQ(ast1, ast2);


    AST ast3;
    auto g3 = new Group("[Desktop Entry]", "Desktop Entry");;
    std::vector<std::shared_ptr<Node>> g3Entries = {
        std::shared_ptr<Node>(new Entry(" Name", "Name", "", "", "=My App", "My App")),
        std::shared_ptr<Node>(new Comment("# Test", " Test"))
    };

    g3->setEntries(g3Entries);
    std::vector<std::shared_ptr<Node>> ast3Entries = {std::shared_ptr<Node>(g3)};

    ast3.setEntries(ast3Entries);;

    ASSERT_NE(ast1, ast3);
}

TEST(TestAST, write) {
    AST ast1;

    auto g1 = new Group("[Desktop Entry]", "Desktop Entry");;
    std::vector<std::shared_ptr<Node>> g1Entries = {
        std::shared_ptr<Node>(new Entry(" Name", "Name", "", "", "=My App", "My App")),
        std::shared_ptr<Node>(new Comment("# Test", " Test"))
    };

    g1->setEntries(g1Entries);

    std::vector<std::shared_ptr<Node>> ast1Entries = {
        std::shared_ptr<Node>(new Comment("# Test", " Test")),
        std::shared_ptr<Node>(g1)
    };

    ast1.setEntries(ast1Entries);;

    std::stringstream res;
    ast1.write(res);

    ASSERT_EQ(res.str(),
              "# Test\n"
              "[Desktop Entry]\n"
              " Name=My App\n"
              "# Test");
}


TEST(TestAST, copy) {
    AST ast1;

    auto g1 = new Group("[Desktop Entry]", "Desktop Entry");;
    std::vector<std::shared_ptr<Node>> g1Entries = {
        std::shared_ptr<Node>(new Entry(" Name", "Name", "", "", "=My App", "My App")),
        std::shared_ptr<Node>(new Comment("# Test", " Test"))
    };

    g1->setEntries(g1Entries);

    std::vector<std::shared_ptr<Node>> ast1Entries = {
        std::shared_ptr<Node>(new Comment("# Test", " Test")),
        std::shared_ptr<Node>(g1)
    };

    ast1.setEntries(ast1Entries);;

    AST ast2 = ast1;
    ASSERT_EQ(ast1, ast2);

    ast1.getEntries().front()->setValue("Desktop Action One");
    ASSERT_NE(ast1, ast2);
}


TEST(TestAST, move) {
    AST ast1;

    auto g1 = new Group("[Desktop Entry]", "Desktop Entry");;
    std::vector<std::shared_ptr<Node>> g1Entries = {
        std::shared_ptr<Node>(new Entry(" Name", "Name", "", "", "=My App", "My App")),
        std::shared_ptr<Node>(new Comment("# Test", " Test"))
    };

    g1->setEntries(g1Entries);

    std::vector<std::shared_ptr<Node>> ast1Entries = {
        std::shared_ptr<Node>(new Comment("# Test", " Test")),
        std::shared_ptr<Node>(g1)
    };

    ast1.setEntries(ast1Entries);;

    std::stringstream stream1;
    stream1 << ast1;

    AST ast2 = std::move(ast1);
    std::stringstream stream2;
    stream2 << ast2;

    ASSERT_EQ(stream1.str(), stream2.str());
}

