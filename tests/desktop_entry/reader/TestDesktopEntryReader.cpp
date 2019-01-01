#include <gtest/gtest.h>

#include <reader/Reader.h>
#include <AST/AST.h>

using namespace xdg_utils::desktop_entry::reader;
using namespace xdg_utils::desktop_entry::ast;

TEST(TestDesktopEntryReader, readWrite) {
    std::string data = {
        "# Test Destkop file\n"
        "[Desktop Entry]\n"
        "Name=My App\n"
        "Name[es]=Mi App\n"
    };


    Reader r;
    AST a = r.read(new std::stringstream(data));

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
    ASSERT_THROW(r.read(new std::stringstream(data)), std::runtime_error);
}
