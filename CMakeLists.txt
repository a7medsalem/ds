#1 define minimum version
cmake_minimum_required(VERSION 3.0.0)

#2 define project
project(ds++ VERSION 1.0.0)

#. declear some variables
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#3 bring the headers, such as *.h into the project
include_directories(include)

#4 define all *.cpp files in src folder as SOURCES
file(GLOB SOURCES "src/*.cpp")

#5 add the executable
add_executable("${PROJECT_NAME}" src/main.cpp)