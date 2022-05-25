# ----------------------------------------------------------------------------------------------------------------------
# UI Library
#
# define the library as Shared
add_library(DroneGaugesUi ${DG_LIB_TYPE}
        include/MainWindow.h
        include/gauge/PrimaryFlightDisplay.h
        includePrivate/gauge/pfd/DisplayElement.h
        includePrivate/gauge/pfd/Adi.h
        includePrivate/gauge/pfd/Alt.h
        includePrivate/gauge/pfd/Asi.h
        includePrivate/gauge/pfd/Hdg.h
        includePrivate/gauge/pfd/font.h
        includePrivate/gauge/pfd/color.h
        src/MainWindow.cpp
        src/ui/MainWindow.ui
        src/gauge/PrimaryFlightDisplay.cpp
        src/gauge/pfd//DisplayElement.cpp
        src/gauge/pfd/Adi.cpp
        src/gauge/pfd/Alt.cpp
        src/gauge/pfd/Asi.cpp
        src/gauge/pfd/Hdg.cpp
        src/gauge/pfd/font.cpp
        ../../resources/DroneGauges.qrc)
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


install(TARGETS DroneGaugesUi RUNTIME DESTINATION bin)
# ----------------------------------------------------------------------------------------------------------------------