#include <sstream>
#include <list>
#include <regex>
#include <map>

// local
#include <DesktopEntry.h>
#include "AST/AST.h"
#include "Reader/Reader.h"
#include "Reader/Errors.h"

namespace XdgUtils {
    namespace DesktopEntry {
        struct DesktopEntry::Impl {
            AST::AST ast;
        };

        DesktopEntry::DesktopEntry() : impl(new Impl) {}

        void DesktopEntry::read(std::istream* input) {
            try {
                Reader::Reader reader;
                impl->ast = reader.read(input);
            } catch (const Reader::MalformedEntry& err) {
                throw ReadError(err.what());
            }
        }

        void DesktopEntry::write(std::stringstream* output) {
            impl->ast.write(output);
        }

        std::vector<std::string> DesktopEntry::listGroups() {
            std::vector<std::string> groups;
            for (const auto node: impl->ast.getEntries())
                if (auto a = dynamic_cast<AST::Group*>(node.get()))
                    groups.emplace_back(a->getValue());

            return groups;
        }

        DesktopEntry::~DesktopEntry() = default;
    }

}
