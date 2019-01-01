cmake_minimum_required(VERSION 3.0)
project(XdgUtils)

## Configuration options
option(XDG_UTILS_TESTS "Enable tests" ON)
option(XDG_UTILS_DESKTOP_ENTRY "Enable Desktop Entry" On)


# Sources
add_subdirectory(src)


# Tests
if(XDG_UTILS_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
