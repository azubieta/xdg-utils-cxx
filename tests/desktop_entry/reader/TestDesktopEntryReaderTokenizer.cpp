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
    const auto input = L"  [Desktop Entry]  \n";
    Tokenizer t(new std::wstringstream(input));
    std::vector<Token> tokens = t.tokenize();

    std::vector<Token> expectedTokens = {Token(L"  [Desktop Entry]  ", 0, L"Desktop Entry", GROUP_HEADER)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeBrokenGroupHeader) {
    const auto input = L"[Desktop[ Entry]\n";
    Tokenizer t(new std::wstringstream(input));
    std::vector<Token> tokens = t.tokenize();

    std::vector<Token> expectedTokens = {Token(L"[Desktop[ Entry]", 0, L"Unexpected char '[' at 8", UNKNOWN)};

    ASSERT_EQ(tokens, expectedTokens);
}

TEST(TestDesktopEntryReaderTokenizer, tokenizeEntry) {
    const auto input = L"Name[es_ES]=Super App\n";
    Tokenizer t(new std::wstringstream(input));
    std::vector<Token> tokens = t.tokenize();

    std::vector<Token> expectedTokens = {Token(L"Name", 0, L"Name", ENTRY_KEY),
                                         Token(L"[es_ES]", 0, L"es_ES", ENTRY_LOCALE),
                                         Token(L"Super App", 0, L"Super App", ENTRY_VALUE_STR)};

    ASSERT_EQ(tokens, expectedTokens);
}
