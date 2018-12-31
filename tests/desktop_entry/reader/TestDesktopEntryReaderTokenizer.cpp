#include <gtest/gtest.h>

#include <Token.h>
#include <Tokenizer.h>

using namespace xdg_utils::desktop_entry::reader;

TEST(TestDesktopEntryReaderTokenizer, tokenizeComments) {
    const auto input = L"# Simple comment";

    Tokenizer t(new std::wstringstream(input));
    std::vector<Token> tokens = t.tokenize();

    std::vector<Token> expectedTokens = {Token(L"# Simple comment", 0, L" Simple comment", COMMENT)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeBlankLine) {
    const auto input = L"   ";
    Tokenizer t(new std::wstringstream(input));
    std::vector<Token> tokens = t.tokenize();

    std::vector<Token> expectedTokens = {Token(L"   ", 0, L"   ", COMMENT)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeGroupHeader) {
    const auto input = L"  [Desktop Entry]  ";
    Tokenizer t(new std::wstringstream(input));
    std::vector<Token> tokens = t.tokenize();

    std::vector<Token> expectedTokens = {Token(L"  [Desktop Entry]  ", 0, L"Desktop Entry", GROUP_HEADER)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeBrokenGroupHeader) {
    const auto input = L"[Desktop[ Entry]";
    Tokenizer t(new std::wstringstream(input));
    std::vector<Token> tokens = t.tokenize();

    std::vector<Token> expectedTokens = {Token(L"[Desktop[ Entry]", 0, L"Unexpected char '[' at 8", UNKNOWN)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeEntry) {
    const auto input = L"Name=Super App";
    Tokenizer t(new std::wstringstream(input));
    std::vector<Token> tokens = t.tokenize();

    std::vector<Token> expectedTokens = {Token(L"Name", 0, L"Name", ENTRY_KEY),
                                         Token(L"=Super App", 0, L"Super App", ENTRY_VALUE)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeLocalizedEntry) {
    const auto input = L"Name[es_ES] = Super App";
    Tokenizer t(new std::wstringstream(input));
    std::vector<Token> tokens = t.tokenize();

    std::vector<Token> expectedTokens = {Token(L"Name", 0, L"Name", ENTRY_KEY),
                                         Token(L"[es_ES] ", 0, L"es_ES", ENTRY_LOCALE),
                                         Token(L"= Super App", 0, L" Super App", ENTRY_VALUE)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeCompleteDesktopEntry) {
    const auto input = L"[Desktop Entry]\n"
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
    Tokenizer t(new std::wstringstream(input));
    std::vector<Token> tokens = t.tokenize();

    std::vector<Token> expectedTokens = {
        Token(L"[Desktop Entry]", 0, L"Desktop Entry", GROUP_HEADER),
        Token(L"Version", 1, L"Version", ENTRY_KEY), Token(L"=1.0", 1, L"1.0", ENTRY_VALUE),
        Token(L"Type", 2, L"Type", ENTRY_KEY), Token(L"=Application", 2, L"Application", ENTRY_VALUE),
        Token(L"Name", 3, L"Name", ENTRY_KEY), Token(L"=Foo Viewer", 3, L"Foo Viewer", ENTRY_VALUE),
        Token(L"Comment", 4, L"Comment", ENTRY_KEY),
        Token(L"=The best viewer for Foo objects available!", 4, L"The best viewer for Foo objects available!",
              ENTRY_VALUE),
        Token(L"TryExec", 5, L"TryExec", ENTRY_KEY), Token(L"=fooview", 5, L"fooview", ENTRY_VALUE),
        Token(L"Exec", 6, L"Exec", ENTRY_KEY), Token(L"=fooview %F", 6, L"fooview %F", ENTRY_VALUE),
        Token(L"Icon", 7, L"Icon", ENTRY_KEY), Token(L"=fooview", 7, L"fooview", ENTRY_VALUE),
        Token(L"MimeType", 8, L"MimeType", ENTRY_KEY), Token(L"=image/x-foo;", 8, L"image/x-foo;", ENTRY_VALUE),
        Token(L"Actions", 9, L"Actions", ENTRY_KEY), Token(L"=Gallery;Create;", 9, L"Gallery;Create;", ENTRY_VALUE),
        Token(L"", 10, L"", COMMENT),
        Token(L"[Desktop Action Gallery]", 11, L"Desktop Action Gallery", GROUP_HEADER),
        Token(L"Exec", 12, L"Exec", ENTRY_KEY), Token(L"=fooview --gallery", 12, L"fooview --gallery", ENTRY_VALUE),
        Token(L"Name", 13, L"Name", ENTRY_KEY), Token(L"=Browse Gallery", 13, L"Browse Gallery", ENTRY_VALUE),
        Token(L"", 14, L"", COMMENT),
        Token(L"[Desktop Action Create]", 15, L"Desktop Action Create", GROUP_HEADER),
        Token(L"Exec", 16, L"Exec", ENTRY_KEY),
        Token(L"=fooview --create-new", 16, L"fooview --create-new", ENTRY_VALUE),
        Token(L"Name", 17, L"Name", ENTRY_KEY), Token(L"=Create a new Foo!", 17, L"Create a new Foo!", ENTRY_VALUE),
        Token(L"Icon", 18, L"Icon", ENTRY_KEY), Token(L"=fooview-new", 18, L"fooview-new", ENTRY_VALUE)
    };

    ASSERT_EQ(tokens, expectedTokens);
}
