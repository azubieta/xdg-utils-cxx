#pragma once

#include <memory>

#include "Lexer.h"
#include "Token.h"

namespace xdg_utils {
    namespace desktop_entry {
        namespace reader {
            class Tokenizer {
                Lexer lexer;
            public:
                explicit Tokenizer(std::wstringstream* input);

                virtual ~Tokenizer();

                /**
                 * Map the file contents to tokens in order to ease manipulation
                 * @return list of tokens identified at in the file
                 */
                std::vector<Token> tokenize();

                /**
                 * Attempts to create tokens from the current line following the rules:
                 * L -> C (comment line)
                 * L -> DH (Desktop Header)
                 * L -> E (key-locale-value entry)
                 *
                 * @return tokens found at the given line
                 */
                std::vector<Token> tokenizeLine();

                /**
                 * Attempts to read the current line as a COMMENT token described as:
                 * C -> '#' (all ASCII char)* EOL
                 *
                 * @param raw
                 * @return COMMENT token if all goes ok or UNKNOWN token if something unexpected happens
                 */
                Token tokenizeCommentLine(std::wstringstream& raw);

                /**
                 * Attempts to read the current line as a GROUP_HEADER token described as:
                 * GH -> [ (all ASCII chars but '[')+ ](spaces)*EOL
                 *
                 * @param raw input line
                 * @return GROUP_HEADER token if all goes ok UNKNOWN token in case of error
                 */
                std::vector<Token> tokenizeGroupHeaderLine(std::wstringstream& raw);

                /**
                 * Attempt to read a ENTRY_KEY token described as
                 * (any alphanumeric char)+
                 * @param raw input line
                 * @return ENTRY_KEY token if all goes ok UNKNOWN token in case of error
                 */
                Token tokenizeEntryKey(std::wstringstream& raw);

                /**
                 * Attempt to read a ENTRY_LOCALE token described as:
                 * [ (any ASCII char but ']' and '[')+ ] (space)+
                 * @param raw input line
                 * @return ENTRY_LOCALE token if all goes ok UNKNOWN token in case of error
                 */
                Token tokenizeEntryLocale(std::wstringstream& raw);

                /**
                 * Attempt to read a ENTRY_VALUE token described as:
                 * = (any UTF-8 char) EOL
                 * @param raw input line
                 * @return ENTRY_VALUE token if all goes ok UNKNOWN token in case of error
                 */
                Token tokenizeEntryValue(std::wstringstream& raw);

                /**
                 * Assume the current char as unexpected, read what remains from the line and create an UNKNOWN
                 * token. The token value will contain an error message string.
                 *
                 * @param raw input line
                 * @return UNKNOWN token
                 */
                Token tokenizeUnknownLine(std::wstringstream& raw);

                /**
                 * Consume all characters until the end of the line
                 * @param data stream where the consumed characters will be placed
                 */
                void consumeLine(std::wstringstream& data);
            };
        }
    }
}
