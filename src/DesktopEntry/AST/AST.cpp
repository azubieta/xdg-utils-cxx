#include "AST.h"
#include "Group.h"
#include "Comment.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace AST {

            std::vector<std::shared_ptr<Node>>& AST::getEntries() {
                return entries;
            }

            const std::vector<std::shared_ptr<Node>>& AST::getEntries() const {
                return entries;
            }

            void AST::setEntries(const std::vector<std::shared_ptr<Node>>& entries) {
                this->entries.clear();
                for (const auto& entry: entries)
                    this->entries.emplace_back(entry->clone());
            }

            bool AST::operator==(const AST& rhs) const {
                auto aItr = entries.begin();
                auto bItr = rhs.entries.begin();

                while (aItr != entries.end() && bItr != rhs.entries.end()) {
                    if (*aItr->get() != *bItr->get())
                        return false;

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
                setEntries(other.entries);
            }

            AST& AST::operator=(const AST& other) {
                setEntries(other.entries);
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
