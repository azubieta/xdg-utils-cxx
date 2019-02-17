// Local
#include "Node.h"

#include "Comment.h"
#include "Entry.h"
#include "Group.h"

namespace XdgUtils {
    namespace DesktopEntry {
        namespace AST {

            bool Node::operator!=(const Node& rhs) const {
                return !operator==(rhs);
            }

            bool Node::operator==(const Node& rhs) const {
                try {
                    auto a = dynamic_cast<const Comment&>(*this);
                    auto b = dynamic_cast<const Comment&>(rhs);

                    return a == b;
                } catch (const std::bad_cast&) {}

                try {
                    auto a = dynamic_cast<const Entry&>(*this);
                    auto b = dynamic_cast<const Entry&>(rhs);

                    return a == b;
                } catch (const std::bad_cast&) {}

                try {
                    auto a = dynamic_cast<const Group&>(*this);
                    auto b = dynamic_cast<const Group&>(rhs);

                    return a == b;
                } catch (const std::bad_cast&) {}

                return false;
            }
        }
    }
}
