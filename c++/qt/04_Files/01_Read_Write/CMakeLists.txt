cmake_minimum_required(VERSION 3.5)

project(Read_Write LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

# Adding input file and marking it read only
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input_file.txt
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(Read_Write.out
  main.cpp
)
target_link_libraries(Read_Write.out Qt5::Core)
