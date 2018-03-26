cmake_minimum_required(VERSION 3.9)
project(testing01)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("external")

add_executable(testing01 main.cpp)
target_link_libraries(testing01 PUBLIC gbench)
