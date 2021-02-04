cmake_minimum_required(VERSION 3.9)
project(StreamZ)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/Admin.h
        src/bst.h
        src/Date.h
        src/Donation.h
        src/Donation.cpp
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
        src/StreamerRecord.h
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
        src/Product.cpp
        src/Product.h
        src/Order.cpp
        src/Order.h
        src/Store.cpp
        src/Store.h
        src/StreamerRecord.cpp
        main.cpp)

include_directories(src)
add_subdirectory(tests)

add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCE_FILES})
add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCE_FILES})

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR ${CMAKE_SOURCE_DIR}/docs/output)
    if(NOT EXISTS ${BUILD_DOC_DIR})
        file(MAKE_DIRECTORY ${BUILD_DOC_DIR})
    endif()

    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)