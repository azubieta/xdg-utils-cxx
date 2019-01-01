find_package(GTest REQUIRED)
include(GoogleTest)

if(XDG_UTILS_DESKTOP_ENTRY)
    add_subdirectory(DesktopEntry)
endif()
