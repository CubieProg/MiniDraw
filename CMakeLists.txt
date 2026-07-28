cmake_minimum_required(VERSION 4.2)
project(MiniDraw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_options(/utf-8)
#add_custom_command(
#        OUTPUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/testIcon.ico"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "${CMAKE_SOURCE_DIR}/resources/testIcon.ico"
#        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/testIcon.ico"
#        DEPENDS "${CMAKE_SOURCE_DIR}/resources/testIcon.ico"
#)
#
#add_custom_target(copy_icon ALL DEPENDS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/testIcon.ico")


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)

find_package(RapidJSON CONFIG REQUIRED)

qt_standard_project_setup()


add_executable(MiniDraw main.cpp Widgets/mainwindow.ui
        Widgets/MainWindow.cpp
        Widgets/MainWindow.h
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


target_link_libraries(MiniDraw
        Qt::Core
        Qt::Gui
        Qt::Widgets
        RapidJSON
)

#install(TARGETS MiniDraw
#        BUNDLE  DESTINATION .
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)

install(TARGETS ${PROJECT_NAME}
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


qt_generate_deploy_app_script(
        TARGET ${PROJECT_NAME}
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})



if(WIN32)

    target_sources(MiniDraw PRIVATE
            "${CMAKE_SOURCE_DIR}/icon.rc"
    )

#    target_sources(MiniDraw PRIVATE
#        "${CMAKE_SOURCE_DIR}/resources/testIcon.ico"
#    )
#
#    add_custom_command(
#        TARGET MiniDraw POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "${CMAKE_SOURCE_DIR}/resources/testIcon.ico"
#        "$<TARGET_FILE_DIR:MiniDraw>/testIcon.ico"
#        COMMENT "Copying testIcon.ico to output directory"
#    )

    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
    # Если используете MSVC, может понадобиться дополнительно указать точку входа
    if(MSVC)
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
    endif()
endif()

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