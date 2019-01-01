// system
#include <string>
#include <AST/Comment.h>
#include <AST/Group.h>
#include <AST/Entry.h>

// local
#include "Reader.h"
#include "Tokenizer.h"
#include "Errors.h"

using namespace xdg_utils::desktop_entry::ast;

namespace xdg_utils {
    namespace desktop_entry {
        namespace reader {
            AST Reader::read(std::istream* input) {
                Tokenizer tokenizer(input);
                xdg_utils::desktop_entry::ast::AST ast;

                std::vector<std::shared_ptr<Node>> entries;
                while (tokenizer.consume() && tokenizer.get().type != TokenType::UNKNOWN) {
                    if (tokenizer.get().type == TokenType::COMMENT)
                        entries.emplace_back(new Comment(tokenizer.get().raw, tokenizer.get().value));

                    if (tokenizer.get().type == TokenType::GROUP_HEADER)
                        entries.emplace_back(readGroup(tokenizer));
                }

                if (!tokenizer.isCompleted())
                    throw MalformedEntry(tokenizer.get().value);

                ast.setEntries(entries);
                return ast;
            }

            xdg_utils::desktop_entry::ast::Group* Reader::readGroup(Tokenizer& tokenizer) {
                auto g = new Group(tokenizer.get().raw, tokenizer.get().value);

                std::vector<std::shared_ptr<Node>> entries;
                while (tokenizer.consume() &&
                       (tokenizer.get().type == TokenType::COMMENT ||
                        tokenizer.get().type == TokenType::ENTRY_KEY)) {

                    if (tokenizer.get().type == TokenType::ENTRY_KEY)
                        entries.emplace_back(readEntry(tokenizer));

                    if (tokenizer.get().type == TokenType::COMMENT)
                        entries.emplace_back(new Comment(tokenizer.get().raw, tokenizer.get().value));
                }

                if (tokenizer.get().type == TokenType::UNKNOWN)
                    throw MalformedEntry(tokenizer.get().value);

                g->setEntries(entries);
                return g;
            }

            ast::Entry* Reader::readEntry(Tokenizer& tokenizer) {
                Token key = tokenizer.get();

                // next token could be a Local or a Value
                tokenizer.consume();
                Token next = tokenizer.get();

                if (next.type == TokenType::UNKNOWN)
                    throw MalformedEntry(tokenizer.get().value);

                if (next.type == TokenType::ENTRY_LOCALE) {
                    tokenizer.consume();

                    if (tokenizer.get().type == TokenType::ENTRY_VALUE)
                        return new Entry(key.raw, key.value, next.raw, next.value, tokenizer.get().raw,
                                         tokenizer.get().value);
                }

                if (tokenizer.get().type == TokenType::ENTRY_VALUE)
                    return new Entry(key.raw, key.value, "", "", tokenizer.get().raw, tokenizer.get().value);

                // if this position is reached something went wrong
                std::stringstream errorMsg;
                errorMsg << "Unexpected token " << tokenizer.get().type << " at line " << tokenizer.get().line;
                throw MalformedEntry(errorMsg.str());
            }
        }
    }
}
