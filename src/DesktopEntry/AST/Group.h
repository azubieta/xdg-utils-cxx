#pragma once

// system
#include <string>
#include <vector>
#include <memory>
#include <ostream>

// local
#include "Node.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace AST {
            class Group : public Node {
            public:
                /**
                 * Create a group node. <headerRawValue> and <headerValue> cannot be empty
                 * @param headerRawValue
                 * @param headerValue
                 * @throw std::runtime_error if <headerRawValue> or <headerValue> are empty.
                 */
                Group(const std::string& headerRawValue, const std::string& headerValue);

                // Copy constructor
                Group(const Group& other);

                // Copy assigment
                Group& operator=(const Group& other);

                // Move constructor
                Group(Group&& other) noexcept;

                // Move assigment
                Group& operator=(Group&& other) noexcept;

                ~Group() override;

                std::string getValue() const override;

                /**
                 * @param newValue (cannot be empty)
                 * @throw std::runtime_error if <newValue> is empty.
                 */
                void setValue(const std::string& newValue) override;

                void write(std::ostream& output) const override;

                Node* clone() const override;

                std::vector<std::shared_ptr<Node>>& getEntries();

                const std::vector<std::shared_ptr<Node>>& getEntries() const;

                void setEntries(const std::vector<std::shared_ptr<Node>>& entries);

                bool operator==(const Group& rhs) const;

                bool operator!=(const Group& rhs) const;

                friend std::ostream& operator<<(std::ostream& os, const Group& group);

            private:
                std::string headerRawValue;
                std::string headerValue;

                std::vector<std::shared_ptr<Node>> entries;
            };
        }
    }
}
