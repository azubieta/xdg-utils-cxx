# Build variables
set(PROJECT_INCLUDEDIR ${PROJECT_SOURCE_DIR}/include)

# Install variables
set(PROJECT_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR}/XdgUtils)
set(PROJECT_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR}/XdgUtils)
set(PROJECT_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

set(PROJECT_COMPONENT ${PROJECT_NAME})
set(PROJECT_COMPONENT_DEVEL ${PROJECT_NAME})

# Modules
include(${PROJECT_SOURCE_DIR}/cmake/module_utils.cmake)

add_subdirectory(DesktopEntry)
add_subdirectory(BaseDir)

include(${PROJECT_SOURCE_DIR}/cmake/generate_cmake_package.cmake)
