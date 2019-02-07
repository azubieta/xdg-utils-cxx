include(cmake/EnableGoogleTest.cmake)

if(XDG_UTILS_DESKTOP_ENTRY)
    add_subdirectory(DesktopEntry)
endif()

if(XDG_UTILS_BASE_DIR)
    add_subdirectory(BaseDir)
endif()

if(XDG_UTILS_CODE_COVERAGE)
    set(COVERAGE_LCOV_EXCLUDES '${PROJECT_SOURCE_DIR}/tests/*' '${PROJECT_SOURCE_DIR}/*build*' '/usr/*')
    SETUP_TARGET_FOR_COVERAGE_GCOVR_XML(
        NAME code_coverage_report
        EXECUTABLE ctest -V -j ${PROCESSOR_COUNT}
    )
endif()
