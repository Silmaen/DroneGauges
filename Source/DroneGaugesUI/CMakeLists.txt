# ----------------------------------------------------------------------------------------------------------------------
# UI Library
#
# define the library as Shared
add_library(DroneGaugesUi SHARED
        include/application.h
        src/application.cpp
        )
#
# add dependency to the core lib
add_dependencies(DroneGaugesUi DroneGaugesCore)

# Public includes: apply to this projet AND to the dependent ones
target_include_directories(DroneGaugesUi PUBLIC include)
# Interface includes: apply to the dependent ones only
target_include_directories(DroneGaugesUi INTERFACE interface)
# Private includes: apply to this project only
target_include_directories(DroneGaugesUi PRIVATE includePrivate)

# need to link to the core library (do not propagate to dependent ones)
target_link_libraries(DroneGaugesUi PRIVATE DroneGaugesCore)
# adding the support for QT
dg_target_add_qt(DroneGaugesUi)
# ----------------------------------------------------------------------------------------------------------------------