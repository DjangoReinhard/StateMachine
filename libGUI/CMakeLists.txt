cmake_minimum_required(VERSION 3.14)

project(GUI LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
             Core
             Gui
             Widgets
             LinguistTools
             )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
             Core
             Gui
             Widgets
             LinguistTools
             )

set(TS_FILES GUI_de_DE.ts)

add_library(GUI STATIC
            ActionButton.h
            ActionButton.cpp
            ToolBar.h
            ToolBar.cpp
            ToolBar.ui
            ${TS_FILES}
            )
target_link_libraries(GUI
                      PRIVATE Qt${QT_VERSION_MAJOR}::Core
                      PRIVATE Qt${QT_VERSION_MAJOR}::Gui
                      PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                      )
target_include_directories(GUI
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()
