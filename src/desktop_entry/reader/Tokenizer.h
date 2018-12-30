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
                 * @param raw
                 * @return
                 */
                std::vector<Token> tokenizeGroupHeaderLine(std::wstringstream& raw);

                /**
                 * Consume all characters until the end of the line
                 * @param data stream where the consumed characters will be placed
                 */
                void consumeLine(std::wstringstream& data);
            };
        }
    }
}
