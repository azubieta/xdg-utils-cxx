#include <sstream>

#include "Lexer.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace Reader {
            Lexer::Lexer(std::istream& input) : input(input), c('\0') {}

            Lexer::~Lexer() = default;

            bool Lexer::consume() {
                if (input.get(c)) {

                    if (eol) {
                        lineCont++;
                        eol = false;
                    }

                    // Increment line count in the next iteration
                    if (isEOL())
                        eol = true;

                    return true;
                } else {
                    c = L'\0';
                    eof = true;
                    return false;
                }

            }

            char Lexer::top() {
                return c;
            }

            bool Lexer::isAlfaNumeric() const { return isalnum(c); }

            bool Lexer::isOpenSquareBracket() const { return c == L'['; }

            bool Lexer::isCloseSquareBracket() const { return c == L']'; }

            bool Lexer::isHash() const { return c == L'#'; }

            bool Lexer::isSpace() const { return isblank(c); }

            bool Lexer::isEOL() const { return c == L'\n'; }

            bool Lexer::isEOF() const { return eof; }

            bool Lexer::isAssignment() const { return c == L'='; }

            unsigned long Lexer::line() { return lineCont; }

            bool Lexer::isDash() { return c == L'-'; }
        }
    }
}
