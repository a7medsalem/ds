#1 define minimum version
cmake_minimum_required(VERSION 3.0)
#.
set(this ds++)

#2 define project
project(${this} VERSION 1.0)

#. declear some variables
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#. testing
enable_testing()
add_subdirectory(googletest)

#3 bring the headers, such as *.h into the project
include_directories(include)

#. define headers
file(GLOB HEADERS "include/*.h")
#4 define all *.cpp files in src folder as SOURCES
file(GLOB SOURCES "src/*.cpp")

#5 add as library
add_library(${this} STATIC ${SOURCES} ${HEADERS})

#. add test sub_directory
add_subdirectory(tests)