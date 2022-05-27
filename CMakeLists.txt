#
# Base CMake for Drone gauges project
#
cmake_minimum_required(VERSION 3.22)

# ----------------------------------------------------------------------------------------------------------------------
# project definition
project(DroneGauges VERSION 1.0
        DESCRIPTION "Drone Telemetry gauges application"
        LANGUAGES CXX)
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# Base Definitions

include(CMakePackageConfigHelpers)      # Helper to create relocatable packages
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake") # Make our cmake scripts available

include(compiler_config)
include(qt_config)
include(coverage_utils)

# It is always easier to navigate in an IDE when projects are organized in folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# base packaging configuration
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/Install)
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# Third party
add_subdirectory(Library)
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# Core Library
add_subdirectory(Source/DroneGaugesCore)
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# UI Library
add_subdirectory(Source/DroneGaugesUi)
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# Main executable
add_executable(DroneGauges Source/main.cpp)
add_dependencies(DroneGauges DroneGaugesUi)
target_include_directories(DroneGauges PUBLIC Source/DroneGaugesUI/include)
target_link_libraries(DroneGauges PUBLIC DroneGaugesUi)
install(TARGETS DroneGauges RUNTIME DESTINATION bin)
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# Documentation
add_subdirectory(documentation)
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# Test
add_subdirectory(tests)
# ----------------------------------------------------------------------------------------------------------------------

if (WIN32)
    set(CPACK_GENERATOR ZIP)
    set(CPACK_BINARY_ZIP ON)
    set(CPACK_BINARY_NSIS OFF)
else ()
    set(CPACK_GENERATOR TGZ)
endif ()
include(CPack)

add_custom_target(Package
        COMMAND ${CMAKE_CPACK_COMMAND}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR})