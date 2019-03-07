add_subdirectory(AST)
add_subdirectory(Reader)

add_gtest(
    TestXdgUtilsDesktopEntry

    TestDesktopEntry.cpp
    TestDesktopEntryKeyPath.cpp
    TestDesktopEntryValue.cpp
    TestDesktopEntryExecValue.cpp
    TestDesktopEntryStringsValue.cpp
)

target_link_libraries(TestXdgUtilsDesktopEntry XdgUtils::DesktopEntry)
