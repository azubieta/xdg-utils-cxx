#pragma once

#include <string>
#include <ostream>

namespace xdg_utils {
    namespace desktop_entry {
        namespace reader {
            enum TokenType {
                COMMENT,
                GROUP_HEADER,
                ENTRY_KEY,
                ENTRY_LOCALE,
                ENTRY_VALUE,
                UNKNOWN
            };

            struct Token {
                std::wstring raw;
                unsigned long line;
                std::wstring value;
                TokenType type;

                Token(const std::wstring& raw, unsigned long line, const std::wstring& value, TokenType type);

                bool operator==(const Token& rhs) const;

                bool operator!=(const Token& rhs) const;

                friend std::ostream& operator<<(std::ostream& os, const Token& token);
            };


            /**
             * Print TokenTypes names
             */
            std::ostream& operator<<(std::ostream& os, const TokenType& tokenType);
        }
    }
}
