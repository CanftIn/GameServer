#!/bin/bash
args=$1

buildType="Debug"
clean=false

if [ ${args}v = "release"v ];then
    buildType="Release"
elif [ ${args}v = "clean"v ];then
    clean=true
elif [ ${args}v = ""v ];then
    echo "INFO: build.sh start"
else
    echo "ERROR: args not support!"
fi


if ${clean};then
    rm -rf build
    rm -rf libs
    rm -rf bin
else
    mkdir build && cd build
    mkdir build_lib && cd build_lib
    cmake -DCMAKE_BUILD_TYPE=${buildType} ../../src
    make
    cd ..
    mkdir build_svr && cd build_svr
    cmake -DCMAKE_BUILD_TYPE=${buildType} ../../samples/server
    make
    cd ..
    mkdir build_cln && cd build_cln
    cmake -DCMAKE_BUILD_TYPE=${buildType} ../../samples/client
    make
    cd ../..
fi

