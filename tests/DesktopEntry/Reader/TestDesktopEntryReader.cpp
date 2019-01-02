#include <gtest/gtest.h>

#include <Reader/Reader.h>
#include <AST/AST.h>

using namespace XdgUtils::DesktopEntry::Reader;
using namespace XdgUtils::DesktopEntry::AST;

TEST(TestDesktopEntryReader, readWrite) {
    std::string data = {
        "# Test Destkop file\n"
        "[Desktop Entry]\n"
        "Name=My App\n"
        "Name[es]=Mi App\n"
    };


    Reader r;
    std::stringstream in(data);
    AST a = r.read(in);

    std::stringstream res;
    a.write(res);

    ASSERT_EQ(res.str(), data);
}

TEST(TestDesktopEntryReader, readBroken) {
    std::string data = {
        "# Test Destkop file\n"
        "[Desktop Entry]\n"
        "--Name=My App\n"
        "Name[es]=Mi App\n"
    };


    Reader r;
    std::stringstream in(data);
    ASSERT_THROW(r.read(in), std::runtime_error);
}
