// system
#include <algorithm>

// local
#include <XdgUtils/DesktopEntry/DesktopEntryKeyValue.h>
#include <XdgUtils/DesktopEntry/Exceptions.h>
#include "DesktopEntryKeyValuePriv.h"

namespace XdgUtils {
    namespace DesktopEntry {
        DesktopEntryKeyValue::DesktopEntryKeyValue(const DesktopEntryKeyValue& other) {
            priv.reset(new Priv(*other.priv));
        }

        DesktopEntryKeyValue& DesktopEntryKeyValue::operator=(const DesktopEntryKeyValue& other) {
            priv.reset(new Priv(*other.priv));
            return *this;
        }

        DesktopEntryKeyValue::operator std::string() {
            return priv->node->getValue();
        }

        DesktopEntryKeyValue& DesktopEntryKeyValue::operator=(const std::string& value) {
            priv->node->setValue(value);
            return *this;
        }

        DesktopEntryKeyValue::operator bool() {
            auto valueStr = priv->node->getValue();
            // lower
            std::transform(valueStr.begin(), valueStr.end(), valueStr.begin(), ::tolower);

            if (valueStr.find("true") != std::string::npos)
                return true;

            if (valueStr.find("false") != std::string::npos)
                return false;

            // the value is not a bool
            throw XdgUtils::DesktopEntry::BadCast("DesktopEntryKeyValue " + valueStr + " can't be converted to bool");
        }

        DesktopEntryKeyValue& DesktopEntryKeyValue::operator=(bool value) {
            std::string valueStr = value ? "true" : "false";
            priv->node->setValue(valueStr);
            return *this;
        }

        DesktopEntryKeyValue::operator const char*() {
            return priv->node->getValue().c_str();
        }

        DesktopEntryKeyValue& DesktopEntryKeyValue::operator=(const char* value) {
            if (value != nullptr)
                priv->node->setValue(value);
            else
                priv->node->setValue(std::string());
            return *this;
        }

        DesktopEntryKeyValue::operator int() {
            auto valueStr = priv->node->getValue();
            auto value = std::stoi(valueStr);

            return value;
        }

        DesktopEntryKeyValue& DesktopEntryKeyValue::operator=(int value) {
            priv->node->setValue(std::to_string(value));
            return *this;
        }

        DesktopEntryKeyValue::operator double() {
            auto valueStr = priv->node->getValue();
            auto value = std::stod(valueStr);

            return value;
        }

        DesktopEntryKeyValue& DesktopEntryKeyValue::operator=(double value) {
            priv->node->setValue(std::to_string(value));
            return *this;
        }

        DesktopEntryKeyValue::DesktopEntryKeyValue(DesktopEntryKeyValue::Priv* priv) : priv(priv) {
        }

        DesktopEntryKeyValue::~DesktopEntryKeyValue() = default;

    }
}
