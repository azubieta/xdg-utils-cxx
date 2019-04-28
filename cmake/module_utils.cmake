function(add_xdgutils_module name srcs)
    if(XDG_UTILS_SHARED)
        message("Creating ${name} as SHARED library")
        add_library(${name} SHARED ${srcs})
    else()
        message("-- Creating module target: ${name} STATIC")
        add_library(${name} STATIC ${srcs})
    endif()

    message("-- Creating module target alias: ${PROJECT_NAME}::${name}")
    add_library(${PROJECT_NAME}::${name} ALIAS ${name})

    # Configure target properties
    target_include_directories(
        ${name}
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC $<BUILD_INTERFACE:${PROJECT_INCLUDEDIR}>
        PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    set_target_properties(
        ${name} PROPERTIES
        PREFIX "lib${PROJECT_NAME}"
        PUBLIC INTERFACE_LINK_DIRECTORIES $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        PUBLIC INTERFACE_LINK_DIRECTORIES $<INSTALL_INTERFACE:${PROJECT_INSTALL_LIBDIR}>
    )
endfunction()

##
# Install module resources
##
SET(PROJECT_INSTALL_LIBS "" CACHE INTERNAL "Libs binaries")
function(install_xdgutils_module name)
    # Install binaries
    install(
        TARGETS ${name}
        EXPORT ${name}
        LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR} COMPONENT ${name}
        ARCHIVE DESTINATION ${PROJECT_INSTALL_LIBDIR} COMPONENT ${name}
    )

    # Install library headers
    install(
        DIRECTORY ${PROJECT_INCLUDEDIR}/${PROJECT_NAME}/${name}
        DESTINATION ${PROJECT_INSTALL_INCLUDEDIR}
        COMPONENT ${name}
    )

    # Build cmake target config files
    export(EXPORT ${name} NAMESPACE ${PROJECT_NAME}::)

    # Install cmake target config files
    install(
        EXPORT ${name}
        FILE "${PROJECT_NAME}${name}.cmake"
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${PROJECT_INSTALL_CMAKEDIR}
        COMPONENT ${name}
    )

    # Register library
    SET(PROJECT_INSTALL_LIBS ${PROJECT_INSTALL_LIBS} "${PROJECT_NAME}${name}" CACHE INTERNAL "Libs binaries")
endfunction()
