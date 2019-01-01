cmake_minimum_required(VERSION 3.0)
project(XdgUtils)

option(XDG_UTILS_TESTS "Enable tests" ON)
option(XDG_UTILS_DESKTOP_ENTRY "Enable Desktop Entry" On)

add_subdirectory(src)
add_subdirectory(tests)
