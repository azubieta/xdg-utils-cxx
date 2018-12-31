#include "AST.h"
#include "Group.h"
#include "Comment.h"

namespace xdg_utils {
    namespace desktop_entry {
        namespace ast {

            const std::vector<std::shared_ptr<Node>>& AST::getEntries() const {
                return entries;
            }

            void AST::setEntries(const std::vector<std::shared_ptr<Node>>& entries) {
                AST::entries = entries;
            }

            bool AST::operator==(const AST& rhs) const {
                auto aItr = entries.begin();
                auto bItr = rhs.entries.begin();

                while (aItr != entries.end() && bItr != rhs.entries.end()) {
                    if (auto a = dynamic_cast<Group*>((*aItr).get())) {
                        // if the first one is an Entry the second one must also be
                        if (auto b = dynamic_cast<Group*>((*bItr).get())) {
                            // if both are entries compare them as such
                            if (*a != *b)
                                return false;
                        } else
                            return false;
                    }

                    if (auto a = dynamic_cast<Comment*>((*aItr).get())) {
                        // if the first one is an Comment the second one must also be
                        if (auto b = dynamic_cast<Comment*>((*bItr).get())) {
                            // if both are comments compare them as such
                            if (*a != *b)
                                return false;
                        } else
                            return false;
                    }

                    ++aItr, ++bItr;
                }

                // Return true if both iterators reached the end
                return (aItr == entries.end() && bItr == rhs.entries.end());
            }

            bool AST::operator!=(const AST& rhs) const {
                return !(rhs == *this);
            }

            std::ostream& operator<<(std::ostream& os, const AST& ast) {
                ast.write(os);
                return os;
            }

            void AST::write(std::ostream& output) const {
                for (const auto& entry: entries) {
                    entry->write(output);

                    // Comments entries doesn't print new lines
                    if (auto a = dynamic_cast<Comment*>((entry).get()))
                        output << std::endl;
                }
            }
        }
    }
}
