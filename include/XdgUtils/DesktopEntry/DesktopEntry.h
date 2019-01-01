#pragma once

// system
#include <memory>
#include <iostream>
#include <string>
#include <vector>

// local
#include <Exceptions.h>

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
            std::string get(const std::string& path, const std::string& fallback = "");

            /**
             * @return names of the existent groups
             */
            std::vector<std::string> listGroups();

            /**
             * @param group
             * @return names of the existent keys that belongs to <group>
             */
            std::vector<std::string> listKeys(const std::string& group);

            /**
             * @param path
             * @return true if there is an entry at <path>, false otherwise
             */
            bool exists(const std::string& path);

            /**
             * Remove entry or group referenced by <path>
             * @param path
             */
            void remove(const std::string& path);

            /**
             * Attempts to read the <input> stream as a Desktop Entry. Any existent data will be replaced.
             * @param input
             * @throw ReadError if something goes wrong
             */
            void read(std::istream* input);

            /**
             * Attempts to write this Desktop Entry to the <output> stream.
             * @param output
             */
            void write(std::stringstream* output);

        private:
            struct Impl;
            std::unique_ptr<Impl> impl;
        };
    }
}
