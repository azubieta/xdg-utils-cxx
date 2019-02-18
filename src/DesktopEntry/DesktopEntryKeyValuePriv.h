#pragma once

// local
#include <XdgUtils/DesktopEntry/DesktopEntryKeyValue.h>
#include <XdgUtils/DesktopEntry/DesktopEntryKeyPath.h>
#include "DesktopEntryKeyValuePriv.h"
#include <AST/Node.h>

namespace XdgUtils {
    namespace DesktopEntry {
        class DesktopEntryKeyValue::Priv {
        public:
            DesktopEntryKeyPath path;
            std::shared_ptr<AST::Node> node;

            Priv(const DesktopEntryKeyPath& path, const std::shared_ptr<AST::Node>& node) : path(path), node(node) {}
        };
    }
}
