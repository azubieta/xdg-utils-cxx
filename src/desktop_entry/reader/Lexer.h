#pragma once

#include <memory>
#include <sstream>

namespace xdg_utils {
    namespace desktop_entry {
        namespace reader {
            class Lexer {
                std::unique_ptr<std::wstringstream> input;
                wchar_t c;
                unsigned long lineCont = 0;
                bool eol = false;   // Line increment flag
                bool eof = false;   // EOF flag
            public:
                explicit Lexer(std::wstringstream* input);

                virtual ~Lexer();

                /**
                 * Read next char from the input
                 * @return true if the character was properly read, false otherwise
                 */
                bool consume();

                /**
                 * @return Last read character
                 */
                wchar_t top();

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
