# ----------------------------------------------------------------------------------------------------------------------
# Test Core lib

add_executable(DroneGaugesCore_UnitTest
        src/vector_test.cpp
        src/base_test.cpp
        )
target_link_libraries(DroneGaugesCore_UnitTest PRIVATE DroneGaugesCore gtest gtest_main)

add_test(DroneGaugesCore_UTests DroneGaugesCore_UnitTest --gtest_output=xml:test/DroneGaugesCore_UTests_Report.xml)
set_tests_properties(DroneGaugesCore_UTests PROPERTIES TIMEOUT 3600)
# ----------------------------------------------------------------------------------------------------------------------
