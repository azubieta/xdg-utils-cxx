#include <vector>

#include "Tokenizer.h"
#include "Token.h"

namespace xdg_utils {
    namespace desktop_entry {
        namespace reader {
            Tokenizer::Tokenizer(std::wstringstream* input) : lexer(input) {}

            Tokenizer::~Tokenizer() = default;

            std::vector<Token> Tokenizer::tokenize() {
                std::vector<Token> tokens;

                while (!lexer.isEOF()) {
                    auto lineTokens = tokenizeLine();
                    tokens.reserve(tokens.size() + lineTokens.size());
                    tokens.insert(tokens.end(), lineTokens.begin(), lineTokens.end());
                }


                return tokens;
            }

            std::vector<Token> Tokenizer::tokenizeLine() {
                std::vector<Token> lineTokens;
                std::wstringstream raw;

                // consume spaces
                while (lexer.consume() && lexer.isSpace() && !lexer.isEOL())
                    raw << lexer.top();

                // Comment Line
                if (lexer.isHash()) {
                    lineTokens.push_back(tokenizeCommentLine(raw));
                    return lineTokens;
                }

                // pure blank line also a Comment Line
                if (lexer.isEOL() || lexer.isEOF()) {
                    lineTokens.emplace_back(Token(raw.str(), lexer.line(), raw.str(), COMMENT));
                    return lineTokens;
                }

                // Group Header
                if (lexer.isOpenSquareBracket())
                    return tokenizeGroupHeaderLine(raw);

                // Entry Line
                if (lexer.isAlfaNumeric()) {}

                // if this section is reached the input doesn't conform with any known line type therefore we will
                // consume the whole line and assume it's an UNKNOWN token
                lineTokens.emplace_back(tokenizeUnknownLine(raw));
                return lineTokens;
            }

            Token Tokenizer::tokenizeCommentLine(std::wstringstream& raw) {
                raw << lexer.top();

                std::wstringstream value;
                // consume the rest of the line
                while (lexer.consume() && !lexer.isEOL()) {
                    raw << lexer.top();
                    value << lexer.top();
                }

                return Token(raw.str(), lexer.line(), value.str(), COMMENT);
            }

            std::vector<Token> Tokenizer::tokenizeGroupHeaderLine(std::wstringstream& raw) {
                std::vector<Token> tokens;

                // save char '['
                raw << lexer.top();

                std::wstringstream value;
                // consume until a ']' is found
                while (lexer.consume() && !lexer.isEOL() &&
                       !lexer.isCloseSquareBracket() && !lexer.isOpenSquareBracket()) {
                    raw << lexer.top();
                    value << lexer.top();
                }

                if (lexer.isCloseSquareBracket()) {
                    raw << lexer.top();
                    // consume trailing spaces
                    while (lexer.consume() && lexer.isSpace() && !lexer.isEOL())
                        raw << lexer.top();

                    if (lexer.isEOL()) {
                        // consume the EOL char
                        lexer.consume();

                        tokens.emplace_back(Token(raw.str(), lexer.line(), value.str(), GROUP_HEADER));
                        return tokens;
                    }
                }

                // if this section is reached the input doesn't conform with the group header spec therefore the whole
                // line must be consumed and it must be treated as an error
                tokens.emplace_back(tokenizeUnknownLine(raw));
                return tokens;
            }

            Token Tokenizer::tokenizeUnknownLine(std::wstringstream& raw) {
                std::wstringstream errorMsg;
                errorMsg << L"Unexpected char \'" << lexer.top() << L"\' at "
                         << std::to_wstring(raw.str().size());

                consumeLine(raw);
                return Token(raw.str(), lexer.line(), errorMsg.str(), UNKNOWN);
            }

            void Tokenizer::consumeLine(std::wstringstream& data) {
                data << lexer.top();
                while (lexer.consume() && !lexer.isEOL())
                    data << lexer.top();

                // Also consume the EOL char
                if (lexer.isEOL())
                    lexer.consume();
            }
        }
    }
}
