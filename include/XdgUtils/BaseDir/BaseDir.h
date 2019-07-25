#pragma once

// system
#include <string>


namespace XdgUtils {
    namespace BaseDir {
        /**
         * Single base directory relative to which user-specific data files should be written.
         *
         * See: https://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html
         * @return XDG_DATA_HOME
         */
        const std::string Home();

        /**
         * Single base directory relative to which user-specific data files should be written.
         *
         * See: https://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html
         * @return XDG_DATA_HOME
         */
        const std::string XdgDataHome();

        /**
         * Single base directory relative to which user-specific data files should be written.
         *
         * See: https://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html
         * @return XDG_CONFIG_HOME
         */
        const std::string XdgConfigHome();

        /**
         * Single base directory relative to which user-specific data files should be written.
         *
         * See: https://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html
         * @return XDG_CACHE_HOME
         */
        const std::string XdgCacheHome();
    }
}
