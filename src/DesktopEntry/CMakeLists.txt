set(DesktopEntry_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(AST)
add_subdirectory(Reader)

set(
    srcs

    DesktopEntry.cpp
    DesktopEntryKeyPath.cpp
    DesktopEntryKeyValue.cpp
    DesktopEntryExecValue.cpp
    DesktopEntryStringsValue.cpp

    "$<TARGET_OBJECTS:XdgUtilsDesktopEntryAST>"
    "$<TARGET_OBJECTS:XdgUtilsDesktopEntryReader>"
)

add_xdgutils_module(DesktopEntry "${srcs}")
install_xdgutils_module(DesktopEntry)
