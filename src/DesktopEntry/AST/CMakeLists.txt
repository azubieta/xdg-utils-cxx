set(srcs AST.cpp Group.cpp Entry.cpp Comment.cpp Node.cpp)

add_library(XdgUtilsDesktopEntryAST OBJECT ${srcs})
target_include_directories(XdgUtilsDesktopEntryAST PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
