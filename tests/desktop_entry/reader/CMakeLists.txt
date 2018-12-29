add_executable(
    TestDesktopEntryReader

    TestDesktopEntryReaderLexer.cpp
    TestDesktopEntryReaderTokenizer.cpp

    $<TARGET_OBJECTS:DesktopEntryReader>
)

target_include_directories(TestDesktopEntryReader PRIVATE "${PROJECT_SOURCE_DIR}/src/desktop_entry/reader")
target_link_libraries(TestDesktopEntryReader GTest::GTest GTest::Main)

gtest_discover_tests(TestDesktopEntryReader)
