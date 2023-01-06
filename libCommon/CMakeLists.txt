cmake_minimum_required(VERSION 3.14)

project(Common LANGUAGES CXX)

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

set(TS_FILES Common_de_DE.ts)

add_library(Common SHARED
            Common_glob.h
            IApplicationPage.h
            MultiStateAction.h
            MultiStateAction.cpp
            ${TS_FILES}
            )
target_link_libraries(Common
                      PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                      )
target_include_directories(Common
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )
target_compile_definitions(Common
                           PRIVATE COMMON_LIBRARY
                           )
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()
