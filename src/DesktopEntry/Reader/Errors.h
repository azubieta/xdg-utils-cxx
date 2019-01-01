#pragma once

// system
#include <stdexcept>

namespace XdgUtils {
    namespace DesktopEntry {
        namespace Reader {
            class MalformedEntry : public std::runtime_error {
            public:
                MalformedEntry(const std::string& msg) : runtime_error(msg) {}
            };
        }
    }
}
