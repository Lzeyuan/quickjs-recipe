cmake_minimum_required(VERSION 3.10)

project(03_ts_module VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(3rd)

set(APP_MAIN main_app)
add_executable(${APP_MAIN})
target_sources(${APP_MAIN} PRIVATE
    main.cpp
)
target_link_libraries(${APP_MAIN} PRIVATE qjs)
