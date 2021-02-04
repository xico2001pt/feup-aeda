cmake_minimum_required(VERSION 3.10)
project(aeda2021_p09)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(aeda2021_p09 main.cpp Tests/tests.cpp Tests/bet.cpp Tests/player.cpp)

target_link_libraries(aeda2021_p09 gtest gtest_main)
