add_library(
    XdgUtilsDesktopEntryReader OBJECT

    Lexer.cpp
    Token.cpp
    Tokenizer.cpp
    Reader.cpp
    Errors.h
)

target_include_directories(XdgUtilsDesktopEntryReader PRIVATE "${PROJECT_SOURCE_DIR}")
