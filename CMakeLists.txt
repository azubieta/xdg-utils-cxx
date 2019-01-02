cmake_minimum_required(VERSION 3.0)
project(
    XdgUtils
    VERSION 0.1.0
    DESCRIPTION "Freedesktop standards C++ implementation"
    LANGUAGES CXX
)

## Configuration options
option(XDG_UTILS_TESTS "Enable tests" ON)
option(XDG_UTILS_DESKTOP_ENTRY "Enable Desktop Entry" On)

# Instalation paths
set(XDG_UTILS_BIN_DIR bin CACHE PATH "Binaries install directory")
set(XDG_UTILS_LIB_DIR lib/XdgUtils CACHE PATH "Libraries install directory")
set(XDG_UTILS_HEADER_DIR include/XdgUtils CACHE PATH "Public Headers install directory")
set(XDG_UTILS_CMAKE_DIR lib/cmake/XdgUtils CACHE PATH "Cmake configs install directory")

# Sources
add_subdirectory(src)

include(cmake/ConfigurePackage.cmake)

# Tests
if(XDG_UTILS_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
