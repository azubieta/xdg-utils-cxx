#include "AST.h"
#include "Group.h"
#include "Comment.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace AST {

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
                auto last = --(entries.end());
                for (auto itr = entries.begin(); itr != entries.end(); ++itr) {
                    itr->get()->write(output);

                    if (itr != last)
                        output << std::endl;
                }
            }

            AST::AST(const AST& other) {
                entries.clear();
                for (const auto& entry: other.entries)
                    entries.emplace_back(entry->clone());
            }

            AST& AST::operator=(const AST& other) {
                entries.clear();
                for (const auto& entry: other.entries)
                    entries.emplace_back(entry->clone());

                return *this;
            }

            AST::AST(AST&& other) noexcept {
                entries = std::move(other.entries);
            }

            AST& AST::operator=(AST&& other) noexcept {
                entries = std::move(other.entries);
                return *this;
            }

            AST::AST() = default;
        }
    }
}
