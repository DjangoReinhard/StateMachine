cmake_minimum_required(VERSION 3.14)

project(PluginB LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
             Widgets
             LinguistTools
             )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
             Widgets
             LinguistTools
             )

set(TS_FILES PluginB_de_DE.ts)

add_library(PluginB MODULE
            PluginB_glob.h
            PluginB.h
            PluginB.cpp
            XIcons.qrc
            ${TS_FILES}
            )
target_link_libraries(PluginB
                      PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                      PRIVATE Common
                      )
target_include_directories(PluginB
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )
target_compile_definitions(PluginB
                           PRIVATE PLUGINB_LIBRARY
                           )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()
