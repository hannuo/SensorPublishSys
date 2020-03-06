cmake_minimum_required(VERSION 2.8.3)
project(_comm)

## Compile as C++11
##add_compile_options(-std=c++11 -fPIC -Wall -fvisibility=hidden)
add_compile_options(-std=c++11 -fPIC -Wall)
## include
##include_directories(./)
include_directories(../../yaml-cpp/include)
## lib path
link_directories(../../yaml-cpp/lib)

add_library(${PROJECT_NAME}  SHARED 
				ConfigParse.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME} yaml-cpp)

