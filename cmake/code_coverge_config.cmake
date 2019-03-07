if(XDG_UTILS_CODE_COVERAGE)
    include(${CMAKE_CURRENT_LIST_DIR}/code_coverage_utils.cmake)
    append_coverage_compiler_flags()
endif()
