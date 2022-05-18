# ----------------------------------------------------------------------------------------------------------------------
# Core Library
#
# define the library as Shared
add_library(DroneGaugesCore SHARED
        include/base.h
        include/Vector.h
        src/base.cpp
        src/Vector.cpp )
#
# Public includes: apply to this projet AND to the dependent ones
target_include_directories(DroneGaugesCore PUBLIC include)
# Interface includes: apply to the dependent ones only
target_include_directories(DroneGaugesCore INTERFACE interface)
# Private includes: apply to this project only
target_include_directories(DroneGaugesCore PRIVATE includePrivate)
#
# ----------------------------------------------------------------------------------------------------------------------
