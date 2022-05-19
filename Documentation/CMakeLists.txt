# ----------------------------------------------------------------------------------------------------------------------
# Documentation
find_package(Doxygen
        REQUIRED dot)
if (DOXYGEN_FOUND)
    message(STATUS "found doxygen version: ${DOXYGEN_VERSION}")
    if (${DOXYGEN_VERSION} VERSION_LESS 1.9.2)
        message(FATAL_ERROR "Doxygen version 1.9.2 or higher is required")
    endif ()
    add_custom_target(Documentation
            COMMAND ${DOXYGEN_EXECUTABLE}
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
            COMMENT "Generating API documentation"
            VERBATIM)
    configure_file(${PROJECT_SOURCE_DIR}/Doxyfile ${PROJECT_BINARY_DIR}/Doxyfile)
else (DOXYGEN_FOUND)
    message(FATAL_ERROR "no doxygen found")
endif (DOXYGEN_FOUND)
# ----------------------------------------------------------------------------------------------------------------------
