#1 define minimum version
cmake_minimum_required(VERSION 3.0)

#.
set(this dc++_tests)

#. define all *.cpp files in src folder as SOURCES
file(GLOB SOURCES "*.cpp")

#.
add_executable(${this} ${SOURCES})

#.
target_link_libraries(${this} PUBLIC gtest_main ds++)

#.
#add_test(NAME ${this} COMMAND ${this})
#add_test(NAME ${this} COMMAND ${this} "--gtest_filter=_ArrayListTests.*")
add_test(NAME ${this} COMMAND ${this} "--gtest_filter=_LinkedListTests.*")