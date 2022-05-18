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

include(CMakeDependentOption)           # This is a really useful scripts that creates options that depends on other options. It can even be used with generator expressions !
include(GNUInstallDirs)                 # This will define the default values for installation directories (all platforms even if named GNU)
include(InstallRequiredSystemLibraries) # Tell CMake that the `install` target needs to install required system libraries (eg: Windows SDK)
include(CMakePackageConfigHelpers)      # Helper to create relocatable packages

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake") # Make our cmake scripts available

include(compiler_config)
include(qt_config)
include(coverage_utils)

# It is always easier to navigate in an IDE when projects are organized in folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
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
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# Documentation
add_subdirectory(documentation)
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# Test
add_subdirectory(tests)
# ----------------------------------------------------------------------------------------------------------------------

