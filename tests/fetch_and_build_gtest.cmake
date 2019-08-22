find_package(GTest)
# Fetch and build GoogleTest if not present in the system
if(NOT TARGET GTest::GTest)
    include(ExternalProject)
    externalproject_add(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
        GIT_SHALLOW On
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
        BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/googletest-build"
        INSTALL_COMMAND ""
        TEST_COMMAND ""
    )

    externalproject_get_property(googletest SOURCE_DIR)
    externalproject_get_property(googletest BINARY_DIR)

    # Workaround fro https://cmake.org/Bug/view.php?id=15052
    file(MAKE_DIRECTORY "${SOURCE_DIR}/googletest/include/")

    add_library(GTest::GTest UNKNOWN IMPORTED)
    add_library(GTest::Main UNKNOWN IMPORTED)
    set_target_properties(
        GTest::GTest PROPERTIES
        IMPORTED_LOCATION ${BINARY_DIR}/lib/libgtest.a
        INTERFACE_INCLUDE_DIRECTORIES "${SOURCE_DIR}/googletest/include/"
        INTERFACE_LINK_LIBRARIES pthread
    )

    set_target_properties(
        GTest::Main PROPERTIES
        IMPORTED_LOCATION ${BINARY_DIR}/lib/libgtest_main.a
        INTERFACE_INCLUDE_DIRECTORIES "${SOURCE_DIR}/googletest/include/"
        INTERFACE_LINK_LIBRARIES pthread
    )

    add_dependencies(GTest::GTest googletest)
    add_dependencies(GTest::Main googletest)
endif()

include(GoogleTest)
