// local
#include "Entry.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace AST {
            bool Entry::operator==(const Entry& rhs) const {
                return keyValue == rhs.keyValue &&
                       localeValue == rhs.localeValue &&
                       valueValue == rhs.valueValue;
            }

            bool Entry::operator!=(const Entry& rhs) const {
                return !(rhs == *this);
            }

            Entry::Entry(const std::string& keyRaw, const std::string& keyValue, const std::string& localeRaw,
                         const std::string& localeValue, const std::string& valueRaw, const std::string& valueValue)
                : keyRaw(keyRaw), keyValue(keyValue), localeRaw(localeRaw),
                  localeValue(localeValue), valueRaw(valueRaw), valueValue(valueValue) {}

            Entry::Entry(const std::string& key, const std::string& locale, const std::string& value) :
                keyRaw(key), keyValue(key) {

                if (!locale.empty()) {
                    localeRaw = ('[' + locale + ']');
                    localeValue = (locale);
                }

                if (!value.empty()) {
                    valueValue = value;
                }
                valueRaw = '=' + value;
            }

            std::string Entry::getValue() const {
                return valueValue;
            }

            void Entry::setValue(const std::string& newValue) {
                if (valueValue.empty()) {
                    valueRaw += newValue;
                    valueValue = newValue;
                } else {
                    auto pos = valueRaw.find(valueValue);

                    valueRaw.replace(pos, std::string::npos, newValue);
                    valueValue = newValue;
                }
            }

            void Entry::write(std::ostream& output) const {
                output << keyRaw << localeRaw << valueRaw;
            }

            std::string Entry::getKey() const {
                return keyValue;
            }

            std::string Entry::getLocale() const {
                return localeValue;
            }

            std::ostream& operator<<(std::ostream& os, const Entry& entry) {
                entry.write(os);
                return os;
            }

            Node* Entry::clone() const {
                return new Entry(*this);
            }
        }
    }
}
