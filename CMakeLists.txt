cmake_minimum_required(VERSION 3.22)
project(solar_tcp)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_library(solar_tcp_lib STATIC src/src_tcp.cpp src/src_tcp.h src/crc/CRC.h)

add_executable(solar_tcp src/main.cpp)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_link_libraries(solar_tcp solar_tcp_lib)
else ()
    target_link_libraries(solar_tcp optimized solar_tcp_lib)
endif ()