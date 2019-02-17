#pragma once

// system
#include <memory>
#include <vector>
#include <ostream>

// local
#include "Node.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace AST {
            /**
             * AST stands for abstract syntax tree. This class provides a representation of a Desktop Entry in form of a
             * tree.
             *
             * For more details about AST see https://en.wikipedia.org/wiki/Abstract_syntax_tree
             */
            class AST {
            public:
                AST();

                // Copy constructor
                AST(const AST& other);

                // Copy assignment
                AST& operator=(const AST& other);

                // Move constructor
                AST(AST&& other) noexcept;

                // Move assignment
                AST& operator=(AST&& other) noexcept;


                std::vector<std::shared_ptr<Node>>& getEntries();

                const std::vector<std::shared_ptr<Node>>& getEntries() const;

                void setEntries(const std::vector<std::shared_ptr<Node>>& entries);

                bool operator==(const AST& rhs) const;

                bool operator!=(const AST& rhs) const;

                void write(std::ostream& output) const;

                friend std::ostream& operator<<(std::ostream& os, const AST& ast);

            private:
                std::vector<std::shared_ptr<Node>> entries;
            };
        }
    }
}
