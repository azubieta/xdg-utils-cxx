#include "Group.h"
#include "Entry.h"
#include "Comment.h"

namespace xdg_utils {
    namespace desktop_entry {
        namespace ast {
            Group::Group(const std::string& headerRawValue, const std::string& headerValue) : headerRawValue(
                headerRawValue), headerValue(headerValue) {
                if (headerValue.empty())
                    throw std::runtime_error("Group Header cannot be emtpy");
            }

            std::string Group::getValue() {
                return headerValue;
            }

            void Group::setValue(const std::string& newValue) {
                if (newValue.empty())
                    throw std::runtime_error("Group Header cannot be emtpy");

                auto pos = headerRawValue.find(headerValue);

                headerRawValue.replace(pos, std::string::npos, newValue);
                headerValue = newValue;
            }

            void Group::write(std::ostream& output) const {
                output << headerRawValue << std::endl;
                for (const auto& entry: entries) {
                    entry->write(output);
                    output << std::endl;
                }
            }

            const std::vector<std::shared_ptr<Node>>& Group::getEntries() const {
                return entries;
            }

            void Group::setEntries(const std::vector<std::shared_ptr<Node>>& entries) {
                Group::entries = entries;
            }

            bool Group::operator==(const Group& rhs) const {
                if (headerValue != rhs.headerValue)
                    return false;

                auto aItr = entries.begin();
                auto bItr = rhs.entries.begin();

                while (aItr != entries.end() && bItr != rhs.entries.end()) {
                    if (auto a = dynamic_cast<Entry*>((*aItr).get())) {
                        // if the first one is an Entry the second one must also be
                        if (auto b = dynamic_cast<Entry*>((*bItr).get())) {
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

            bool Group::operator!=(const Group& rhs) const {
                return !(rhs == *this);
            }

            std::ostream& operator<<(std::ostream& os, const Group& group) {
                group.write(os);
                return os;
            }

        }
    }
}
