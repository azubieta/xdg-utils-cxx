#pragma once

// system
#include <memory>
#include <string>

namespace XdgUtils {
    namespace DesktopEntry {
        /**
         * Utility class to handle 'string(s)' values in Desktop Entries.
         * More details at: https://standards.freedesktop.org/desktop-entry-spec/latest/ar01s04.html
         */
        class DesktopEntryStringsValue {
        public:
            DesktopEntryStringsValue();

            /**
                         * Create a instance from a DesktopEntry value
                         * @param data
                         */
            explicit DesktopEntryStringsValue(const std::string& data);

            virtual ~DesktopEntryStringsValue();

            /**
             * @return total of strings contained
             */
            unsigned long size() const;

            /**
             * Access string at <o>
             * @param i
             * @return string
             */
            std::string& operator[](int i);

            /**
             * @return string list raw representation to be set on the DesktopEntry
             */
            std::string dump();


            /**
             * Append <string> at the end of the list
             * @param string
             */
            void append(const std::string& string);

            /**
             * Remove item at <pos>
             * @param pos
             */
            void remove(int pos);

        private:
            struct Priv;
            std::unique_ptr<Priv> priv;
        };
    }
}
