#
# CMAKE QT configuration
#
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (NOT DG_QT_VERSION)
    set(DG_QT_VERSION 6)
endif ()
if (NOT DG_QT_PREFIX_PATH)
    set(DG_QT_PREFIX_PATH "C:/msys64/mingw64/share/qt${DG_QT_VERSION}")
endif ()
if (DG_QT_VERSION EQUAL 6)
    set(DG_QT_LIBS Core Gui Widgets Svg SvgWidgets)
else ()
    set(DG_QT_LIBS Core Gui Widgets Svg)
endif ()

set(CMAKE_PREFIX_PATH ${DG_QT_PREFIX_PATH})

find_package(Qt${DG_QT_VERSION} COMPONENTS ${DG_QT_LIBS} REQUIRED)

function(dg_target_add_qt PROJECT_ID)
    foreach (QT_LIB ${DG_QT_LIBS})
        target_link_libraries(${PROJECT_ID} PUBLIC Qt::${QT_LIB})
    endforeach (QT_LIB)

    if (WIN32)
        #set(DEBUG_SUFFIX)
        #if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        #    set(DEBUG_SUFFIX "d")
        #endif ()
        set(QT_INSTALL_PATH "${DG_QT_PREFIX_PATH}")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin/Qt${DG_QT_VERSION}Core${DEBUG_SUFFIX}.dll")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            if (NOT EXISTS "${QT_INSTALL_PATH}/bin/Qt${DG_QT_VERSION}Core${DEBUG_SUFFIX}.dll")
                set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
            endif ()
        endif ()
        if (EXISTS "${DG_QT_PREFIX_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
            add_custom_command(TARGET ${PROJECT_ID} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:${PROJECT_ID}>/platforms/")
            add_custom_command(TARGET ${PROJECT_ID} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${DG_QT_PREFIX_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_ID}>/platforms/")
            add_custom_command(TARGET ${PROJECT_ID} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "${CMAKE_BINARY_DIR}/platforms/")
            add_custom_command(TARGET ${PROJECT_ID} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${DG_QT_PREFIX_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                    "${CMAKE_BINARY_DIR}/platforms/")
            install(FILES ${DG_QT_PREFIX_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll
                    DESTINATION ${CMAKE_INSTALL_BINDIR}/platforms)
        else ()
            message(WARNING "file ${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll not found, execution may fail")
        endif ()
        foreach (QT_LIB ${DG_QT_LIBS})
            add_custom_command(TARGET ${PROJECT_ID} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/Qt${DG_QT_VERSION}${QT_LIB}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
            install(FILES ${QT_INSTALL_PATH}/bin/Qt${DG_QT_VERSION}${QT_LIB}${DEBUG_SUFFIX}.dll
                    DESTINATION ${CMAKE_INSTALL_BINDIR})
        endforeach (QT_LIB)
    endif ()
endfunction()