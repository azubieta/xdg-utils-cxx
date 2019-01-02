#include <gtest/gtest.h>

#include <DesktopEntry.h>

using namespace XdgUtils;

class TestDesktopEntry : public ::testing::Test {
protected:
    const std::string exampleDesktopEntry = "[Desktop Entry]\n"
                                            "Version=1.0\n"
                                            "Type=Application\n"
                                            "Name=Foo Viewer\n"
                                            "Comment=The best viewer for Foo objects available!\n"
                                            "TryExec=fooview\n"
                                            "Exec=fooview %F\n"
                                            "Icon=fooview\n"
                                            "MimeType=image/x-foo;\n"
                                            "Actions=Gallery;Create;\n"
                                            "\n"
                                            "[Desktop Action Gallery]\n"
                                            "Exec=fooview --gallery\n"
                                            "Name=Browse Gallery\n"
                                            "\n"
                                            "[Desktop Action Create]\n"
                                            "Exec=fooview --create-new\n"
                                            "Name=Create a new Foo!\n"
                                            "Icon=fooview-new\n";
};


TEST_F(TestDesktopEntry, readWrite) {
    DesktopEntry::DesktopEntry entry;

    std::stringstream in(exampleDesktopEntry);
    entry.read(in);

    std::stringstream out;
    entry.write(out);

    ASSERT_EQ(in.str(), out.str());
}

TEST_F(TestDesktopEntry, listGroups) {
    DesktopEntry::DesktopEntry entry;

    std::stringstream in(exampleDesktopEntry);
    entry.read(in);

    std::vector<std::string> expected = {"Desktop Entry", "Desktop Action Gallery", "Desktop Action Create"};
    std::vector<std::string> result = entry.listGroups();

    ASSERT_EQ(result, expected);
}

TEST_F(TestDesktopEntry, listGroupKeys) {
    DesktopEntry::DesktopEntry entry;

    std::stringstream in(exampleDesktopEntry);
    entry.read(in);

    std::vector<std::string> expected = {"Exec", "Name"};
    std::vector<std::string> result = entry.listGroupKeys("Desktop Action Gallery");

    ASSERT_EQ(result, expected);
}

TEST_F(TestDesktopEntry, get) {
    const std::string s = "[Desktop Entry]\n"
                          "Version=1.0\n"
                          "Type=Application\n"
                          "Name=Foo Viewer\n"
                          "Comment=The best viewer for Foo objects available!\n"
                          "TryExec=fooview\n"
                          "Exec=fooview %F\n"
                          "Icon=fooview\n"
                          "MimeType=image/x-foo;\n"
                          "Actions=Gallery;Create;\n"
                          "\n"
                          "[Desktop Action Gallery]\n"
                          "Exec=fooview --gallery\n"
                          "Name=Browse Gallery\n"
                          "\n"
                          "[Desktop Action Create]\n"
                          "Exec=fooview --create-new\n"
                          "Name=Create a new Foo!\n"
                          "Icon=fooview-new\n";

    DesktopEntry::DesktopEntry entry;

    std::stringstream in(s);
    entry.read(in);

    ASSERT_EQ(entry.get("Desktop Entry/Name"), "Foo Viewer");
    ASSERT_EQ(entry.get("Desktop Action Gallery/Name"), "Browse Gallery");
    ASSERT_EQ(entry.get("Desktop Action Create/Name"), "Create a new Foo!");
}

TEST_F(TestDesktopEntry, set) {
    DesktopEntry::DesktopEntry entry;

    std::stringstream in(exampleDesktopEntry);
    entry.read(in);

    entry.set("Spam", "");
    ASSERT_EQ(entry.get("Spam"), "Spam");

    entry.set("Spam/Spam", "Food");
    ASSERT_EQ(entry.get("Spam/Spam"), "Food");

    entry.set("Spam2/Spam", "Food");
    ASSERT_EQ(entry.get("Spam2/Spam"), "Food");

    entry.set("Spam2/Spam", "");
    ASSERT_EQ(entry.get("Spam2/Spam"), "");

    entry.set("Desktop Entry/Name", "New Foo Viewer");
    ASSERT_EQ(entry.get("Desktop Entry/Name"), "New Foo Viewer");

    entry.set("Desktop Action Gallery/Name", "Browse The Gallery");
    ASSERT_EQ(entry.get("Desktop Action Gallery/Name"), "Browse The Gallery");

    entry.set("Desktop Action Create/Name", "Create Foo!");
    ASSERT_EQ(entry.get("Desktop Action Create/Name"), "Create Foo!");

    entry.set("Desktop Action Create/Name[es_ES]", "Crear Foo");
    ASSERT_EQ(entry.get("Desktop Action Create/Name[es_ES]"), "Crear Foo");
}


TEST_F(TestDesktopEntry, exists) {
    DesktopEntry::DesktopEntry entry;

    std::stringstream in(exampleDesktopEntry);
    entry.read(in);

    ASSERT_TRUE(entry.exists("Desktop Action Gallery/Name"));
    ASSERT_FALSE(entry.exists("Desktop Action Gallery/Nam"));
}

TEST_F(TestDesktopEntry, removeGroup) {
    DesktopEntry::DesktopEntry entry;

    std::string entryStr = {"[G1]\nName=1\n[g2]\nName=2\n"};
    std::stringstream in(entryStr);
    entry.read(in);

    ASSERT_TRUE(entry.exists("G1"));
    entry.remove("G1");
    ASSERT_FALSE(entry.exists("G1"));

    std::stringstream out;
    entry.write(out);

    ASSERT_EQ(out.str(), "[g2]\nName=2\n");
}

TEST_F(TestDesktopEntry, removeEntry) {
    DesktopEntry::DesktopEntry entry;

    std::string entryStr = {"[G1]\nName=1\nIcon=1\n[g2]\nName=2\n"};
    std::stringstream in(entryStr);
    entry.read(in);

    ASSERT_TRUE(entry.exists("G1/Icon"));
    entry.remove("G1/Icon");
    ASSERT_FALSE(entry.exists("G1/Icon"));

    std::stringstream out;
    entry.write(out);

    ASSERT_EQ(out.str(), "[G1]\nName=1\n[g2]\nName=2\n");
}
