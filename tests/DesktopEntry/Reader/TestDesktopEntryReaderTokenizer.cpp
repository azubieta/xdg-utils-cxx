// system
#include <sstream>

// libraries
#include <gtest/gtest.h>

// local
#include <Reader/Token.h>
#include <Reader/Tokenizer.h>

using namespace XdgUtils::DesktopEntry::Reader;

TEST(TestDesktopEntryReaderTokenizer, tokenizeComments) {
    const auto input = "# Simple comment";
    std::stringstream inputStream(input);

    Tokenizer t(inputStream);
    auto tokens = t.consumeAll();

    std::vector<Token> expectedTokens = {Token("# Simple comment", 0, " Simple comment", COMMENT)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeBlankLine) {
    const auto input = "   ";
    std::stringstream inputStream(input);

    Tokenizer t(inputStream);
    auto tokens = t.consumeAll();

    std::vector<Token> expectedTokens = {Token("   ", 0, "   ", COMMENT)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeGroupHeader) {
    const auto input = "  [Desktop Entry]  ";
    std::stringstream inputStream(input);

    Tokenizer t(inputStream);
    auto tokens = t.consumeAll();

    std::vector<Token> expectedTokens = {Token("  [Desktop Entry]  ", 0, "Desktop Entry", GROUP_HEADER)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeBrokenGroupHeader) {
    const auto input = "[Desktop[ Entry]";
    std::stringstream inputStream(input);

    Tokenizer t(inputStream);
    auto tokens = t.consumeAll();

    std::vector<Token> expectedTokens = {Token("[Desktop[ Entry]", 0, "Unexpected char '[' at 8", UNKNOWN)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeEntry) {
    const auto input = "Name=Super App";
    std::stringstream inputStream(input);

    Tokenizer t(inputStream);
    auto tokens = t.consumeAll();

    std::vector<Token> expectedTokens = {Token("Name", 0, "Name", ENTRY_KEY),
                                         Token("=Super App", 0, "Super App", ENTRY_VALUE)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeLocalizedEntry) {
    const auto input = "Name[es_ES] = Super App";
    std::stringstream inputStream(input);

    Tokenizer t(inputStream);
    auto tokens = t.consumeAll();
    std::vector<Token> expectedTokens = {Token("Name", 0, "Name", ENTRY_KEY),
                                         Token("[es_ES] ", 0, "es_ES", ENTRY_LOCALE),
                                         Token("= Super App", 0, " Super App", ENTRY_VALUE)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeCompleteDesktopEntry) {
    const auto input = "[Desktop Entry]\n"
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
                       "Icon=fooview-new";
    std::stringstream inputStream(input);

    Tokenizer t(inputStream);
    auto tokens = t.consumeAll();

    std::vector<Token> expectedTokens = {
        Token("[Desktop Entry]", 0, "Desktop Entry", GROUP_HEADER),
        Token("Version", 1, "Version", ENTRY_KEY), Token("=1.0", 1, "1.0", ENTRY_VALUE),
        Token("Type", 2, "Type", ENTRY_KEY), Token("=Application", 2, "Application", ENTRY_VALUE),
        Token("Name", 3, "Name", ENTRY_KEY), Token("=Foo Viewer", 3, "Foo Viewer", ENTRY_VALUE),
        Token("Comment", 4, "Comment", ENTRY_KEY),
        Token("=The best viewer for Foo objects available!", 4, "The best viewer for Foo objects available!",
              ENTRY_VALUE),
        Token("TryExec", 5, "TryExec", ENTRY_KEY), Token("=fooview", 5, "fooview", ENTRY_VALUE),
        Token("Exec", 6, "Exec", ENTRY_KEY), Token("=fooview %F", 6, "fooview %F", ENTRY_VALUE),
        Token("Icon", 7, "Icon", ENTRY_KEY), Token("=fooview", 7, "fooview", ENTRY_VALUE),
        Token("MimeType", 8, "MimeType", ENTRY_KEY), Token("=image/x-foo;", 8, "image/x-foo;", ENTRY_VALUE),
        Token("Actions", 9, "Actions", ENTRY_KEY), Token("=Gallery;Create;", 9, "Gallery;Create;", ENTRY_VALUE),
        Token("", 10, "", COMMENT),
        Token("[Desktop Action Gallery]", 11, "Desktop Action Gallery", GROUP_HEADER),
        Token("Exec", 12, "Exec", ENTRY_KEY), Token("=fooview --gallery", 12, "fooview --gallery", ENTRY_VALUE),
        Token("Name", 13, "Name", ENTRY_KEY), Token("=Browse Gallery", 13, "Browse Gallery", ENTRY_VALUE),
        Token("", 14, "", COMMENT),
        Token("[Desktop Action Create]", 15, "Desktop Action Create", GROUP_HEADER),
        Token("Exec", 16, "Exec", ENTRY_KEY),
        Token("=fooview --create-new", 16, "fooview --create-new", ENTRY_VALUE),
        Token("Name", 17, "Name", ENTRY_KEY), Token("=Create a new Foo!", 17, "Create a new Foo!", ENTRY_VALUE),
        Token("Icon", 18, "Icon", ENTRY_KEY), Token("=fooview-new", 18, "fooview-new", ENTRY_VALUE)
    };

    ASSERT_EQ(tokens, expectedTokens);
}
