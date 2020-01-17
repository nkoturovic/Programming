cmake_minimum_required(VERSION 3.5)

project(04_QtConcurrent LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(Qt5Concurrent)

add_executable(04_QtConcurrent.out
  main.cpp
)
target_link_libraries(04_QtConcurrent.out Qt5::Core Qt5::Concurrent)
