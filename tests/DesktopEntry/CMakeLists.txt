add_subdirectory(AST)
add_subdirectory(Reader)

add_executable(
    TestXdgUtilsDesktopEntry
    TestDesktopEntry.cpp
    TestDesktopEntryStringsValue.cpp
    TestDesktopEntryExecValue.cpp
    TestDesktopEntryKeyPath.cpp
)

target_include_directories(TestXdgUtilsDesktopEntry PRIVATE "${PROJECT_SOURCE_DIR}/src/desktop_entry")
target_link_libraries(TestXdgUtilsDesktopEntry XdgUtils::DesktopEntry GTest::GTest GTest::Main)

if(${CMAKE_VERSION} VERSION_LESS "3.10.0")
    add_test(TestXdgUtilsDesktopEntry TestXdgUtilsDesktopEntry)
else()
    gtest_discover_tests(TestXdgUtilsDesktopEntry)
endif()


