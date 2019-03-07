set(
    srcs

    TestDesktopEntryReaderLexer.cpp
    TestDesktopEntryReaderTokenizer.cpp
    TestDesktopEntryReader.cpp
    "$<TARGET_OBJECTS:XdgUtilsDesktopEntryAST>"
    "$<TARGET_OBJECTS:XdgUtilsDesktopEntryReader>"
)

add_gtest(TestXdgUtilsDesktopEntryReader "${srcs}")
target_include_directories(TestXdgUtilsDesktopEntryReader PRIVATE ${PROJECT_SOURCE_DIR}/src/DesktopEntry)
