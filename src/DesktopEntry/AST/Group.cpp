#include <iostream>
#include "Group.h"
#include "Entry.h"
#include "Comment.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace AST {
            Group::Group(const std::string& headerRawValue, const std::string& headerValue) : headerRawValue(
                headerRawValue), headerValue(headerValue) {
                if (headerValue.empty())
                    throw std::runtime_error("Group Header cannot be emtpy");
            }

            std::string Group::getValue() const {
                return headerValue;
            }

            void Group::setValue(const std::string& newValue) {
                if (newValue.empty())
                    throw std::runtime_error("Group Header cannot be emtpy");

                auto pos = headerRawValue.find(headerValue);

                headerRawValue = '[' + newValue + ']';
                headerValue = newValue;
            }

            void Group::write(std::ostream& output) const {
                output << headerRawValue << std::endl;

                auto last = --(entries.end());
                for (auto itr = entries.begin(); itr != entries.end(); ++itr) {
                    itr->get()->write(output);

                    if (itr != last)
                        output << std::endl;
                }
            }

            std::vector<std::shared_ptr<Node>>& Group::getEntries() {
                return entries;;
            }

            const std::vector<std::shared_ptr<Node>>& Group::getEntries() const {
                return entries;
            }

            void Group::setEntries(const std::vector<std::shared_ptr<Node>>& entries) {
                this->entries.clear();
                for (const auto& entry: entries)
                    this->entries.emplace_back(entry->clone());
            }

            bool Group::operator==(const Group& rhs) const {
                if (headerValue != rhs.headerValue)
                    return false;

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


            bool Group::operator!=(const Group& rhs) const {
                return !(rhs == *this);
            }

            std::ostream& operator<<(std::ostream& os, const Group& group) {
                group.write(os);
                return os;
            }

            Node* Group::clone() const {
                return new Group(*this);
            }

            Group::Group(const Group& other) : headerValue(other.headerValue), headerRawValue(other.headerRawValue) {
                setEntries(other.entries);
            }

            Group& Group::operator=(const Group& other) {
                headerValue = other.headerValue;
                headerRawValue = other.headerRawValue;

                setEntries(other.entries);
                return *this;
            }

            Group::Group(Group&& other) noexcept {
                headerValue = std::move(other.headerValue);
                headerRawValue = std::move(other.headerRawValue);
                entries = std::move(other.entries);
            }

            Group& Group::operator=(Group&& other) noexcept {
                headerValue = std::move(other.headerValue);
                headerRawValue = std::move(other.headerRawValue);
                entries = std::move(other.entries);

                return *this;
            }

            Group::~Group() = default;
        }
    }
}
