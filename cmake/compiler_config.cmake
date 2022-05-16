#
# Compiler definition
#
# ----------------------------------------------------------------------------------------------------------------------
# OS helper variables
cmake_host_system_information(RESULT RSH_PLATFORM_RELEASE QUERY OS_RELEASE)
cmake_host_system_information(RESULT RSH_PLATFORM_VERSION QUERY OS_VERSION)

# Trimming potential leading & trailing space characters (happens for Windows' values)
string(STRIP ${RSH_PLATFORM_RELEASE} RSH_PLATFORM_RELEASE)
string(STRIP ${RSH_PLATFORM_VERSION} RSH_PLATFORM_VERSION)

if (WIN32 OR CYGWIN)
    set(RSH_PLATFORM_STR "Windows")
    set(RSH_PLATFORM_WINDOWS ON)

    if (CYGWIN)
        set(RSH_PLATFORM_STR "${RSH_PLATFORM_STR} (Cygwin)")
        set(RSH_PLATFORM_CYGWIN ON)
    endif ()
elseif (UNIX)
    set(RSH_PLATFORM_STR "Linux")
    set(RSH_PLATFORM_LINUX ON)
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
message(STATUS "Using processor: ${DG_COMPILER}")
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
if (${DG_COMPILER} MATCHES gcc)
    add_compile_options(-Wall
            -Wextra
            -Wdeprecated
            -Wdeprecated-declarations
            -Wcast-align
            -Wcast-qual
            -Werror
            )
elseif (${DG_COMPILER} MATCHES clang)
    add_compile_options(
            -Weverything
            -pedantic
            -pedantic-errors
            -Werror
            -Wno-c++98-compat
    )
elseif (${DG_COMPILER} MATCHES clang-cl)
    add_compile_options(
            -Weverything
            -Werror
    )
elseif (${DG_COMPILER} MATCHES msvc)
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
    if (WIN32 AND (${DG_COMPILER} MATCHES "gcc" OR ${DG_COMPILER} MATCHES "clang"))
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