#pragma once

// system
#include <istream>
#include <AST/Group.h>
#include <AST/Comment.h>

// local
#include "AST/AST.h"
#include "AST/Group.h"
#include "AST/Entry.h"
#include "Tokenizer.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace Reader {
            /**
             * Reads a Desktop Entry according to the following formal grammar.
             * F -> C* G+ EOF
             * C -> # (any ASCII char)+ EOL
             * C -> (space)* EOL
             * G -> GH E*
             * GH -> [ (A-Za-z0-9)+ ] EOL
             * E -> EK EL? EV EOL
             * EK -> (A-Za-z0-9)+
             * EL -> [ (any ASCII char)+ ] (space)*
             * EV -> '=' (any ASCII char)+ EOL
             *
             * Where:
             * F: stands for File
             * C: stands for Comment
             * G: stands for Group
             * GH: stands for Group Header
             * E: stands for Entry
             * EK: stands for Entry Key
             * EL: stands for Entry Locale
             * EV: stands for Entry Value
             *
             * More about formal grammars at: https://en.wikipedia.org/wiki/Formal_grammar
             * More about Desktop Entries at: https://standards.freedesktop.org/desktop-entry-spec/latest/index.html
             */
            class Reader {
            public:
                /**
                 * Read a Desktop Entry into a AST
                 * @param input
                 * @return AST if all goes ok
                 * @throw MalformedEntry in case of errors
                 */
                XdgUtils::DesktopEntry::AST::AST read(std::istream& input);

                /**
                 * Read Group tokens
                 * @param tokenizer
                 * @return Group Node
                 * @throw MalformedEntry in case of errors
                 */
                std::shared_ptr<AST::Group> readGroup(Tokenizer& tokenizer);

                /**
                 * Read entry tokens
                 * @param tokenizer
                 * @return Entry node
                 * @throw MalformedEntry in case of errors
                 */
                AST::Entry* readEntry(Tokenizer& tokenizer);
            };
        }
    }
}
