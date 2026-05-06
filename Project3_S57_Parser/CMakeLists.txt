cmake_minimum_required(VERSION 3.16)
project(Project3_S57_Parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(S57ParserApp
    src/main.cpp
    src/S57Parser.cpp
)

add_executable(GenerateS57Sample
    src/GenerateSampleData.cpp
    src/S57Parser.cpp
)

target_include_directories(S57ParserApp PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(GenerateS57Sample PRIVATE ${CMAKE_SOURCE_DIR}/include)
