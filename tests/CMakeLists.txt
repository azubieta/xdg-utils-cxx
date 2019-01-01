if(XDG_UTILS_TESTS)
    enable_testing()

    find_package(GTest REQUIRED)
    include(GoogleTest)

    add_subdirectory(DesktopEntry)
endif()
