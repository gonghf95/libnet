cmake_minimum_required(VERSION 2.8)

project(libnet C CXX)

set(CXX_FLAGS
 -std=c++11
 -g
 -Wall
)

string(REPLACE ";" " " CMAKE_CXX_COMPILER "${CXX_FLAGS}")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(src)