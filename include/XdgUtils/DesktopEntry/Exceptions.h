#pragma once

// system
#include <stdexcept>

namespace XdgUtils {
    namespace DesktopEntry {
        class DesktopEntryError : public std::runtime_error {
        public:
            explicit DesktopEntryError(const std::string& what) : std::runtime_error(what) {}
        };

        class ReadError : public DesktopEntryError {
        public:
            explicit ReadError(const std::string& what) : DesktopEntryError(what) {}
        };

        class ParseError : public DesktopEntryError {
        public:
            explicit ParseError(const std::string& what) : DesktopEntryError(what) {}
        };

        class MalformedPathError : public DesktopEntryError {
        public:
            explicit MalformedPathError(const std::string& what) : DesktopEntryError(what) {}
        };

        class BadCast : public DesktopEntryError {
        public:
            explicit BadCast(const std::string& what) : DesktopEntryError(what) {}
        };
    }
}
