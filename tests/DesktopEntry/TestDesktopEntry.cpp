#include <gtest/gtest.h>

#include <DesktopEntry.h>

using namespace XdgUtils;

class TestDesktopEntry : public ::testing::Test {
protected:


    std::string exampleDesktopEntry = "[Desktop Entry]\n"
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

    std::unique_ptr<std::stringstream> in(new std::stringstream(exampleDesktopEntry));
    entry.read(in.get());

    auto out = new std::stringstream();
    entry.write(out);

    ASSERT_EQ(in->str(), out->str());
}

TEST_F(TestDesktopEntry, listGroups) {
    DesktopEntry::DesktopEntry entry;

    auto in = new std::stringstream(exampleDesktopEntry);
    entry.read(in);

    std::vector<std::string> expected = {"Desktop Entry", "Desktop Action Gallery", "Desktop Action Create"};
    std::vector<std::string> result = entry.listGroups();

    ASSERT_EQ(result, expected);
}

TEST_F(TestDesktopEntry, listGroupKeys) {
    DesktopEntry::DesktopEntry entry;

    auto in = new std::stringstream(exampleDesktopEntry);
    entry.read(in);

    std::vector<std::string> expected = {"Exec", "Name"};
    std::vector<std::string> result = entry.listGroupKeys("Desktop Action Gallery");

    ASSERT_EQ(result, expected);
}
