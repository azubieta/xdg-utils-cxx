add_executable(
    TestAST

    TestAST.cpp
    $<TARGET_OBJECTS:DesktopEntryAST> TestEntry.cpp TestComment.cpp TestGroup.cpp)

target_include_directories(TestAST PRIVATE "${PROJECT_SOURCE_DIR}/src/DesktopEntry/AST")
target_link_libraries(TestAST GTest::GTest GTest::Main)

gtest_discover_tests(TestAST)
