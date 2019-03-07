set(
    srcs

    TestAST.cpp
    TestEntry.cpp
    TestComment.cpp
    TestGroup.cpp
    "$<TARGET_OBJECTS:XdgUtilsDesktopEntryAST>"
)

add_gtest(TestXdgUtilsDesktopAST "${srcs}")
target_include_directories(TestXdgUtilsDesktopAST PRIVATE ${PROJECT_SOURCE_DIR}/src/DesktopEntry/AST)
