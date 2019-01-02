add_executable(
    TestXdgUtilsDesktopAST

    TestAST.cpp
    TestEntry.cpp
    TestComment.cpp
    TestGroup.cpp

    $<TARGET_OBJECTS:XdgUtilsDesktopEntryAST>
)

target_include_directories(TestXdgUtilsDesktopAST PRIVATE "${PROJECT_SOURCE_DIR}/src/DesktopEntry/AST")
target_link_libraries(TestXdgUtilsDesktopAST GTest::GTest GTest::Main)

gtest_discover_tests(TestXdgUtilsDesktopAST)
