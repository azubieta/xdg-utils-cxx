#pragma once

// system
#include <stdexcept>

namespace xdg_utils {
    namespace desktop_entry {
        namespace reader {
            class MalformedEntry : public std::runtime_error {
            public:
                MalformedEntry(const std::string& msg) : runtime_error(msg) {}
            };
        }
    }
}
