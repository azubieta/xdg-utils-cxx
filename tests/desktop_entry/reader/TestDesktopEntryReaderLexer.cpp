#include <gtest/gtest.h>

#include <Lexer.h>

using namespace xdg_utils::desktop_entry::reader;

TEST(TestDesktopEntryReaderLexer, consume) {
    const auto str = L"[Desktop Entry]\n";
    Lexer l(new std::wstringstream(str));

    int i = 0;
    while (l.consume()) {
        ASSERT_EQ(l.top(), str[i]);
        i++;
    }
}

TEST(TestDesktopEntryReaderLexer, classify) {
    const auto str = L"#"   // Comment begin char
                     " "    // white space
                     "\t"   // white space
                     "\n"   // EOL
                     "["    // Group Open
                     "]"    // Group Close
                     "="    // Assignment
                     "R";   // Regular char

    Lexer l(new std::wstringstream(str));

    l.consume();
    ASSERT_TRUE(l.isHash());
    ASSERT_FALSE(l.isAlfaNumeric());

    l.consume();
    ASSERT_TRUE(l.isSpace());

    l.consume();
    ASSERT_TRUE(l.isSpace());

    l.consume();
    ASSERT_TRUE(l.isEOL());

    l.consume();
    ASSERT_TRUE(l.isOpenSquareBracket());

    l.consume();
    ASSERT_TRUE(l.isCloseSquareBracket());

    l.consume();
    ASSERT_TRUE(l.isAssignment());

    l.consume();
    ASSERT_TRUE(l.isAlfaNumeric());
}

TEST(TestDesktopEntryReaderLexer, lineCount) {
    const auto str = L"\n\na";
    Lexer l(new std::wstringstream(str));

    int i = 0;
    while (l.consume()) {
        ASSERT_EQ(l.line(), i);
        i++;
    }
}
