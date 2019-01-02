add_executable(
    TestXdgUtilsDesktopEntryReader

    TestDesktopEntryReaderLexer.cpp
    TestDesktopEntryReaderTokenizer.cpp
    TestDesktopEntryReader.cpp

    $<TARGET_OBJECTS:XdgUtilsDesktopEntryAST>
    $<TARGET_OBJECTS:XdgUtilsDesktopEntryReader>
)

target_include_directories(TestXdgUtilsDesktopEntryReader PRIVATE "${PROJECT_SOURCE_DIR}/src/DesktopEntry")
target_link_libraries(TestXdgUtilsDesktopEntryReader GTest::GTest GTest::Main)

gtest_discover_tests(TestXdgUtilsDesktopEntryReader)
