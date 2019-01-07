//system
#include <cstdlib>
#include <string>

// library
#include <XdgUtils/BaseDir/BaseDir.h>


// local
#include "XdgUtils/BaseDir/BaseDir.h"

namespace XdgUtils {
    namespace BaseDir {

        const std::string Home() {
            std::string home;

            auto envHome = getenv("HOME");
            if (envHome)
                home = envHome;

            return home;
        }

        const std::string XdgDataHome() {
            std::string xdgDataHome;

            // try to read it from the environment
            char* dataHomeVal = getenv("XDG_DATA_HOME");
            if (dataHomeVal != nullptr && !std::string(dataHomeVal).empty())
                xdgDataHome = dataHomeVal;
            else {
                // Fallback to $HOME/.local/share
                auto homeVal = Home();
                if (!homeVal.empty())
                    xdgDataHome = homeVal + "/.local/share";
            }

            return xdgDataHome;
        }
    }
}

