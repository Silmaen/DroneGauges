#
# CMAKE QT configuration
#
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(DG_QT_LIBS Core Gui Widgets)
if (NOT DG_QT_VERSION)
    set(DG_QT_VERSION 6)
endif()
if (NOT DG_QT_PREFIX_PATH)
    set(DG_QT_PREFIX_PATH "C:/msys64/mingw64/share/qt${DG_QT_VERSION}")
endif()

set(CMAKE_PREFIX_PATH ${DG_QT_PREFIX_PATH})

find_package(Qt${DG_QT_VERSION} COMPONENTS ${DG_QT_LIBS} REQUIRED)

function(dg_target_add_qt PROJECT_ID)
    foreach (QT_LIB ${DG_QT_LIBS})
        target_link_libraries(${PROJECT_ID} Qt::${QT_LIB})
    endforeach (QT_LIB)

    if (WIN32)
        set(DEBUG_SUFFIX)
        if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
            set(DEBUG_SUFFIX "d")
        endif ()
        set(QT_INSTALL_PATH "${DG_QT_PREFIX_PATH}")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin/Qt${DG_QT_VERSION}Core${DEBUG_SUFFIX}.dll")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            if (NOT EXISTS "${QT_INSTALL_PATH}/bin/Qt${DG_QT_VERSION}Core${DEBUG_SUFFIX}.dll")
                set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            endif ()
        endif ()
        if (EXISTS "${DG_QT_PREFIX_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms/")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${DG_QT_PREFIX_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms/")
        endif ()
        foreach (QT_LIB ${DG_QT_LIBS})
            add_custom_command(TARGET ${PROJECT_ID} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/Qt${DG_QT_VERSION}${QT_LIB}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
        endforeach (QT_LIB)
    endif ()
endfunction()