#!/bin/bash
cd ../src
mkdir build
cd build
cmake ..
make
mkdir ../../release
cp -f ./alg/lib_alg.so ./buffer/lib_buffer.so ./comm/lib_comm.so ./sensor/lib_sensor.so ./main/robooster_framework ../../release
