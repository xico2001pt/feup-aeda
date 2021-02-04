cmake_minimum_required(VERSION 3.9)
project(StreamZ)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/Admin.h
        src/Date.h
        src/StreamData.h
        src/Stream.h
        src/PrivateStream.h
        src/User.h
        src/Streamer.h
        src/Viewer.h
        src/Archive.h
        src/Exceptions.h
        src/Platform.h
        src/Input.h
        src/Menu.h
        src/Admin.cpp
        src/Date.cpp
        src/StreamData.cpp
        src/Stream.cpp
        src/PrivateStream.cpp
        src/User.cpp
        src/Streamer.cpp
        src/Viewer.cpp
        src/Exceptions.cpp
        src/Archive.cpp
        src/Platform.cpp
        src/Menu.cpp
        src/Input.cpp
        main.cpp)

include_directories(src)
add_subdirectory(tests)

add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCE_FILES})
add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCE_FILES})