project(XdgUtilsDesktopEntry)

add_subdirectory(AST)
add_subdirectory(Reader)

add_library(
    ${PROJECT_NAME} STATIC

    DesktopEntry.cpp

    $<TARGET_OBJECTS:XdgUtilsDesktopEntryAST>
    $<TARGET_OBJECTS:XdgUtilsDesktopEntryReader>
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>

    PUBLIC
    $<BUILD_INTERFACE:${XdgUtils_SOURCE_DIR}/include/XdgUtils/DesktopEntry>
    $<INSTALL_INTERFACE:include/XdgUtils/DesktopEntry>  # <prefix>/include/XdgUtils
)

add_library(XdgUtils::DesktopEntry ALIAS ${PROJECT_NAME})
