// system
#include <vector>
#include <sstream>


// local
#include <XdgUtils/DesktopEntry/DesktopEntryExecValue.h>
#include <algorithm>

namespace XdgUtils {
    namespace DesktopEntry {
        struct DesktopEntryExecValue::Priv {
            std::vector<std::string> sections;

            void parse(const std::string& value) {
                // marks when the next char was escaped
                bool escapeNext = false;

                // marks when traversing a section between quotes '"'
                bool inBetweenQuotes = false;

                std::stringstream section;

                for (const auto& c: value) {
                    if (c == '\"') {
                        if (inBetweenQuotes)
                            finishSection(section);

                        inBetweenQuotes = !inBetweenQuotes;
                        continue;
                    }

                    if (inBetweenQuotes) {
                        if (escapeNext) {
                            section << c;
                            escapeNext = false;
                            continue;
                        }

                        if (c == '\\') {
                            escapeNext = true;
                            continue;
                        }

                        section << c;
                    } else {
                        if (c == ' ')
                            finishSection(section);
                        else
                            section << c;
                    }
                }

                finishSection(section);
            }

            void finishSection(std::stringstream& section) {
                auto sectionStr = section.str();
                section.str("");

                if (!sectionStr.empty())
                    sections.emplace_back(sectionStr);
            }

            std::string dump() {
                bool firstSection = true;

                std::stringstream res;

                for (const auto& section: sections) {
                    if (firstSection) {
                        firstSection = false;
                    } else {
                        res << " ";
                    }

                    res << quotePath(section);
                }

                return res.str();
            }
        };

        DesktopEntryExecValue::DesktopEntryExecValue() : priv(new Priv()) {}

        DesktopEntryExecValue::DesktopEntryExecValue(const std::string& value) : priv(new Priv()) {
            priv->parse(value);
        }

        DesktopEntryExecValue::~DesktopEntryExecValue() = default;

        unsigned long DesktopEntryExecValue::size() const {
            return priv->sections.size();
        }

        std::string& DesktopEntryExecValue::operator[](int i) {
            return priv->sections[i];
        }

        std::string DesktopEntryExecValue::dump() {
            return priv->dump();
        }

        void DesktopEntryExecValue::append(const std::string& string) {
            priv->sections.emplace_back(string);
        }

        void DesktopEntryExecValue::remove(int pos) {
            priv->sections.erase(priv->sections.begin() + pos);
        }

        std::string DesktopEntryExecValue::quotePath(const std::string& string) {
            // these characters need to be escaped with a backslash (\)
            static const std::string charactersToEscape = "\"`$\\";
            // the following characters don't require escaping but can be used fine with simple quoting
            static const std::string charactersWhichRequireQuoting = " \t\n\'<>~|&;*?#()";
            // we may need the combined list more than once and therefore cache it in a variable
            static const std::string reservedCharacters = charactersWhichRequireQuoting + charactersToEscape;

            std::ostringstream res;

            // some paths don't need to be quoted
            // in that case, we don't prepend/append quotes
            bool needsToBeQuoted = std::find_if(string.begin(), string.end(), [](const char c) {
                return reservedCharacters.find(c) != std::string::npos;
            }) != string.end();

            if (!needsToBeQuoted) {
                return string;
            }

            res << "\"";
            for (const auto& c: string) {
                if (charactersToEscape.find(c) != std::string::npos)
                    res << "\\";
                res << c;
            }
            res << "\"";

            return res.str();
        }
    }
}


