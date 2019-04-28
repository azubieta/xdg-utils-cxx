cmake_minimum_required(VERSION 3.0)
project(XdgUtils)
set(PROJECT_VERSION 0.1.1)
set(PROJECT_DESCRIPTION "Freedesktop standards C++ implementation")
set(PROJECT_HOMEPAGE_URL https://github.com/azubieta/xdg-utils-cxx)

## Configuration options
option(XDG_UTILS_SHARED "Build shared libs instead of static" OFF)
option(XDG_UTILS_TESTS "Build tests" OFF)
option(XDG_UTILS_CODE_COVERAGE "Build Code Coverage report" OFF)

## Global variables

# Request C++-11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set GNU Install Dirs variables
include(GNUInstallDirs)

# Prepare code coverage
include(cmake/code_coverge_config.cmake)

# Sources
add_subdirectory(src)

# Tests
enable_testing()
add_subdirectory(tests)
