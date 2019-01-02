#include <gtest/gtest.h>

#include <Reader/Lexer.h>

using namespace XdgUtils::DesktopEntry::Reader;

TEST(TestDesktopEntryReaderLexer, consume) {
    const auto str = "[Desktop Entry]\n";
    std::stringstream in(str);
    Lexer l(in);

    int i = 0;
    while (l.consume()) {
        ASSERT_EQ(l.top(), str[i]);
        i++;
    }
}

TEST(TestDesktopEntryReaderLexer, classify) {
    const auto str = "#"   // Comment begin char
                     " "    // white space
                     "\t"   // white space
                     "\n"   // EOL
                     "["    // Group Open
                     "]"    // Group Close
                     "="    // Assignment
                     "R";   // Regular char

    std::stringstream strStream(str);
    Lexer l(strStream);

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
    const auto str = "\n\na";
    std::stringstream strStream(str);
    Lexer l(strStream);

    int i = 0;
    while (l.consume()) {
        ASSERT_EQ(l.line(), i);
        i++;
    }
}
