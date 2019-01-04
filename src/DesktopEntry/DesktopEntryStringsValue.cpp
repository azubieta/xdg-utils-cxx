// system
#include <vector>
#include <sstream>

// local
#include <XdgUtils/DesktopEntry/DesktopEntryStringsValue.h>

namespace XdgUtils {
    namespace DesktopEntry {
        struct DesktopEntryStringsValue::Priv {
            std::vector<std::string> sections;

            void parse(const std::string& in) {
                sections.clear();

                std::stringstream section;
                bool escapeNext = false;
                for (const auto& c: in) {
                    if (escapeNext) {
                        section << c;
                        escapeNext = false;
                        continue;
                    }

                    if (c == '\\') {
                        escapeNext = true;
                        continue;
                    }

                    if (c == ';') {
                        sections.emplace_back(section.str());
                        // clear string
                        section.str("");
                        continue;
                    }

                    section << c;
                }

                auto last = section.str();
                if (!last.empty())
                    sections.emplace_back(last);
            }

            std::string dump() {
                std::stringstream res;
                for (const auto& str: sections) {
                    for (const auto& c: str) {
                        // escape semicolon
                        if (c == ';')
                            res << "\\";
                        res << c;
                    }

                    res << ';';
                }

                return res.str();
            };
        };

        DesktopEntryStringsValue::DesktopEntryStringsValue() : priv(new Priv()) {

        }

        DesktopEntryStringsValue::DesktopEntryStringsValue(const std::string& data) : priv(new Priv()) {
            priv->parse(data);
        }

        unsigned long DesktopEntryStringsValue::size() const {
            return priv->sections.size();
        }

        std::string& DesktopEntryStringsValue::operator[](int i) {
            return priv->sections[i];
        }

        std::string DesktopEntryStringsValue::dump() {
            return priv->dump();
        }

        void DesktopEntryStringsValue::append(const std::string& string) {
            priv->sections.emplace_back(string);
        }

        void DesktopEntryStringsValue::remove(int pos) {
            priv->sections.erase(priv->sections.begin() + pos);
        }

        DesktopEntryStringsValue::~DesktopEntryStringsValue() = default;
    }
}
