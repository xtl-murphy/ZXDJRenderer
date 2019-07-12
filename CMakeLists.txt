cmake_minimum_required(VERSION 3.13)
project(ZXDJRenderer)

set(LOCAL_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fPIC -Wall -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -fPIC -Wall -Wno-deprecated-declarations")

include_directories(${LOCAL_PATH})

file(GLOB_RECURSE STB_FILE "${LOCAL_PATH}/external/stb/*.h")
file(GLOB_RECURSE CPP_FILE "${LOCAL_PATH}/Component/*.cpp")

add_executable(ZXDJRenderer main.cpp ${CPP_FILE} ${STB_FILE})