// system
#include <string>
#include <AST/Comment.h>
#include <AST/Group.h>
#include <AST/Entry.h>

// local
#include "Reader.h"
#include "Tokenizer.h"
#include "Errors.h"

using namespace XdgUtils::DesktopEntry::AST;

namespace XdgUtils {
    namespace DesktopEntry {
        namespace Reader {
            AST::AST Reader::read(std::istream& input) {
                Tokenizer tokenizer(input);
                XdgUtils::DesktopEntry::AST::AST ast;

                std::vector<std::shared_ptr<Node>> entries;
                tokenizer.consume();

                while (!tokenizer.isCompleted() && tokenizer.get().type != TokenType::UNKNOWN) {

                    if (tokenizer.get().type == TokenType::COMMENT) {
                        entries.emplace_back(new Comment(tokenizer.get().raw, tokenizer.get().value));
                        tokenizer.consume();

                        continue;
                    }

                    if (tokenizer.get().type == TokenType::GROUP_HEADER) {
                        entries.emplace_back(readGroup(tokenizer));

                        continue;
                    }

                    // only comments or group headers tokens can be found other things are an error
                    std::stringstream err;
                    err << "Unexpected token: " << tokenizer.get().type << " at line: " << tokenizer.get().line;
                    throw MalformedEntry(err.str());
                }

                if (!tokenizer.isCompleted())
                    throw MalformedEntry(tokenizer.get().value);

                ast.setEntries(entries);
                return ast;
            }

            std::shared_ptr<Group> Reader::readGroup(Tokenizer& tokenizer) {
                std::shared_ptr<Group> g(new Group(tokenizer.get().raw, tokenizer.get().value));

                std::vector<std::shared_ptr<Node>> entries;
                while (!tokenizer.isCompleted() && tokenizer.consume() &&
                       (tokenizer.get().type == TokenType::COMMENT || tokenizer.get().type == TokenType::ENTRY_KEY)) {

                    if (tokenizer.get().type == TokenType::ENTRY_KEY)
                        entries.emplace_back(readEntry(tokenizer));

                    if (tokenizer.get().type == TokenType::COMMENT)
                        entries.emplace_back(new Comment(tokenizer.get().raw, tokenizer.get().value));
                }

                if (!tokenizer.isCompleted() && tokenizer.get().type == TokenType::UNKNOWN)
                    throw MalformedEntry(tokenizer.get().value);

                g->setEntries(entries);
                return g;
            }

            AST::Entry* Reader::readEntry(Tokenizer& tokenizer) {
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
