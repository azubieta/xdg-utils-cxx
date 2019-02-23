#include <gtest/gtest.h>

#include <XdgUtils/DesktopEntry/DesktopEntry.h>

using namespace XdgUtils::DesktopEntry;

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


TEST_F(TestDesktopEntry, create) {
    DesktopEntry a;
    auto entryPath = "Desktop Entry/Name";
    auto entryValue = "A";
    a.set(entryPath, entryValue);

    // Copy constructor
    DesktopEntry b = a;
    ASSERT_EQ(a.get(entryPath), b.get(entryPath));

    ASSERT_EQ(a, b);

    b.set(entryPath, "b");
    ASSERT_NE(a, b);
}

TEST_F(TestDesktopEntry, readWrite) {
    DesktopEntry entry;

    std::stringstream in(exampleDesktopEntry);
    in >> entry;

    std::stringstream out;
    out << entry;

    ASSERT_EQ(in.str(), out.str());
}

TEST_F(TestDesktopEntry, paths) {
    DesktopEntry entry{
        "[Desktop Entry]\n"
        "Version=1.0\n"
        "Type=Application\n"
        "Name=Foo Viewer\n"
        "Comment=The best viewer for Foo objects available!\n"
        "TryExec=fooview\n"
        "Exec=fooview %F\n"
        "Icon=fooview\n"
    };

    std::vector<std::string> paths = entry.paths();
    std::vector<std::string> expectedPaths = {
        "Desktop Entry",
        "Desktop Entry/Comment",
        "Desktop Entry/Exec",
        "Desktop Entry/Icon",
        "Desktop Entry/Name",
        "Desktop Entry/TryExec",
        "Desktop Entry/Type",
        "Desktop Entry/Version",
    };

    ASSERT_EQ(paths, expectedPaths);
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

    DesktopEntry entry;

    std::stringstream in(s);
    in >> entry;

    ASSERT_EQ(entry.get("Desktop Entry/Name"), "Foo Viewer");
    ASSERT_EQ(entry.get("Desktop Action Gallery/Name"), "Browse Gallery");
    ASSERT_EQ(entry.get("Desktop Action Create/Name"), "Create a new Foo!");
}

TEST_F(TestDesktopEntry, set) {
    DesktopEntry entry;
    entry.set("A/B", "C");

    std::stringstream out;
    out << entry;

    std::string expected = "[A]\nB=C";
    ASSERT_EQ(out.str(), expected);
}

TEST_F(TestDesktopEntry, edit) {
    DesktopEntry entry;

    std::stringstream in(exampleDesktopEntry);
    in >> entry;

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
    DesktopEntry entry;

    std::stringstream in(exampleDesktopEntry);
    in >> entry;

    ASSERT_TRUE(entry.exists("Desktop Action Gallery/Name"));
    ASSERT_FALSE(entry.exists("Desktop Action Gallery/Nam"));
}

TEST_F(TestDesktopEntry, removeGroup) {
    DesktopEntry entry;

    std::string entryStr = {"[G1]\nName=1\n[g2]\nName=2\n"};
    std::stringstream in(entryStr);
    in >> entry;

    ASSERT_TRUE(entry.exists("G1"));
    entry.remove("G1");
    ASSERT_FALSE(entry.exists("G1"));

    std::stringstream out;
    out << entry;

    ASSERT_EQ(out.str(), "[g2]\nName=2\n");
}

TEST_F(TestDesktopEntry, removeEntry) {
    DesktopEntry entry;

    std::string entryStr = {"[G1]\nName=1\nIcon=1\n[g2]\nName=2\n"};
    std::stringstream in(entryStr);
    in >> entry;

    ASSERT_TRUE(entry.exists("G1/Icon"));
    entry.remove("G1/Icon");
    ASSERT_FALSE(entry.exists("G1/Icon"));

    std::stringstream out;
    out << entry;

    ASSERT_EQ(out.str(), "[G1]\nName=1\n[g2]\nName=2\n");
}

TEST_F(TestDesktopEntry, arraySubscriptOperatorAccessGroup) {
    DesktopEntry entry;

    entry["Group"] = "Group";

    std::stringstream out;
    out << entry;

    ASSERT_EQ(out.str(), "[Group]\n");
}

TEST_F(TestDesktopEntry, arraySubscriptOperatorAccessEntry) {
    DesktopEntry entry;
    entry["Group/Key"] = "My App";

    ASSERT_EQ(static_cast<std::string>(entry["Group/Key"]), "My App");

    std::stringstream out;
    out << entry;

    ASSERT_EQ(out.str(), "[Group]\n"
                         "Key=My App");
}

TEST_F(TestDesktopEntry, copy) {
    DesktopEntry a;
    a["g/k"] = "v";

    // Assert that values are copied
    DesktopEntry b = a;
    ASSERT_EQ(static_cast<std::string>(b["g/k"]), "v");

    // Assert that b inner data pointers are different from the a ones
    b["g/k"] = "v1";
    ASSERT_EQ(static_cast<std::string>(a["g/k"]), "v");
    ASSERT_EQ(static_cast<std::string>(b["g/k"]), "v1");
}

TEST_F(TestDesktopEntry, move) {
    DesktopEntry a;
    a["g/k"] = "v";

    // Assert that values are copied
    DesktopEntry b = std::move(a);
    ASSERT_EQ(static_cast<std::string>(b["g/k"]), "v");
}
