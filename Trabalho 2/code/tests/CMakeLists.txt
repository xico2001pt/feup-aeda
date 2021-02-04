project(tests)

add_subdirectory(gtest-lib)
include_directories(gtest-lib/googletest/include)
include_directories(gtest-lib/googlemock/include)


add_executable(Google_Tests_run admin-tests.cpp archive-tests.cpp date-tests.cpp platform-tests.cpp stream-tests.cpp user-tests.cpp input-tests.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main ${CMAKE_PROJECT_NAME}_lib)