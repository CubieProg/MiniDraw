cmake_minimum_required(VERSION 4.2)
project(MiniDraw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_options(/utf-8)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
#        CanvasPainter
        REQUIRED)

add_executable(MiniDraw main.cpp Widgets/mainwindow.ui
        toolbar.ui
        Widgets/MainWindow.cpp
        Widgets/MainWindow.h
        ToolBar.cpp
        ToolBar.h
        Widgets/CanvasWidget.cpp
        Widgets/CanvasWidget.h
        Widgets/ColorPicker.cpp
        Widgets/ColorPicker.h
        DrawObjects/BaseDraw.cpp
        DrawObjects/BaseDraw.h
        DrawObjects/PixelObject/PixelObject.cpp
        DrawObjects/PixelObject/PixelObject.h
        DrawObjects/DrawObjectsPool.cpp
        DrawObjects/DrawObjectsPool.h
        DrawTools/Pencil/Pencil.cpp
        DrawTools/Pencil/Pencil.h
        DrawTools/BaseTool.cpp
        DrawTools/BaseTool.h
        DrawTools/Liner/Liner.cpp
        DrawTools/Liner/Liner.h
        DrawTools/CircleTool/CircleTool.cpp
        DrawTools/CircleTool/CircleTool.h
        DrawTools/ArrowTool/ArrowTool.cpp
        DrawTools/ArrowTool/ArrowTool.h
        DrawTools/RectTool/RectTool.cpp
        DrawTools/RectTool/RectTool.h
        DrawTools/TextTool/TextTool.cpp
        DrawTools/TextTool/TextTool.h
        DrawTools/ToolsContainer.cpp
        DrawTools/ToolsContainer.h
        DrawTools/SelectTool/SelectTool.cpp
        DrawTools/SelectTool/SelectTool.h
        DrawObjects/LineObject/LineObject.cpp
        DrawObjects/LineObject/LineObject.h
        DrawObjects/CircleObject/CircleObject.cpp
        DrawObjects/CircleObject/CircleObject.h
        DrawObjects/RectObject/RectObject.cpp
        DrawObjects/RectObject/RectObject.h
        DrawObjects/ArrowObject/ArrowObject.cpp
        DrawObjects/ArrowObject/ArrowObject.h
        DrawObjects/TextObject/TextObject.cpp
        DrawObjects/TextObject/TextObject.h
        Gizmos/BaseGizmo.cpp
        Gizmos/BaseGizmo.h
        Gizmos/RectGizmo.cpp
        Gizmos/RectGizmo.h
        Gizmos/DotGizmo.cpp
        Gizmos/DotGizmo.h
        Gizmos/LineGizmo.cpp
        Gizmos/LineGizmo.h
        QtUtils/QtUtils.h
)

find_package(Qt6 CONFIG REQUIRED)
#target_link_libraries(MiniDraw PRIVATE DB2::DB2 PPS::PPS Oracle::OCI Libb2::Libb2)


target_link_libraries(MiniDraw
        Qt::Core
        Qt::Gui
        Qt::Widgets
#        Qt::CanvasPainter
)


if (EXISTS "C:/Users/spp16/.vcpkg-clion/vcpkg/installed/x64-windows/Qt6/plugins/platforms/qwindows.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "C:/Users/spp16/.vcpkg-clion/vcpkg/installed/x64-windows/Qt6/plugins/platforms/qwindows.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
endif ()
foreach (QT_LIB Core Gui Widgets)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "C:/Users/spp16/.vcpkg-clion/vcpkg/installed/x64-windows/bin/Qt6${QT_LIB}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endforeach (QT_LIB)


#if (WIN32)
#    set(DEBUG_SUFFIX)
#    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
#        set(DEBUG_SUFFIX "d")
#    endif ()
#    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
#    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
#        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
#        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
#            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
#        endif ()
#    endif ()
#    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E make_directory
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
#    endif ()
#    foreach (QT_LIB Core Gui Widgets)
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
#    endforeach (QT_LIB)
#endif ()


#if(WIN32 AND TARGET MiniDraw)
#    find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt PATHS "C:/Users/spp16/Qt6.5.3-Windows-x86_64-VS2019-16.11.37/bin")
#    if(WINDEPLOYQT_EXECUTABLE)
#        add_custom_command(TARGET MiniDraw POST_BUILD
#                COMMAND "${WINDEPLOYQT_EXECUTABLE}"
#                "--no-compiler-runtime"
#                "$<TARGET_FILE:MiniDraw>"
#                COMMENT "Running windeployqt to deploy Qt dependencies..."
#        )
#    else()
#        message(WARNING "windeployqt not found. You may need to run it manually.")
#    endif()
#endif()
