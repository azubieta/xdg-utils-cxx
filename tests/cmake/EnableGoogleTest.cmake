# Fetch and build GoogleTest if not present in the system
if(NOT TARGET GTest)
    # Download and unpack googletest at configure time
    configure_file(cmake/GTestRemoteCMakeLists.txt.in ${CMAKE_CURRENT_BINARY_DIR}/googletest/remote/CMakeLists.txt)
    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googletest/remote")
    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googletest/remote")

    set(GTEST_ROOT ${CMAKE_BINARY_DIR}/googletest)
    find_package(GTest REQUIRED)
endif()

include(GoogleTest)
