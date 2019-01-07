add_executable(
    TestXdgUtilsBaseDir
    TestBaseDir.cpp
)

target_include_directories(TestXdgUtilsBaseDir PRIVATE "${PROJECT_SOURCE_DIR}/src/BaseDir")
target_link_libraries(TestXdgUtilsBaseDir XdgUtils::BaseDir GTest::GTest GTest::Main)

if(${CMAKE_VERSION} VERSION_LESS "3.10.0")
    add_test(TestXdgUtilsBaseDir TestXdgUtilsBaseDir)
else()
    gtest_discover_tests(TestXdgUtilsBaseDir)
endif()


