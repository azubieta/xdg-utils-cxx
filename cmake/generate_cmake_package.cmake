include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/package/cmake/XdgUtilsConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/XdgUtilsConfig.cmake"
    INSTALL_DESTINATION ${PROJECT_INSTALL_CMAKEDIR}
    PATH_VARS PROJECT_INSTALL_LIBDIR PROJECT_INSTALL_INCLUDEDIR
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/XdgUtilsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/XdgUtilsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/XdgUtilsConfigVersion.cmake"
    DESTINATION ${PROJECT_INSTALL_CMAKEDIR}
    COMPONENT ${PROJECT_COMPONENT_DEVEL}
)

