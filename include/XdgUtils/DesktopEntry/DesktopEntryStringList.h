#pragma once

// system
#include <memory>
#include <string>

namespace XdgUtils {
    namespace DesktopEntry {
        /**
         * Utility class to handle string list values at Desktop files.
         * More details at: https://standards.freedesktop.org/desktop-entry-spec/latest/ar01s04.html
         */
        class DesktopEntryStringList {
        public:
            /**
             * Create a instance from a DesktopEntry value
             * @param data
             */
            explicit DesktopEntryStringList(const std::string& data);

            virtual ~DesktopEntryStringList();

            unsigned long size() const;

            std::string& operator[](int i);

            /**
             * @return string list raw representation to be set on the DesktopEntry
             */
            std::string dump();


        private:
            struct Priv;
            std::unique_ptr<Priv> priv;
        };
    }
}
