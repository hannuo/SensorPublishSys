#!/bin/bash
cd ../src
mkdir buildDeb
cd buildDeb
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
mkdir ../../Debug
cp -f ./alg/lib_alg.so ./buffer/lib_buffer.so ./comm/lib_comm.so ./sensor/lib_sensor.so ./main/robooster_framework ../../Debug
