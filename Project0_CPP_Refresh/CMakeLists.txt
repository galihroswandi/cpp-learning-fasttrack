cmake_minimum_required(VERSION 3.10)
project(Project0_CPP_Refresh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Program 1: Memory Management
add_executable(01_memory src/01_Memory_Management.cpp)

# Program 2: OOP Classes
add_executable(02_oop src/02_OOP_Classes.cpp)

# Program 3: STL Containers
add_executable(03_stl src/03_STL_Containers.cpp)

# Program 4: File I/O
add_executable(04_fileio src/04_File_IO.cpp)

# Program 5: Exception Handling
add_executable(05_exceptions src/05_Exception_Handling.cpp)

# Program 6: Modern C++
add_executable(06_modern src/06_Modern_CPP.cpp)
