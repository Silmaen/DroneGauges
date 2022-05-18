# ----------------------------------------------------------------------------------------------------------------------
# Test
enable_test_report()
#
#
add_subdirectory(testsCore)
target_add_test_report(DroneGaugesCore_UnitTest)
add_subdirectory(testsUI)
#target_add_test_report(DroneGaugesUi_UnitTest)
#
# coverage
test_report_finalization()
# ----------------------------------------------------------------------------------------------------------------------
