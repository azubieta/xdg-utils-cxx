#pragma once

// system
#include <string>
#include <ostream>

// local
#include "Node.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace AST {
            class Comment : public Node {
            public:
                Comment(const std::string& raw, const std::string& value);

                std::string getValue() const override;

                void setValue(const std::string& newValue) override;

                void write(std::ostream& output) const override;

                Node* clone() const override;

                bool operator==(const Comment& rhs) const;

                bool operator!=(const Comment& rhs) const;

                friend std::ostream& operator<<(std::ostream& os, const Comment& comment);

            private:
                std::string raw;
                std::string value;
            };
        }
    }
}
