#pragma once

// system
#include <memory>
#include <iostream>
#include <string>
#include <vector>

// local
#include <XdgUtils/DesktopEntry/Exceptions.h>

namespace XdgUtils {
    namespace DesktopEntry {

        /**
         * Represents a Desktop Entry according to https://standards.freedesktop.org/desktop-entry-spec/
         *
         * Entry contents are reference through its path.
         * A path is made by: <Group Name>/<Key Name>[<locale>]. Locale section is optional.
         */
        class DesktopEntry {
        public:
            DesktopEntry();

            explicit DesktopEntry(const std::string& data);

            explicit DesktopEntry(std::istream& data);

            DesktopEntry(const DesktopEntry& other);

            virtual ~DesktopEntry();

            /**
             * Set <value> to the entry reference by <path>.
             * If the Group or Key doesn't exist they will be created.
             * @param path
             * @param value
             */
            void set(const std::string& path, const std::string& value);

            /**
             * Get the value of the entry pointed by <path>.
             * @param path
             * @param fallback
             * @return entry value or <fallback> if the entry doesn't exist
             */
            std::string get(const std::string& path, const std::string& fallback = "") const;

            /**
             * @param path
             * @return true if there is an entry at <path>, false otherwise
             */
            bool exists(const std::string& path) const;

            /**
             * Remove entry or group referenced by <path>
             * @param path
             */
            void remove(const std::string& path);

            /**
             * @return Paths to all available entries and groups
             */
            std::vector<std::string> paths() const;

            /**
             * Attempts to read the <is> stream as a Desktop Entry. Any existent data will be replaced.
             * @param input
             * @throw ReadError if something goes wrong
             */
            friend std::istream& operator>>(std::istream& is, const DesktopEntry& entry);

            /**
              * Attempts to write this Desktop Entry to the <os> stream.
              * @param output
              */
            friend std::ostream& operator<<(std::ostream& os, const DesktopEntry& entry);


            bool operator==(const DesktopEntry& rhs) const;

            bool operator!=(const DesktopEntry& rhs) const;

        private:
            struct Priv;
            std::unique_ptr<Priv> priv;
        };
    }
}
