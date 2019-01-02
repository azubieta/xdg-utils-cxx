#pragma once

// system
#include <exception>

namespace XdgUtils {
    namespace DesktopEntry {
        class ReadError : public std::runtime_error {
        public:
            explicit ReadError(const std::string& what) : std::runtime_error(what) {}
        };
    }
}
