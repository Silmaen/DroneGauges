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
# Core Library
set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()
include(cmake/compiler_config.cmake)
include(cmake/qt_config.cmake)
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# Core Library
add_library(DroneGaugesCore SHARED
        Source/DroneGaugesCore/include/base.h
        Source/DroneGaugesCore/src/base.cpp
        )
target_include_directories(DroneGaugesCore PUBLIC Source/DroneGaugesCore/include)
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# UI Library
add_library(DroneGaugesUi SHARED
        Source/DroneGaugesUI/include/application.h
        Source/DroneGaugesUI/src/application.cpp
        )
add_dependencies(DroneGaugesUi DroneGaugesCore)
target_include_directories(DroneGaugesUi PUBLIC Source/DroneGaugesUi/include)
target_link_libraries(DroneGaugesUi PUBLIC DroneGaugesCore)
dg_target_add_qt(DroneGaugesUi)
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# Main executable
add_executable(DroneGauges Source/main.cpp)
add_dependencies(DroneGauges DroneGaugesUi)
target_include_directories(DroneGauges PUBLIC Source/DroneGaugesUI/include)
target_link_libraries(DroneGauges PUBLIC DroneGaugesUi)
# ----------------------------------------------------------------------------------------------------------------------
