#include <locale>

#include "Token.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace Reader {
            Token::Token(const std::string& raw, unsigned long line, const std::string& value,
                         XdgUtils::DesktopEntry::Reader::TokenType type) : raw(raw), line(line), value(value),
                                                                             type(type) {}

            bool Token::operator==(const Token& rhs) const {
                return raw == rhs.raw &&
                       line == rhs.line &&
                       value == rhs.value &&
                       type == rhs.type;
            }

            bool Token::operator!=(const Token& rhs) const {
                return !(rhs == *this);
            }

            std::ostream& operator<<(std::ostream& os, const Token& token) {
                os << "{ raw: \"" << token.raw << "\", ";
                os << "line: " << token.line << ", ";
                os << "value: \"" << token.value << "\", ";
                os << "type: " << token.type << " }";
                return os;
            }

            std::ostream& operator<<(std::ostream& os, const TokenType& tokenType) {
                const char* s = nullptr;
#define PROCESS_VAL(p) case(p): s = #p; break;
                switch (tokenType) {
                    PROCESS_VAL(COMMENT);
                    PROCESS_VAL(GROUP_HEADER);
                    PROCESS_VAL(ENTRY_KEY);
                    PROCESS_VAL(ENTRY_LOCALE);
                    PROCESS_VAL(ENTRY_VALUE);
                    PROCESS_VAL(UNKNOWN);
                }
#undef PROCESS_VAL

                return os << s;
            }
        }
    }
}
