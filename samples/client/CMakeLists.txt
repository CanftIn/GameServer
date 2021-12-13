cmake_minimum_required(VERSION 2.8)
set(MyProjectName client)
set(MyLibNetWorkName gamesvr.a)

project(${MyProjectName})

aux_source_directory(. SRCS)

include_directories(../../src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin")

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -DEPOLL")
set(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG -O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

link_directories(${CMAKE_BINARY_DIR}/../../libs)

add_executable(${MyProjectName} ${SRCS})
target_link_libraries(${MyProjectName} ${MyLibNetWorkName} -lpthread)