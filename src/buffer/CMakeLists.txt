cmake_minimum_required(VERSION 2.8.3)
project(_buffer)

## Compile as C++11
##add_compile_options(-std=c++11 -fPIC -Wall -fvisibility=hidden)
add_compile_options(-std=c++11 -fPIC -Wall)
## include
include_directories(./)

## lib path


add_library(${PROJECT_NAME}  SHARED 
				CQueueFactory.cpp)
