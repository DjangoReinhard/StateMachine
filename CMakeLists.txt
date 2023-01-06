cmake_minimum_required(VERSION 3.5)

project(AppStateMachine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
             Widgets
             Gui
             LinguistTools
             )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
             Widgets
             Gui
             LinguistTools
             )

set(TS_FILES AppStateMachine_de_DE.ts)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    MainControl.h
    MainControl.cpp
    mainwindow.ui
    AppUserEvents.h
    AppUserEvents.cpp
    ${TS_FILES}
    )
enable_testing()
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(AppStateMachine
                    MANUAL_FINALIZATION
                    ${PROJECT_SOURCES}
                    XIcons.qrc
                    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET AppStateMachine APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(AppStateMachine SHARED
                    ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(AppStateMachine
                       ${PROJECT_SOURCES}
        )
    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(AppStateMachine
                      PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                      PRIVATE Common
                      PRIVATE StateMachine
                      PRIVATE Service
                      PRIVATE GUI
                      )

set_target_properties(AppStateMachine PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


add_subdirectory(libCommon)
add_subdirectory(libGUI)
add_subdirectory(libService)
add_subdirectory(libStateMachine)
add_subdirectory(pluginA)
add_subdirectory(pluginB)
add_subdirectory(Tests)

install(TARGETS AppStateMachine Common PluginA PluginB
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AppStateMachine)
endif()
