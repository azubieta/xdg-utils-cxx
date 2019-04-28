set(srcs AST.cpp Group.cpp Entry.cpp Comment.cpp Node.cpp)

add_library(XdgUtilsDesktopEntryAST OBJECT ${srcs})
target_include_directories(XdgUtilsDesktopEntryAST PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

if(XDG_UTILS_SHARED)
    set_property(TARGET XdgUtilsDesktopEntryAST PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()
