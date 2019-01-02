#pragma once

// system
#include <stdexcept>

namespace XdgUtils {
    namespace DesktopEntry {
        namespace Reader {
            class MalformedEntry : public std::runtime_error {
            public:
                explicit MalformedEntry(const std::string& msg) : runtime_error(msg) {}
            };

            class NoTokensLeft : public std::runtime_error {
            public:
                explicit NoTokensLeft(const std::string& msg) : runtime_error(msg) {}
            };
        }
    }
}
