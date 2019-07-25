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

        const std::string XdgConfigHome() {
            std::string xdgConfigHome;

            // try to read it from the environment
            char* configHomeVal = getenv("XDG_CONFIG_HOME");
            if (configHomeVal != nullptr && !std::string(configHomeVal).empty())
                xdgConfigHome = configHomeVal;
            else {
                // Fallback to $HOME/.config
                auto homeVal = Home();

                if (!homeVal.empty())
                    xdgConfigHome = homeVal + "/.config";
            }

            return xdgConfigHome;
        }

        const std::string XdgCacheHome() {
            std::string xdgCacheHome;

            // try to read it from the environment
            char* cacheHomeVal = getenv("XDG_CACHE_HOME");
            if (cacheHomeVal != nullptr && !std::string(cacheHomeVal).empty())
                xdgCacheHome = cacheHomeVal;
            else {
                // Fallback to $HOME/.cache
                auto homeVal = Home();

                if (!homeVal.empty())
                    xdgCacheHome = homeVal + "/.cache";
            }

            return xdgCacheHome;
        }
    }
}

