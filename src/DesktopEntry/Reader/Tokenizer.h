#pragma once

#include <memory>

#include "Lexer.h"
#include "Token.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace Reader {
            class Tokenizer {
                Lexer lexer;
            public:
                explicit Tokenizer(std::istream& input);

                virtual ~Tokenizer();

                /**
                 * Returns the current token
                 * @return
                 */
                Token get() const;

                /**
                 * Move to the next token
                 * @return true if a new token is available, otherwise false;
                 */
                bool consume();

                bool isCompleted() const;

                std::vector<Token> consumeAll();

            private:
                std::vector<Token> buffer;
                bool completed = false;

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
                Token tokenizeCommentLine(std::stringstream& raw);

                /**
                 * Attempts to read the current line as a GROUP_HEADER token described as:
                 * GH -> [ (all ASCII chars but '[')+ ](spaces)*EOL
                 *
                 * @param raw input line
                 * @return GROUP_HEADER token if all goes ok UNKNOWN token in case of error
                 */
                std::vector<Token> tokenizeGroupHeaderLine(std::stringstream& raw);

                /**
                 * Attempt to read a ENTRY_KEY token described as
                 * (any alphanumeric char)+
                 * @param raw input line
                 * @return ENTRY_KEY token if all goes ok UNKNOWN token in case of error
                 */
                Token tokenizeEntryKey(std::stringstream& raw);

                /**
                 * Attempt to read a ENTRY_LOCALE token described as:
                 * [ (any ASCII char but ']' and '[')+ ] (space)+
                 * @param raw input line
                 * @return ENTRY_LOCALE token if all goes ok UNKNOWN token in case of error
                 */
                Token tokenizeEntryLocale(std::stringstream& raw);

                /**
                 * Attempt to read a ENTRY_VALUE token described as:
                 * = (any UTF-8 char) EOL
                 * @param raw input line
                 * @return ENTRY_VALUE token if all goes ok UNKNOWN token in case of error
                 */
                Token tokenizeEntryValue(std::stringstream& raw);

                /**
                 * Assume the current char as unexpected, read what remains from the line and create an UNKNOWN
                 * token. The token value will contain an error message string.
                 *
                 * @param raw input line
                 * @return UNKNOWN token
                 */
                Token tokenizeUnknownLine(std::stringstream& raw);

                /**
                 * Consume all characters until the end of the line
                 * @param data stream where the consumed characters will be placed
                 */
                void consumeLine(std::stringstream& data);
            };
        }
    }
}
