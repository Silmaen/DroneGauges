cmake_minimum_required(VERSION 3.22)

set(PRJPREFIX DG)
set(PRJPREFIX_LOWER dg)

set(${PRJPREFIX}_PROJECT DroneGauges)


project(${${PRJPREFIX}_PROJECT} CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(compiler_config)
include(qt_config)

# Main Applicvation
file(GLOB_RECURSE DG_SOURCE_FILES Source/main.cpp)
add_executable(${${PRJPREFIX}_PROJECT} ${DG_SOURCE_FILES})

# UI lib
file(GLOB_RECURSE ${PRJPREFIX}_SOURCE_FILES_UI Source/${${PRJPREFIX}_PROJECT}UI/*)
add_library(${${PRJPREFIX}_PROJECT}_ui SHARED ${${PRJPREFIX}_SOURCE_FILES_UI})
add_dependencies(${${PRJPREFIX}_PROJECT} ${${PRJPREFIX}_PROJECT}_ui)
dg_target_add_qt(${${PRJPREFIX}_PROJECT}_ui)
target_include_directories(${${PRJPREFIX}_PROJECT}_ui PUBLIC Source/${${PRJPREFIX}_PROJECT}UI/include)

# core Lib
file(GLOB_RECURSE DG_SOURCE_FILES_CORE Source/${${PRJPREFIX}_PROJECT}Core/*.cpp)

add_library(${${PRJPREFIX}_PROJECT}_core SHARED ${${PRJPREFIX}_SOURCE_FILES_CORE})
target_include_directories(${${PRJPREFIX}_PROJECT}_core PUBLIC Source/${${PRJPREFIX}_PROJECT}Core/include)
add_dependencies(${${PRJPREFIX}_PROJECT}_ui ${${PRJPREFIX}_PROJECT}_core)


