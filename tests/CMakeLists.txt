if(XDG_UTILS_TESTS)
    include(fetch_and_build_gtest.cmake)
    include(utils.cmake)

    add_subdirectory(DesktopEntry)
    add_subdirectory(BaseDir)
        
    include(setup_coverage_target.cmake)
endif()
