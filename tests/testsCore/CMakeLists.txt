# ----------------------------------------------------------------------------------------------------------------------
# Test Core lib

add_executable(DroneGaugesCore_UnitTest
        src/vector_test.cpp
        src/base_test.cpp
        src/CoreTestHelper.h)
target_link_libraries(DroneGaugesCore_UnitTest PRIVATE DroneGaugesCore)
# ----------------------------------------------------------------------------------------------------------------------
