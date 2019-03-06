project(BaseDir)

add_library(
    ${PROJECT_NAME} STATIC
    BaseDir.cpp
)

set(PUBLIC_HEADERS_DIR "${XdgUtils_SOURCE_DIR}/include")

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>

    PUBLIC $<BUILD_INTERFACE:${PUBLIC_HEADERS_DIR}>
    PUBLIC $<INSTALL_INTERFACE:${XDG_UTILS_HEADER_DIR}>  # <prefix>/include/XdgUtils
)

add_library(XdgUtils::BaseDir ALIAS ${PROJECT_NAME})

# Install library headers
install(
    DIRECTORY ${PUBLIC_HEADERS_DIR}/XdgUtils/BaseDir
    DESTINATION ${XDG_UTILS_HEADER_DIR}/XdgUtils
    COMPONENT BaseDir-Dev
)

# Install library files
install(
    TARGETS ${PROJECT_NAME}
    EXPORT BaseDir
    ARCHIVE DESTINATION ${XDG_UTILS_LIB_DIR} COMPONENT BaseDir
    PUBLIC_HEADER DESTINATION ${XDG_UTILS_HEADER_DIR}/XdgUtils/BaseDir COMPONENT BaseDir-Dev
)

# Install cmake config files
install(
    EXPORT BaseDir
    NAMESPACE XdgUtils::
    DESTINATION ${XDG_UTILS_CMAKE_DIR}
    COMPONENT BaseDir-Dev
)

# Expose the target to be used without installation
export(EXPORT BaseDir NAMESPACE XdgUtils::)
