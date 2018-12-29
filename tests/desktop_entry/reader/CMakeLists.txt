add_executable(TestDesktopEntryReaderLexer TestDesktopEntryReaderLexer.cpp $<TARGET_OBJECTS:DesktopEntryReader>)

target_include_directories(TestDesktopEntryReaderLexer PRIVATE "${PROJECT_SOURCE_DIR}/src/desktop_entry/reader")
target_link_libraries(TestDesktopEntryReaderLexer GTest::GTest GTest::Main)

gtest_discover_tests(TestDesktopEntryReaderLexer)
