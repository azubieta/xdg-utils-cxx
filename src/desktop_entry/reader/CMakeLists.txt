add_library(
    DesktopEntryReader OBJECT

    Lexer.cpp
    Token.cpp
    Tokenizer.cpp
    Reader.cpp
    Errors.h)

target_include_directories(DesktopEntryReader PRIVATE "${PROJECT_SOURCE_DIR}/src/desktop_entry")
