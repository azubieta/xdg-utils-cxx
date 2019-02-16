#pragma once

// system
#include <string>
#include <ostream>

// local
#include "Node.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace AST {
            /**
             * Describes a Desktop Entry entry.
             * See https://standards.freedesktop.org/desktop-entry-spec/latest/
             */
            class Entry : public Node {
            public:
                Entry(const std::string &key, const std::string &locale, const std::string &value);

                Entry(const std::string& keyRaw, const std::string& keyValue, const std::string& localeRaw,
                      const std::string& localeValue, const std::string& valueRaw, const std::string& valueValue);

                std::string getKey() const;

                std::string getLocale() const;

                std::string getValue() const override;

                void setValue(const std::string& newValue) override;

                void write(std::ostream& output) const override;

                Node* clone() const override;

                /**
                 * Compare two Entries according to they fields values. Raw values will be ignored
                 * @param rhs
                 * @return
                 */
                bool operator==(const Entry& rhs) const;

                bool operator!=(const Entry& rhs) const;

                friend std::ostream& operator<<(std::ostream& os, const Entry& entry);

            private:
                std::string keyRaw;
                std::string keyValue;

                std::string localeRaw;
                std::string localeValue;

                std::string valueRaw;
                std::string valueValue;
            };
        }
    }
}
