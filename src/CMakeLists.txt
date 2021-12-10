cmake_minimum_required(VERSION 3.0)
set(GAMESVR gamesvr)
project(${GAMESVR})

aux_source_directory(. SRCS)
aux_source_directory(./utils SRCS)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "../../libs")

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG -O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

add_library(${GAMESVR} STATIC ${SRCS})
target_link_libraries(${GAMESVR} pthread) # protobuf uuid)