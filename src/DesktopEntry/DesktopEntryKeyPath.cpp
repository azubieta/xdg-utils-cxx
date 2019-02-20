// system
#include <sstream>

// local
#include <XdgUtils/DesktopEntry/Exceptions.h>
#include <XdgUtils/DesktopEntry/DesktopEntryKeyPath.h>

namespace XdgUtils {
    namespace DesktopEntry {

        struct DesktopEntryKeyPath::Priv {
            std::string group;
            std::string key;
            std::string locale;

            explicit Priv(const std::string& path) {
                parse(path);
            }

            Priv(const std::string& group, const std::string& key, const std::string& locale) :
                group(group), key(key), locale(locale) {}

            Priv& operator=(const Priv& other) = default;

            bool operator==(const Priv& rhs) const {
                return group == rhs.group &&
                       key == rhs.key &&
                       locale == rhs.locale;
            }

            bool operator!=(const Priv& rhs) const {
                return !(rhs == *this);
            }

            void parse(const std::string& path) {
                // remove old values
                group.clear();
                key.clear();
                locale.clear();

                auto itr = path.begin();

                // parse the group section, '[' and ']' char are not allowed
                std::string invalidGroupChars = "[]";
                while (*itr != '\0' && *itr != '/') {
                    if (invalidGroupChars.find(*itr) != std::string::npos)
                        throw ParseError(std::string("Unexpected char in path group section: ") + *itr);

                    ++itr;
                }

                group = {path.begin(), itr};
                if (*itr == '\0')
                    return;

                // parse the key section
                // ignore group-key separator ('/')
                ++itr;
                auto keyBegin = itr;
                while (*itr != '\0' && *itr != '[') {
                    if (!std::isalnum(*itr) && *itr != '-' && *itr != '_')
                        throw ParseError(std::string("Unexpected char in path key section: ") + *itr);

                    ++itr;
                }

                key = {keyBegin, itr};
                if (*itr == '\0')
                    return;

                // parse locale section
                // ignore key-locale separator ('[')
                ++itr;
                auto localeBegin = itr;
                while (*itr != '\0' && *itr != ']')
                    ++itr;

                if (*itr == '\0')
                    throw ParseError(std::string("Unexpected char in path key section: ") + *itr);

                locale = {localeBegin, itr};
            }

            std::string string() const {
                std::stringstream pathBuilder;
                pathBuilder << group;

                if (key.empty())
                    return pathBuilder.str();

                pathBuilder << '/' << key;

                if (locale.empty())
                    return pathBuilder.str();

                pathBuilder << '[' << locale << ']';
                return pathBuilder.str();
            }

        };

        DesktopEntryKeyPath::DesktopEntryKeyPath(const std::string& path) : priv(new Priv(path)) {}


        DesktopEntryKeyPath::DesktopEntryKeyPath(const std::string& group, const std::string& key,
                                                 const std::string& locale) : priv(new Priv(group, key, locale)) {

        }

        std::string DesktopEntryKeyPath::group() const {
            return priv->group;
        }

        void DesktopEntryKeyPath::setGroup(const std::string& group) {
            if (group.empty())
                throw MalformedPathError("Group section cannot be empty");

            priv->group = group;
        }

        std::string DesktopEntryKeyPath::key() const {
            return priv->key;
        }

        void DesktopEntryKeyPath::setKey(const std::string& key) {
            for (const auto& c: key)
                if (!std::isalnum(c) && c != '-' && c != '_')
                    throw MalformedPathError("Unexpected char in key name");

            priv->key = key;
        }

        std::string DesktopEntryKeyPath::locale() const {
            return priv->locale;
        }

        void DesktopEntryKeyPath::setLocale(const std::string& locale) {
            priv->locale = locale;
        }

        std::string DesktopEntryKeyPath::string() const {
            return priv->string();
        }

        DesktopEntryKeyPath::DesktopEntryKeyPath(const DesktopEntryKeyPath& other) {
            priv.reset(new Priv(*other.priv));
        }

        DesktopEntryKeyPath& DesktopEntryKeyPath::operator=(const DesktopEntryKeyPath& other) {
            *priv = *(other.priv);
            return *this;
        }

        DesktopEntryKeyPath& DesktopEntryKeyPath::operator=(const std::string& path) {
            priv->parse(path);
            return *this;
        }

        bool DesktopEntryKeyPath::operator==(const DesktopEntryKeyPath& rhs) const {
            return *priv == *(rhs.priv);
        }

        bool DesktopEntryKeyPath::operator!=(const DesktopEntryKeyPath& rhs) const {
            return !(rhs == *this);
        }

        bool DesktopEntryKeyPath::operator==(const std::string& path) const {
            return priv->string() == path;
        }

        bool DesktopEntryKeyPath::operator!=(const std::string& path) const {
            return !(*this == path);
        }

        std::ostream& operator<<(std::ostream& os, const DesktopEntryKeyPath& path) {
            os << path.string();
            return os;
        }

        std::string DesktopEntryKeyPath::fullKey() const {
            return priv->key + '[' + priv->locale + ']';
        }

        DesktopEntryKeyPath::~DesktopEntryKeyPath() = default;
    }
}
