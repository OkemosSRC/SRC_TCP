if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_library(solar_tcp_lib STATIC src_tcp.cpp src_tcp.h crc/CRC.h)

add_executable(solar_tcp main.cpp)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_link_libraries(solar_tcp solar_tcp_lib)
else ()
    target_link_libraries(solar_tcp optimized solar_tcp_lib)
endif ()
