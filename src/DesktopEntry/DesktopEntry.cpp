#include <sstream>
#include <list>
#include <regex>
#include <map>

// local
#include <DesktopEntry.h>
#include "AST/AST.h"

#include "Reader/Tokenizer.h"
#include "Reader/Reader.h"
#include "Reader/Errors.h"

namespace XdgUtils {
    namespace DesktopEntry {
        struct DesktopEntry::Impl {
            AST::AST ast;

            // Cache of the existent entries and their paths
            std::map<std::string, std::shared_ptr<AST::Node>> paths;
            typedef std::pair<std::string, std::shared_ptr<AST::Node>> path_entry_t;

            /**
             * Recreate the paths mappings to the nodes inside the AST
             */
            void updatePaths() {
                paths.clear();

                for (const auto& astEntry: ast.getEntries()) {
                    if (auto group = dynamic_cast<AST::Group*>(astEntry.get())) {
                        paths[group->getValue()] = astEntry;

                        for (const auto& groupEntry: group->getEntries()) {
                            if (auto entry = dynamic_cast<AST::Entry*>(groupEntry.get())) {
                                auto path = createEntryPath(group->getValue(), *entry);
                                paths[path] = groupEntry;
                            }
                        }
                    }
                }
            }

            void createGroup(const std::string& name) {
                std::shared_ptr<AST::Group> g(new AST::Group("[" + name + "]", name));

                // update entries
                auto entries = ast.getEntries();

                entries.emplace_back(g);

                ast.setEntries(entries);

                // update path
                paths[name] = g;
            }

            void createEntry(const std::string& groupName, const std::string& keypath, const std::string& value) {
                std::stringstream keystr;
                keystr << keypath << "=" << value;

                Reader::Tokenizer tokenizer(keystr);
                tokenizer.consume();
                Reader::Reader reader;
                std::shared_ptr<AST::Entry> entry(reader.readEntry(tokenizer));

                auto group = dynamic_cast<AST::Group*>(paths[groupName].get());

                // append entry to group
                auto entries = group->getEntries();
                entries.emplace_back(entry);
                group->setEntries(entries);

                // update paths
                auto path = createEntryPath(groupName, *entry);
                paths[path] = entry;
            }

            std::string createEntryPath(const std::string& groupName, const AST::Entry& entry) {
                std::stringstream path;

                if (!groupName.empty())
                    path << groupName << '/';

                path << entry.getKey();

                if (!entry.getLocale().empty())
                    path << '[' << entry.getLocale() << ']';

                return path.str();
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

                    AST::Group* g = dynamic_cast<AST::Group*>(groupNode.get());
                    // remove item from the AST
                    auto groupEntries = g->getEntries();

                    auto itemItr = std::find(groupEntries.begin(), groupEntries.end(), groupNode);
                    groupEntries.erase(itemItr);

                    g->setEntries(groupEntries);

                    // remove path
                    paths.erase(path);
                }
            }
        };

        DesktopEntry::DesktopEntry() : impl(new Impl) {}

        void DesktopEntry::read(std::istream& input) {
            try {
                Reader::Reader reader;
                impl->ast = reader.read(input);

                impl->updatePaths();
            } catch (const Reader::MalformedEntry& err) {
                throw ReadError(err.what());
            }
        }

        void DesktopEntry::write(std::stringstream& output) {
            impl->ast.write(output);
        }

        std::vector<std::string> DesktopEntry::listGroups() {
            std::vector<std::string> groups;
            for (const auto& node: impl->ast.getEntries())
                if (auto a = dynamic_cast<AST::Group*>(node.get()))
                    groups.emplace_back(a->getValue());

            return groups;
        }

        std::vector<std::string> DesktopEntry::listGroupKeys(const std::string& group) {
            std::vector<std::string> keys;

            // Find group
            auto itr = impl->paths.find(group);
            if (itr == impl->paths.end())
                return keys;

            auto gPtr = dynamic_cast<AST::Group*>(itr->second.get());

            if (gPtr) {
                for (const auto& node: gPtr->getEntries())
                    if (auto a = dynamic_cast<AST::Entry*>(node.get()))
                        keys.push_back(a->getKey());
            }

            return keys;
        }

        std::string DesktopEntry::get(const std::string& path, const std::string& fallback) {
            auto itr = impl->paths.find(path);
            if (itr == impl->paths.end())
                return fallback;

            return itr->second->getValue();
        }

        void DesktopEntry::set(const std::string& path, const std::string& value) {
            auto itr = impl->paths.find(path);
            if (itr != impl->paths.end()) {
                // Update node value
                itr->second->setValue(value);
            } else {
                // Find path split
                auto splitIdx = path.rfind('/');

                if (splitIdx != std::string::npos) {
                    auto groupName = path.substr(0, splitIdx);
                    auto keyName = path.substr(splitIdx + 1, path.size() - splitIdx);

                    auto groupItr = impl->paths.find(groupName);

                    // create the group if it doesn't exists
                    if (groupItr == impl->paths.end())
                        impl->createGroup(groupName);

                    impl->createEntry(groupName, keyName, value);

                } else
                    impl->createGroup(path);
            }
        }

        bool DesktopEntry::exists(const std::string& path) {
            return impl->paths.find(path) != impl->paths.end();
        }

        void DesktopEntry::remove(const std::string& path) {
            if (exists(path)) {
                auto splitIdx = path.rfind('/');

                if (splitIdx != std::string::npos)
                    impl->removeEntry(path);
                else
                    impl->removeGroup(path);

            }
        }

        DesktopEntry::~DesktopEntry() = default;
    }

}
