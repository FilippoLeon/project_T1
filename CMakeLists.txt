cmake_minimum_required(VERSION 3.9)
project(testing01)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "Build path: ${CMAKE_CURRENT_BINARY_DIR}")

enable_testing()

add_subdirectory("src")
add_subdirectory("external")
add_subdirectory("tests")

add_executable(testing01 main.cpp) 
target_link_libraries(testing01 PUBLIC gbench projectT1)

 