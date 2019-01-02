add_subdirectory(AST)
add_subdirectory(Reader)

add_executable(
    TestXdgUtilsDesktopEntry
    TestDesktopEntry.cpp)

target_include_directories(TestXdgUtilsDesktopEntry PRIVATE "${PROJECT_SOURCE_DIR}/src/desktop_entry")
target_link_libraries(TestXdgUtilsDesktopEntry XdgUtils::DesktopEntry GTest::GTest GTest::Main)

gtest_discover_tests(TestXdgUtilsDesktopEntry)
