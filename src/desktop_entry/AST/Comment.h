#pragma once

// system
#include <string>
#include <ostream>

// local
#include "Node.h"

namespace xdg_utils {
    namespace desktop_entry {
        namespace ast {
            class Comment : public Node {
            public:
                Comment(const std::string& raw, const std::string& value);

                std::string getValue() override;

                void setValue(const std::string& newValue) override;

                void write(std::ostream& output) const override;

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
