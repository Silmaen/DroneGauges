#
# coverage helper functions
#
function(enable_test_report)
    message(STATUS "** Fetching Google test")
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.11.0
    )
    set(BUILD_GMOCK OFF)
    set(INSTALL_GTEST OFF)
    FetchContent_MakeAvailable(googletest)
    add_library(GTest::GTest INTERFACE IMPORTED)
    target_link_libraries(GTest::GTest INTERFACE gtest_main)
    if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
        target_compile_options(gtest PUBLIC
                -Wno-undef
                -Wno-reserved-identifier
                -Wno-padded
                -Wno-c++98-compat-pedantic
                -Wno-used-but-marked-unused
                -Wno-suggest-destructor-override
                -Wno-suggest-override
                -Wno-global-constructors
                -Wno-exit-time-destructors
                -Wno-zero-as-null-pointer-constant
                -Wno-switch-enum
                -Wno-missing-noreturn
                -Wno-covered-switch-default
                -Wno-weak-vtables
                -Wno-unused-member-function
                )
        target_compile_options(gtest_main PUBLIC
                -Wno-undef
                -Wno-reserved-identifier
                -Wno-padded
                -Wno-c++98-compat-pedantic
                -Wno-used-but-marked-unused
                -Wno-suggest-destructor-override
                -Wno-suggest-override
                -Wno-global-constructors
                -Wno-exit-time-destructors
                -Wno-zero-as-null-pointer-constant
                -Wno-switch-enum
                -Wno-missing-noreturn
                -Wno-covered-switch-default
                -Wno-weak-vtables
                -Wno-unused-member-function
                )
    elseif (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
        target_compile_options(gtest PRIVATE
                -Wno-deprecated
                )
    endif ()

    enable_testing()
    add_custom_target(Generate_test_report)
    if (NOT CMAKE_BUILD_TYPE MATCHES "Debug")
        return()
    endif ()
    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        return()
    endif ()
    find_program(GCOVR gcovr)
    if (${GCOVR} STREQUAL GCOVR-NOTFOUND)
        message(WARNING "unable to find gcovr: no coverage report is possible")
    else ()
        # Get gcov version
        execute_process(COMMAND ${GCOVR} --version
                OUTPUT_VARIABLE GCOVR_VERSION)
        string(REPLACE "\n" ";" GCOVR_VERSION ${GCOVR_VERSION})
        list(SUBLIST GCOVR_VERSION 0 1 GCOVR_VERSION)
        string(REPLACE " " ";" GCOVR_VERSION ${GCOVR_VERSION})
        list(SUBLIST GCOVR_VERSION 1 1 GCOVR_VERSION)

        message(STATUS "Found gcovr version ${GCOVR_VERSION} at location: ${GCOVR} ")
        if (${GCOVR_VERSION} VERSION_LESS 5.0)
            message(FATAL_ERROR "gcovr: Too old version of gcovr, minimum required is 5.0")
        endif ()
    endif ()
    # options for coverage
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_compile_options(--coverage)
        link_libraries(gcov)
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_compile_options(--coverage)
        add_link_options(--coverage)
        get_filename_component(COMPILER_PATH ${CMAKE_CXX_COMPILER} DIRECTORY)
        set(${PRJPREFIX}_GCOV "${COMPILER_PATH}/llvm-cov gcov")
        if (WIN32)
            string(REPLACE "/" "\\\\" ${PRJPREFIX}_GCOV ${${PRJPREFIX}_GCOV})
        endif ()
    endif ()
endfunction()

#
#
function(target_add_test_report TARGET_ID)
    target_link_libraries(${TARGET_ID} PRIVATE GTest::GTest)
    add_test(${TARGET_ID} ${TARGET_ID} --gtest_output=xml:test/${TARGET_ID}_Report.xml)
    set_tests_properties(${TARGET_ID} PROPERTIES TIMEOUT 3600)
    add_dependencies(Generate_test_report ${TARGET_ID})
    add_custom_command(TARGET Generate_test_report POST_BUILD
            COMMAND ${TARGET_ID} --gtest_output=xml:test/${TARGET_ID}_Report.xml
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endfunction()
#
#
function(test_report_finalization)
    if (NOT CMAKE_BUILD_TYPE MATCHES "Debug")
        return()
    endif ()
    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        return()
    endif ()
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Coverage)
    set(COVERAGE_TITLE "Drone Gauges: Tests code coverage")
    set(COVERAGE_HTML --html --html-details --html-details-syntax-highlighting --html-title ${COVERAGE_TITLE} --source-encoding utf-8)
    set(COVERAGE_FILTER -e ".*Library/.*" -e ".*_deps/.*" -e ".*tests/.*" -e ".*autogen.*" -e ".*main\.cpp")
    set(COVERAGE_OPTION -buds -j 4 --exclude-throw-branches --exclude-unreachable-branches --exclude-lines-by-pattern ".*---UNCOVER---.*")
    if ("d${DG_GCOV}" STREQUAL "d")
        set(COVERAGE_GCOV)
    else ()
        set(COVERAGE_GCOV "--gcov-executable \"llvm-cov gcov\"" --gcov-ignore-parse-errors)
    endif ()
    add_custom_command(TARGET Generate_test_report POST_BUILD
            COMMAND ${GCOVR} ${COVERAGE_OPTION} -r ${CMAKE_SOURCE_DIR} -o ${CMAKE_BINARY_DIR}/Coverage/index.html ${COVERAGE_GCOV} ${COVERAGE_HTML} ${COVERAGE_FILTER} .
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            USES_TERMINAL)

endfunction()

