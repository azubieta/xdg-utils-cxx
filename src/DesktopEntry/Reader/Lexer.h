#pragma once

#include <memory>
#include <sstream>

namespace XdgUtils {
    namespace DesktopEntry {
        namespace Reader {
            class Lexer {
                std::istream &input;
                char c;
                unsigned long lineCont = 0;
                bool eol = false;   // Line increment flag
                bool eof = false;   // EOF flag
            public:
                explicit Lexer(std::istream& input);

                virtual ~Lexer();

                /**
                 * Read next char from the input
                 * @return true if the character was properly read, false otherwise
                 */
                bool consume();

                /**
                 * @return Last read character
                 */
                char top();

                bool isAlfaNumeric() const;

                bool isOpenSquareBracket() const;

                bool isCloseSquareBracket() const;

                bool isAssignment() const;

                bool isHash() const;

                bool isSpace() const;

                bool isEOL() const;

                bool isEOF() const;

                unsigned long line();

                bool isDash();
            };
        }

    }
}
