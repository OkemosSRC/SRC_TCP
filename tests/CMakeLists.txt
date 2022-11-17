include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# run until first failure
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} $<CONFIG> --repeat-until-fail 100 --output-on-failure)
# add_executable(src_test src_test.cpp)
add_executable(case_test case_test.cpp)
add_executable(create_packet_test create_packet_test.cpp)
add_executable(header_seq_test header_seq_test.cpp)
add_executable(hex_test hex_test.cpp)
add_executable(raw_data_test raw_data_test.cpp)
add_executable(packet_header_test packet_header_test.cpp)
add_executable(create_solar_test create_solar_test.cpp)


target_link_libraries(case_test
        PRIVATE
        GTest::GTest
        solar_tcp_lib)

target_link_libraries(create_packet_test
        PRIVATE
        GTest::GTest
        solar_tcp_lib)

target_link_libraries(header_seq_test
        PRIVATE
        GTest::GTest
        solar_tcp_lib)

target_link_libraries(hex_test
        PRIVATE
        GTest::GTest
        solar_tcp_lib)

target_link_libraries(raw_data_test
        PRIVATE
        GTest::GTest
        solar_tcp_lib)

target_link_libraries(packet_header_test
        PRIVATE
        GTest::GTest
        solar_tcp_lib)

target_link_libraries(create_solar_test
        PRIVATE
        GTest::GTest
        solar_tcp_lib)

add_test(NAME case_test COMMAND case_test)
add_test(NAME create_packet_test COMMAND create_packet_test)
add_test(NAME header_seq_test COMMAND header_seq_test)
add_test(NAME hex_test COMMAND hex_test)
add_test(NAME raw_data_test COMMAND raw_data_test)
add_test(NAME packet_header_test COMMAND packet_header_test)
add_test(NAME create_solar_test COMMAND create_solar_test)
