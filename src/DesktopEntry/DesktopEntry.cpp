#include <sstream>
#include <list>
#include <regex>
#include <map>

// local
#include <XdgUtils/DesktopEntry/DesktopEntry.h>
#include <XdgUtils/DesktopEntry/DesktopEntryKeyPath.h>
#include "AST/AST.h"

#include "Reader/Tokenizer.h"
#include "Reader/Reader.h"
#include "Reader/Errors.h"
#include "DesktopEntryKeyValuePriv.h"

namespace XdgUtils {
    namespace DesktopEntry {
        struct DesktopEntry::Priv {
            AST::AST ast;

            // Cache of the existent entries and their paths
            std::map<std::string, std::shared_ptr<AST::Node>> paths;
            typedef std::pair<std::string, std::shared_ptr<AST::Node>> path_entry_t;

            void read(std::istream& in) {
                try {
                    Reader::Reader reader;
                    ast = reader.read(in);

                    updatePaths();
                } catch (const Reader::MalformedEntry& err) {
                    throw ReadError(err.what());
                }
            }

            /**
             * Recreate the paths mappings to the nodes inside the AST
             */
            void updatePaths() {
                paths.clear();

                for (const auto& astEntry: ast.getEntries()) {
                    if (auto group = std::dynamic_pointer_cast<AST::Group>(astEntry)) {
                        paths[group->getValue()] = astEntry;

                        for (const auto& groupEntry: group->getEntries()) {
                            if (auto entry = std::dynamic_pointer_cast<AST::Entry>(groupEntry)) {
                                DesktopEntryKeyPath path(group->getValue(), entry->getKey(), entry->getLocale());
                                paths[path.string()] = groupEntry;
                            }
                        }
                    }
                }
            }

            void createGroup(const std::string& name) {
                auto group = std::make_shared<AST::Group>("[" + name + "]", name);

                // update entries
                auto& entries = ast.getEntries();
                entries.emplace_back(group);

                // update path
                paths[name] = group;
            }

            void createEntry(const DesktopEntryKeyPath& keyPath, const std::string& value) {
                auto group = std::dynamic_pointer_cast<AST::Group>(paths[keyPath.group()]);
                // create group if it doesn't exists
                if (!group) {
                    createGroup(keyPath.group());
                    group = std::dynamic_pointer_cast<AST::Group>(paths[keyPath.group()]);
                }

                // append entry to group
                auto entry = std::make_shared<AST::Entry>(keyPath.key(), keyPath.locale(), value);
                std::vector<std::shared_ptr<AST::Node>>& entries = group->getEntries();
                entries.emplace_back(entry);

                // update paths
                paths[keyPath.string()] = entry;
            }

            void removeGroup(const std::string& groupName) {
                auto g = paths[groupName];

                // remove item from the AST
                auto astEntries = ast.getEntries();

                auto itemItr = std::find(astEntries.begin(), astEntries.end(), g);
                astEntries.erase(itemItr);

                ast.setEntries(astEntries);

                // remove path
                paths.erase(groupName);
            }

            void removeEntry(const std::string& path) {
                // Find path split
                auto splitIdx = path.rfind('/');

                if (splitIdx != std::string::npos) {
                    auto groupName = path.substr(0, splitIdx);
                    auto keyName = path.substr(splitIdx + 1, path.size() - splitIdx);

                    auto groupNode = paths[groupName];
                    auto entryNode = paths[path];

                    auto g = dynamic_cast<AST::Group*>(groupNode.get());
                    // remove item from the AST
                    auto groupEntries = g->getEntries();

                    auto itemItr = std::find(groupEntries.begin(), groupEntries.end(), groupNode);
                    groupEntries.erase(itemItr);

                    g->setEntries(groupEntries);

                    // remove path
                    paths.erase(path);
                }
            }

            std::shared_ptr<AST::Node> getOrCreateEntry(const DesktopEntryKeyPath& keyPath) {
                auto itr = paths.find(keyPath.string());
                if (itr == paths.end()) {
                    if (keyPath.key().empty())
                        createGroup(keyPath.group());
                    else
                        createEntry(keyPath, "");
                }

                return paths[keyPath.string()];
            }
        };

        DesktopEntry::DesktopEntry() : priv(new Priv) {}

        DesktopEntry::DesktopEntry(const std::string& data) : priv(new Priv) {
            std::stringstream ss(data);
            priv->read(ss);
        }

        DesktopEntry::DesktopEntry(std::istream& data) : priv(new Priv) {
            priv->read(data);
        }

        DesktopEntry::DesktopEntry(const DesktopEntry& other) : priv(new Priv()) {
            priv->ast = other.priv->ast;
            priv->updatePaths();
        }

        DesktopEntry& DesktopEntry::operator=(const DesktopEntry& other) {
            priv->ast = other.priv->ast;
            priv->updatePaths();

            return *this;
        }

        DesktopEntry::DesktopEntry::DesktopEntry(DesktopEntry&& other) noexcept {
            priv = std::move(other.priv);
        }


        DesktopEntry& DesktopEntry::operator=(DesktopEntry&& other) noexcept {
            priv = std::move(other.priv);

            return *this;
        }

        DesktopEntry::~DesktopEntry() = default;

        std::string DesktopEntry::get(const std::string& path, const std::string& fallback) const {
            auto itr = priv->paths.find(path);
            if (itr == priv->paths.end())
                return fallback;

            return itr->second->getValue();
        }

        void DesktopEntry::set(const std::string& path, const std::string& value) {
            auto itr = priv->paths.find(path);
            if (itr != priv->paths.end()) {
                // Update node value
                itr->second->setValue(value);
            } else {
                // Find path split
                DesktopEntryKeyPath keyPath(path);

                // create the group if it doesn't exists
                if (priv->paths.find(keyPath.group()) == priv->paths.end())
                    priv->createGroup(keyPath.group());

                if (!keyPath.key().empty())
                    priv->createEntry(keyPath, value);
            }
        }

        bool DesktopEntry::exists(const std::string& path) const {
            return priv->paths.find(path) != priv->paths.end();
        }

        void DesktopEntry::remove(const std::string& path) {
            if (exists(path)) {
                auto splitIdx = path.rfind('/');

                if (splitIdx != std::string::npos)
                    priv->removeEntry(path);
                else
                    priv->removeGroup(path);

            }
        }

        std::vector<std::string> DesktopEntry::paths() const {
            std::vector<std::string> paths;
            for (const auto& itr: priv->paths)
                paths.emplace_back(itr.first);

            return paths;
        }

        std::ostream& operator<<(std::ostream& os, const DesktopEntry& entry) {
            entry.priv->ast.write(os);
            return os;
        }

        std::istream& operator>>(std::istream& is, const DesktopEntry& entry) {
            entry.priv->read(is);
            return is;
        }

        bool DesktopEntry::operator==(const DesktopEntry& rhs) const {
            return priv->ast == rhs.priv->ast;
        }

        bool DesktopEntry::operator!=(const DesktopEntry& rhs) const {
            return !(rhs == *this);
        }


        DesktopEntryKeyValue DesktopEntry::operator[](const DesktopEntryKeyPath& keyPath) {
            auto entry = priv->getOrCreateEntry(keyPath);

            return DesktopEntryKeyValue(new DesktopEntryKeyValue::Priv(keyPath, entry));
        }

        DesktopEntryKeyValue DesktopEntry::operator[](const std::string& keyPath) {
            return operator[](DesktopEntryKeyPath(keyPath));
        }
    }

}
