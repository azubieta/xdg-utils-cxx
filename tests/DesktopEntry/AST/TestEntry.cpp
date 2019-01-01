#include <gtest/gtest.h>

#include <Entry.h>

using namespace XdgUtils::DesktopEntry::AST;

TEST(TestEntry, create) {
    Entry e1(" Name", "Name", "[es] ", "es", "= Mi App", "Mi App");

    ASSERT_EQ("Name", e1.getKey());
    ASSERT_EQ("es", e1.getLocale());
    ASSERT_EQ("Mi App", e1.getValue());
}

TEST(TestEntry, write) {
    Entry e1("Name", "Name", "[es] ", "es", "= Mi App", "Mi App");
    std::stringstream s;
    e1.write(s);

    ASSERT_EQ("Name[es] = Mi App", s.str());
}

TEST(TestEntry, setRegularEntryValue) {
    Entry e1(" Name", "Name", "[es] ", "es", "= Mi App", "Mi App");
    e1.setValue("Mi Grand App");

    ASSERT_EQ("Mi Grand App", e1.getValue());

    std::stringstream s;
    e1.write(s);

    ASSERT_EQ(" Name[es] = Mi Grand App", s.str());
}

TEST(TestEntry, setEmptyEntryValue) {
    Entry e1(" Name", "Name", "[es] ", "es", "= ", "");
    e1.setValue("Mi Grand App");

    ASSERT_EQ("Mi Grand App", e1.getValue());

    std::stringstream s;
    e1.write(s);

    ASSERT_EQ(" Name[es] = Mi Grand App", s.str());
}


TEST(TestEntry, compare) {
    Entry e1(" Name", "Name", "[es] ", "es", "= Mi App", "Mi App");
    Entry e2(" Name", "Name", "[es]", "es", "=Mi App", "Mi App");

    ASSERT_EQ(e1, e2);
}

