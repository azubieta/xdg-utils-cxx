project(DesktopEntry)

add_subdirectory(AST)
add_subdirectory(Reader)

add_library(
    ${PROJECT_NAME} STATIC

    DesktopEntry.cpp
    DesktopEntryKeyPath.cpp
    DesktopEntryKeyValue.cpp
    DesktopEntryExecValue.cpp
    DesktopEntryStringsValue.cpp

    $<TARGET_OBJECTS:XdgUtilsDesktopEntryAST>
    $<TARGET_OBJECTS:XdgUtilsDesktopEntryReader>
)

set(PUBLIC_HEADERS_DIR "${XdgUtils_SOURCE_DIR}/include")

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>

    PUBLIC $<BUILD_INTERFACE:${PUBLIC_HEADERS_DIR}>
    PUBLIC $<INSTALL_INTERFACE:${XDG_UTILS_HEADER_DIR}>  # <prefix>/include/XdgUtils
)

add_library(XdgUtils::DesktopEntry ALIAS ${PROJECT_NAME})

# Install library headers
install(
    DIRECTORY ${PUBLIC_HEADERS_DIR}/XdgUtils/DesktopEntry
    DESTINATION ${XDG_UTILS_HEADER_DIR}/XdgUtils
    COMPONENT BaseDir-Dev
)

# Install library files
install(
    TARGETS ${PROJECT_NAME}
    EXPORT DesktopEntry
    ARCHIVE DESTINATION ${XDG_UTILS_LIB_DIR} COMPONENT DesktopEntry
    PUBLIC_HEADER DESTINATION ${XDG_UTILS_HEADER_DIR}/XdgUtils/DesktopEntry COMPONENT DesktopEntry-Dev
)

# Install cmake config files
install(
    EXPORT DesktopEntry
    NAMESPACE XdgUtils::
    DESTINATION ${XDG_UTILS_CMAKE_DIR}
    COMPONENT DesktopEntry-Dev
)

# Expose the target to be used without installation
export(EXPORT DesktopEntry NAMESPACE XdgUtils::)
