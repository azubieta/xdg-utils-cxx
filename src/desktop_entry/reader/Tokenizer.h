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

                std::vector<Token> tokenize();

                Token next();
            };
        }
    }
}
