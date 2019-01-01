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
    AST a = r.read(new std::stringstream(data));

    std::unique_ptr<std::stringstream> res(new std::stringstream());
    a.write(res.get());

    ASSERT_EQ(res->str(), data);
}

TEST(TestDesktopEntryReader, readBroken) {
    std::string data = {
        "# Test Destkop file\n"
        "[Desktop Entry]\n"
        "--Name=My App\n"
        "Name[es]=Mi App\n"
    };


    Reader r;
    ASSERT_THROW(r.read(new std::stringstream(data)), std::runtime_error);
}
