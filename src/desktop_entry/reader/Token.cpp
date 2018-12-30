#include <locale>
#include <codecvt>

#include "Token.h"

namespace xdg_utils {
    namespace desktop_entry {
        namespace reader {
            Token::Token(const std::wstring& raw, unsigned long line, const std::wstring& value,
                         xdg_utils::desktop_entry::reader::TokenType type) : raw(raw), line(line), value(value),
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
                // small type conversion to make it work
                std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
                std::string rawStr8 = cv.to_bytes(token.raw);
                std::string valueStr8 = cv.to_bytes(token.value);

                os << "{ raw: \"" << rawStr8 << "\", ";
                os << "line: " << token.line << ", ";
                os << "value: \"" << valueStr8 << "\", ";
                os << "type: " << token.type << " }";
                return os;
            }

            std::ostream& operator<<(std::ostream& os, const TokenType& tokenType) {
                const char* s = 0;
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
