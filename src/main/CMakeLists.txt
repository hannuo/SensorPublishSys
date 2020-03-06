cmake_minimum_required(VERSION 2.8.3)
project(robooster_framework)

## Compile as C++11
##add_compile_options(-std=c++11 -fPIC -Wall -fvisibility=hidden)
add_compile_options(-std=c++11 -fPIC -Wall -lpthread)
## include
include_directories(./)

## lib path
link_directories(../build/comm
		 ../build/alg
		 ../build/sensor
		 ../../yaml-cpp/lib)

aux_source_directory(. SRC_DIR)
add_executable(${PROJECT_NAME}  ${SRC_DIR})

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME} _comm _alg _sensor yaml-cpp)

