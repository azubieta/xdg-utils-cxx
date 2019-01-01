#pragma once

#include <string>
#include <ostream>

namespace XdgUtils {
    namespace DesktopEntry {
        namespace Reader {
            enum TokenType {
                COMMENT,
                GROUP_HEADER,
                ENTRY_KEY,
                ENTRY_LOCALE,
                ENTRY_VALUE,
                UNKNOWN
            };

            struct Token {
                std::string raw;
                unsigned long line;
                std::string value;
                TokenType type;

                Token(const std::string& raw, unsigned long line, const std::string& value, TokenType type);

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
