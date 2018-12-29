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

                do {
                    tokens.push_back(next());
                } while (!lexer.isEOF());

                return tokens;
            }

            Token Tokenizer::next() {
                std::wstringstream raw;

                // consume spaces
                while (lexer.consume() && lexer.isSpace() && !lexer.isEOL())
                    raw << lexer.top();

                // pure blank line
                if (lexer.isEOL() || lexer.isEOF())
                    return Token(raw.str(), lexer.line(), raw.str(), COMMENT);

                // comment line
                if (lexer.isHash()) {
                    raw << lexer.top();

                    std::wstringstream value;
                    // consume the rest of the line
                    while (lexer.consume() && !lexer.isEOL()) {
                        raw << lexer.top();
                        value << lexer.top();
                    }

                    return Token(raw.str(), lexer.line(), value.str(), COMMENT);
                }
            }
        }
    }
}
