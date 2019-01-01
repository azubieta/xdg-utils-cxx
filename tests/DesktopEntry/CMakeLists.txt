add_subdirectory(AST)
add_subdirectory(Reader)

add_executable(
    TestDesktopEntry
    TestDesktopEntry.cpp)

target_include_directories(TestDesktopEntry PRIVATE "${PROJECT_SOURCE_DIR}/src/desktop_entry")
target_link_libraries(TestDesktopEntry XdgUtils::DesktopEntry GTest::GTest GTest::Main)

gtest_discover_tests(TestDesktopEntry)
