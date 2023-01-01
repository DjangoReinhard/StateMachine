cmake_minimum_required(VERSION 3.5)

project(BasicsTests LANGUAGES CXX)
project(ChildTests LANGUAGES CXX)
project(HistoryTests LANGUAGES CXX)
project(OrphanTests LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
             Test
             )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
             Test
             )
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BasicsTests
               BasicsTests.cpp
               )
add_test(NAME BasicsTests COMMAND BasicsTests)
target_include_directories(BasicsTests PRIVATE ../libStateMachine)
target_link_libraries(BasicsTests
                      PRIVATE Qt${QT_VERSION_MAJOR}::Test
                      PRIVATE StateMachine
                      )

add_executable(ChildTests
               ChildTests.cpp
               )
add_test(NAME ChildTests COMMAND ChildTests)
target_include_directories(ChildTests PRIVATE ../libStateMachine)
target_link_libraries(ChildTests
                      PRIVATE Qt${QT_VERSION_MAJOR}::Test
                      PRIVATE StateMachine
                      )

add_executable(HistoryTests
               HistoryTests.cpp
               )
add_test(NAME HistoryTests COMMAND HistoryTests)
target_include_directories(HistoryTests PRIVATE ../libStateMachine)
target_link_libraries(HistoryTests
                      PRIVATE Qt${QT_VERSION_MAJOR}::Test
                      PRIVATE StateMachine
                      )

add_executable(OrphanTests
               OrphanTests.cpp
               )
add_test(NAME OrphanTests COMMAND OrphanTests)
target_include_directories(OrphanTests PRIVATE ../libStateMachine)
target_link_libraries(OrphanTests
                      PRIVATE Qt${QT_VERSION_MAJOR}::Test
                      PRIVATE StateMachine
                      )


