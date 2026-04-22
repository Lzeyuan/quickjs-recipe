cmake_minimum_required(VERSION 3.10)

project(HelloWorld VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(3rd)

add_executable(hello main.cpp)

target_link_libraries(hello PRIVATE qjs)