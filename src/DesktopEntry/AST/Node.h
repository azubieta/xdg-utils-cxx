#pragma once

#include <ostream>

namespace XdgUtils {
    namespace DesktopEntry {
        namespace AST {
            class Node {
            public:
                virtual std::string getValue() const = 0;

                virtual void setValue(const std::string& newValue) = 0;

                virtual void write(std::ostream& output) const = 0;

                virtual Node* clone() const = 0;

                friend std::ostream& operator<<(std::ostream& os, const Node& node) {
                    node.write(os);
                    return os;
                }


                bool operator==(const Node& rhs) const;

                bool operator!=(const Node& rhs) const;

                virtual ~Node() = default;
            };

        }
    }
}
