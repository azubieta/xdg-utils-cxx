set(srcs Lexer.cpp Token.cpp Tokenizer.cpp Reader.cpp)

add_library(XdgUtilsDesktopEntryReader OBJECT ${srcs})

target_include_directories(XdgUtilsDesktopEntryReader
    PUBLIC $<BUILD_INTERFACE:${DesktopEntry_SOURCES_DIR}>
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )
if(XDG_UTILS_SHARED)
    set_property(TARGET XdgUtilsDesktopEntryReader PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()
