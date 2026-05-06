cmake_minimum_required(VERSION 3.16)
project(Project1_Qt_Basics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)

# Portable Qt (Qt6 or Qt5)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(QtBasicsApp
    src/main.cpp
    src/MainWindow.cpp
)

target_include_directories(QtBasicsApp PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(QtBasicsApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
