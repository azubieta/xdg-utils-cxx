SET(PROJECT_TESTS_TARGETS "" CACHE INTERNAL "Available tests targets")

function(add_gtest name srcs)
    add_executable(${name} ${srcs})
    target_link_libraries(${name} GTest::GTest GTest::Main)

    if(${CMAKE_VERSION} VERSION_LESS "3.10.0")
        add_test(${name} ${name})
    else()
        gtest_discover_tests(${name})
    endif()

    SET(PROJECT_TESTS_TARGETS ${PROJECT_TESTS_TARGETS} "${name}" CACHE INTERNAL "Available tests targets")
endfunction()
