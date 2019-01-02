#include <vector>

#include "Tokenizer.h"
#include "Token.h"
#include "Errors.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace Reader {
            Tokenizer::Tokenizer(std::istream& input) : lexer(input) {}

            Tokenizer::~Tokenizer() = default;


            Token Tokenizer::get() const {
                if (buffer.begin() != buffer.end())
                    return *buffer.begin();
                else
                    throw NoTokensLeft("There are no tokens left or Tokenizer::consume wasn't called.");
            }

            bool Tokenizer::consume() {
                if (completed)
                    return false;

                // remove buffer top
                if (!buffer.empty())
                    buffer.erase(buffer.begin());

                if (buffer.empty()) {
                    if (lexer.isEOF())
                        completed = true;
                    else
                        buffer = tokenizeLine();
                }

                return !completed;
            }

            bool Tokenizer::isCompleted() const {
                return completed;
            }

            std::vector<Token> Tokenizer::tokenizeLine() {
                std::vector<Token> lineTokens;
                std::stringstream raw;

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
                if (lexer.isAlfaNumeric()) {
                    lineTokens.push_back(tokenizeEntryKey(raw));

                    // after an entry key is expected a '[', '=' or a set of whitespaces and a '
                    if (lexer.isOpenSquareBracket()) {
                        auto locale = tokenizeEntryLocale(raw);
                        lineTokens.push_back(locale);

                        if (locale.type == UNKNOWN)
                            return lineTokens;
                    }

                    if (lexer.isAssignment()) {
                        auto value = tokenizeEntryValue(raw);
                        lineTokens.push_back(value);
                    }

                    return lineTokens;

                }

                // if this section is reached the input doesn't conform with any known line type therefore we will
                // consume the whole line and assume it's an UNKNOWN token
                lineTokens.emplace_back(tokenizeUnknownLine(raw));
                return lineTokens;
            }

            Token Tokenizer::tokenizeEntryKey(std::stringstream& raw) {
                std::stringstream value;
                do value << lexer.top();
                while (lexer.consume() && (lexer.isAlfaNumeric() || lexer.isDash()) && !lexer.isEOL());

                raw << value.str();

                while (lexer.isSpace()) {
                    raw << lexer.top();
                    lexer.consume();
                }

                return Token(raw.str(), lexer.line(), value.str(), ENTRY_KEY);
            }

            Token Tokenizer::tokenizeEntryLocale(std::stringstream& raw) {
                std::stringstream rawSection;
                std::stringstream value;

                rawSection << lexer.top();

                while (lexer.consume() && !lexer.isEOL() && !lexer.isSpace() &&
                       !lexer.isCloseSquareBracket() && !lexer.isOpenSquareBracket()) {
                    rawSection << lexer.top();
                    value << lexer.top();
                }


                if (lexer.isCloseSquareBracket()) {
                    // consume ']' with trailing spaces
                    do rawSection << lexer.top(); while (lexer.consume() && lexer.isSpace());

                    raw << rawSection.str();
                    return Token(rawSection.str(), lexer.line(), value.str(), ENTRY_LOCALE);
                }

                raw << rawSection.str();
                return tokenizeUnknownLine(raw);
            }

            Token Tokenizer::tokenizeEntryValue(std::stringstream& raw) {
                // consume entry value
                std::stringstream value;
                std::stringstream sectionRaw;

                // save '=' raw
                sectionRaw << lexer.top();
                while (lexer.consume() && !lexer.isEOL())
                    value << lexer.top();

                sectionRaw << value.str();
                if (lexer.isEOL() || lexer.isEOF())
                    return Token(sectionRaw.str(), lexer.line(), value.str(), ENTRY_VALUE);


                raw << sectionRaw.str();
                return tokenizeUnknownLine(raw);
            }

            Token Tokenizer::tokenizeCommentLine(std::stringstream& raw) {
                raw << lexer.top();

                std::stringstream value;
                // consume the rest of the line
                while (lexer.consume() && !lexer.isEOL()) {
                    raw << lexer.top();
                    value << lexer.top();
                }

                return Token(raw.str(), lexer.line(), value.str(), COMMENT);
            }

            std::vector<Token> Tokenizer::tokenizeGroupHeaderLine(std::stringstream& raw) {
                std::vector<Token> tokens;

                // save char '['
                raw << lexer.top();

                std::stringstream value;
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

                    if (lexer.isEOL() || lexer.isEOF()) {
                        tokens.emplace_back(Token(raw.str(), lexer.line(), value.str(), GROUP_HEADER));
                        return tokens;
                    }
                }

                // if this section is reached the input doesn't conform with the group header spec therefore the whole
                // line must be consumed and it must be treated as an error
                tokens.emplace_back(tokenizeUnknownLine(raw));
                return tokens;
            }

            Token Tokenizer::tokenizeUnknownLine(std::stringstream& raw) {
                std::stringstream errorMsg;
                errorMsg << "Unexpected char \'" << lexer.top() << "\' at "
                         << std::to_string(raw.str().size());

                consumeLine(raw);
                return Token(raw.str(), lexer.line(), errorMsg.str(), UNKNOWN);
            }

            void Tokenizer::consumeLine(std::stringstream& data) {
                data << lexer.top();
                while (lexer.consume() && !lexer.isEOL())
                    data << lexer.top();
            }

            std::vector<Token> Tokenizer::consumeAll() {
                std::vector<Token> tokens;
                while (consume())
                    tokens.emplace_back(get());

                return tokens;
            }
        }
    }
}
