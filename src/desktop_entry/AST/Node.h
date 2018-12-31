#pragma once

#include <ostream>

namespace xdg_utils {
    namespace desktop_entry {
        namespace ast {
            class Node {
            public:
                virtual std::string getValue() = 0;

                virtual void setValue(const std::string& newValue) = 0;

                virtual void write(std::ostream& output) const = 0;

                friend std::ostream& operator<<(std::ostream& os, const Node& node) {
                    node.write(os);
                    return os;
                }
            };
        }
    }
}
