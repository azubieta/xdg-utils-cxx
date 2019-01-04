// system
#include <vector>
#include <sstream>


// local
#include <XdgUtils/DesktopEntry/DesktopEntryExecValue.h>
#include <set>

namespace XdgUtils {
    namespace DesktopEntry {
        struct DesktopEntryExecValue::Priv {
            std::vector<std::string> sections;
            std::string escapedCharacters = "\"`$\\";
            std::string reservedCharacters = " \t\n\"\'\\<>~|&;$*?#()`";

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
                    if (firstSection)
                        firstSection = false;
                    else
                        res << " ";

                    if (containsReservedCharacter(section)) {
                        // dump escaped section
                        res << "\"";
                        for (const auto& c: section) {
                            if (escapedCharacters.find(c) != std::string::npos)
                                res << "\\";
                            res << c;
                        }
                        res << "\"";

                    } else
                        res << section;

                }
                return res.str();
            }

            bool containsReservedCharacter(const std::string& string) {
                for (const auto& c: string)
                    if (reservedCharacters.find(c) != std::string::npos)
                        return true;

                return false;
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
    }
}


