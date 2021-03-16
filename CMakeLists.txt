
cmake_minimum_required(VERSION 3.0)

project(tibere)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED Widgets Core Gui)

add_subdirectory(src)

