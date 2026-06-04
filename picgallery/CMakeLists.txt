cmake_minimum_required(VERSION 3.16)
project(picgallery VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH "/home/galih/Qt/6.5.3/gcc_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES i18n/picgallery_id.ts)

add_executable(picgallery
    main.cpp
    mainwindow.h
    fullview.h
    resources.qrc
)

qt_add_translations(picgallery TS_FILES ${TS_FILES})

target_link_libraries(picgallery PRIVATE Qt6::Widgets)
