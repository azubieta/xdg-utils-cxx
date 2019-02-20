#pragma once
// system
#include <memory>
#include <string>

namespace XdgUtils {
    namespace DesktopEntry {
        /**
         * @brief Desktop Entry values accessor.
         *
         * Provides a mutable reference to the inner desktop entry key values and cast constructors
         * to ease manipulation.
         */
        class DesktopEntryKeyValue {
        public:
            DesktopEntryKeyValue(const DesktopEntryKeyValue& other);

            DesktopEntryKeyValue& operator=(const DesktopEntryKeyValue& other);

            explicit operator const char*();

            explicit operator std::string();

            explicit operator bool();

            explicit operator int();

            explicit operator double();

            DesktopEntryKeyValue& operator=(double value);

            DesktopEntryKeyValue& operator=(int value);

            DesktopEntryKeyValue& operator=(const char* value);

            DesktopEntryKeyValue& operator=(const std::string& value);

            DesktopEntryKeyValue& operator=(bool value);

            ~DesktopEntryKeyValue();

        protected:
            class Priv;

            std::unique_ptr<Priv> priv;

            friend class DesktopEntry;

            explicit DesktopEntryKeyValue(Priv* priv);
        };
    }
}
