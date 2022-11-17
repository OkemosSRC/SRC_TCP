cmake_minimum_required(VERSION 3.22)
project(solar_tcp)

set(CMAKE_CXX_STANDARD 17)

# Tests
enable_testing()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(tests)

