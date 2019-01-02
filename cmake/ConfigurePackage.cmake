include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/XdgUtilsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_file(cmake/XdgUtilsConfig.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/XdgUtilsConfig.cmake" @ONLY)

set(ConfigPackageLocation ${XDG_UTILS_CMAKE_DIR})

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/XdgUtilsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/XdgUtilsConfigVersion.cmake"
    DESTINATION ${ConfigPackageLocation} COMPONENT Devel
)
