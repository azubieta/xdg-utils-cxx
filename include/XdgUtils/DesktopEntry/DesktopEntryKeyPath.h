#pragma once

// system
#include <string>
#include <memory>

// local
#include <XdgUtils/DesktopEntry/Exceptions.h>
#include <ostream>

namespace XdgUtils {
    namespace DesktopEntry {
        /**
         * Utility class to parse, validate and extract Key Paths sections.
         *
         * A KeyPath has the following format:
         * <group>/<key>[<locale>]
         */
        class DesktopEntryKeyPath {
        public:
            explicit DesktopEntryKeyPath(const std::string& path);

            DesktopEntryKeyPath(const std::string& group, const std::string& key, const std::string& locale);

            DesktopEntryKeyPath(const DesktopEntryKeyPath& other);

            DesktopEntryKeyPath& operator=(const DesktopEntryKeyPath& other);

            DesktopEntryKeyPath& operator=(const std::string& path);

            virtual ~DesktopEntryKeyPath();

            bool operator==(const DesktopEntryKeyPath& rhs) const;

            bool operator!=(const DesktopEntryKeyPath& rhs) const;

            bool operator==(const std::string& path) const;

            bool operator!=(const std::string& path) const;

            friend std::ostream& operator<<(std::ostream& os, const DesktopEntryKeyPath& path);

            /**
             * @return group section of the KeyPath
             */
            std::string group() const;

            /**
             * Set group section of the path
             * @param group
             */
            void setGroup(const std::string& group);

            /**
             * @return key section of the KeyPath or empty string if none
             */
            std::string key() const;

            /**
             * Set the key section of the path
             * @param key
             */
            void setKey(const std::string& key);

            /**
             * @return locale section of the KeyPath or empty string if none
             */
            std::string locale() const;

            /**
             * Set the locale section of the path
             * @param locale
             */
            void setLocale(const std::string& locale);

            /**
             * @return key and locale sections
             */
            std::string fullKey() const;

            /**
             * @return string representation of the KeyPath
             */
            std::string string() const;

        private:
            struct Priv;
            std::unique_ptr<Priv> priv;
        };
    }
}
