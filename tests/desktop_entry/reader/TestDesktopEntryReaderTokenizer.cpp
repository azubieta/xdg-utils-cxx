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
