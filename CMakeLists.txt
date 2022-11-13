cmake_minimum_required(VERSION 3.22)
project(solar_tcp)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_library(solar_tcp_lib STATIC library.cpp library.h CRC.h)

add_executable(solar_tcp main.cpp)

target_link_libraries(solar_tcp optimized solar_tcp_lib)
