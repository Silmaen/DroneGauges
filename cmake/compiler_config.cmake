#
# Compiler definition
#
set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif ()
# ----------------------------------------------------------------------------------------------------------------------
# OS helper variables
cmake_host_system_information(RESULT DG_PLATFORM_RELEASE QUERY OS_RELEASE)
cmake_host_system_information(RESULT DG_PLATFORM_VERSION QUERY OS_VERSION)

# Trimming potential leading & trailing space characters (happens for Windows' values)
string(STRIP ${DG_PLATFORM_RELEASE} DG_PLATFORM_RELEASE)
string(STRIP ${DG_PLATFORM_VERSION} DG_PLATFORM_VERSION)

if (WIN32 OR CYGWIN)
    set(DG_PLATFORM_STR "Windows")
    set(DG_PLATFORM_WINDOWS ON)

    if (CYGWIN)
        set(DG_PLATFORM_STR "${DG_PLATFORM_STR} (Cygwin)")
        set(DG_PLATFORM_CYGWIN ON)
    endif ()
    set(DG_LIB_TYPE STATIC)
elseif (UNIX)
    set(DG_PLATFORM_STR "Linux")
    set(DG_PLATFORM_LINUX ON)
    set(DG_LIB_TYPE SHARED)
endif ()
# ----------------------------------------------------------------------------------------------------------------------
# default compiler
if (NOT DG_COMPILER)
    if (MSVC)
        if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            set(DG_COMPILER clang-cl)
        else ()
            set(DG_COMPILER msvc)
        endif ()
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(DG_COMPILER clang)
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(DG_COMPILER gcc)
    else ()
        message(ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
        set(DG_COMPILER "unsupported compiler")
    endif ()
endif ()
message(STATUS "Using Compiler: ${DG_COMPILER}")
# ----------------------------------------------------------------------------------------------------------------------
# platform & architecture
if (NOT DG_ARCHITECTURE)
    set(DG_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
    if (${DG_ARCHITECTURE} MATCHES "AMD64")
        set(DG_ARCHITECTURE x64)
    endif ()
endif ()
message(STATUS "Using architecture: ${DG_ARCHITECTURE}")
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
add_compile_definitions(DG_ARCHITECTURE=${DG_ARCHITECTURE})
add_compile_definitions(DG_COMPILER=${DG_COMPILER})

if (${DG_COMPILER} STREQUAL gcc)
    add_compile_options(
            --coverage
            -Wall
            -Wextra
            -Wdeprecated
            -Wdeprecated-declarations
            -Wcast-align
            -Wcast-qual
            -Werror
    )
    link_libraries(gcov)
elseif (${DG_COMPILER} STREQUAL clang)
    add_compile_options(
            --coverage
            -Weverything
            -pedantic
            -pedantic-errors
            -Werror
            -Wno-c++98-compat
    )
    add_link_options(--coverage)
    get_filename_component(COMPILER_PATH ${CMAKE_CXX_COMPILER} DIRECTORY)
    set(${PRJPREFIX}_GCOV "${COMPILER_PATH}/llvm-cov gcov")
    if (WIN32)
        string(REPLACE "/" "\\\\" ${PRJPREFIX}_GCOV ${${PRJPREFIX}_GCOV})
    endif ()
elseif (${DG_COMPILER} STREQUAL clang-cl)
    add_compile_options(
            -Weverything
            -Werror
            -Wno-c++98-c++11-c++14-compat
            -Wno-c++98-compat
    )
elseif (${DG_COMPILER} STREQUAL msvc)
    add_compile_options(
            "$<$<CONFIG:Debug>:/RTC1>"
            /fp:precise /Zc:wchar_t /Zc:forScope /Zc:inline /GR
            /utf-8
            /MP
            /W4
            /WX
    )
endif ()
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
function(dg_target_add_system_lib PROJECT_ID)
    if (WIN32 AND (${DG_COMPILER} STREQUAL "gcc" OR ${DG_COMPILER} MASTREQUALTCHES "clang"))
        get_filename_component(BIN_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
        add_custom_command(TARGET ${PROJECT_ID} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${BIN_DIR}/libgcc_s_seh-1.dll"
                "$<TARGET_FILE_DIR:${PROJECT_ID}>")
        add_custom_command(TARGET ${PROJECT_ID} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${BIN_DIR}/libstdc++-6.dll"
                "$<TARGET_FILE_DIR:${PROJECT_ID}>")
    endif ()
endfunction()