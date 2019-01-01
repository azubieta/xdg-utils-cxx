add_executable(
    TestDesktopEntryReader

    TestDesktopEntryReaderLexer.cpp
    TestDesktopEntryReaderTokenizer.cpp
    TestDesktopEntryReader.cpp

    $<TARGET_OBJECTS:AST>
    $<TARGET_OBJECTS:DesktopEntryReader>
)

target_include_directories(TestDesktopEntryReader PRIVATE "${PROJECT_SOURCE_DIR}/src/desktop_entry")
target_link_libraries(TestDesktopEntryReader GTest::GTest GTest::Main)

gtest_discover_tests(TestDesktopEntryReader)
