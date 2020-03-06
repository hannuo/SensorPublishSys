cmake_minimum_required(VERSION 2.8.3)
project(_alg)

## Compile as C++11
##add_compile_options(-std=c++11 -fPIC -Wall -fvisibility=hidden)
add_compile_options(-std=c++11 -fPIC -Wall)
## include
include_directories(./
		    ../comm
		    ../buffer
		    ../../yaml-cpp/include)

## lib path
link_directories(../build/comm
		 ../build/buffer
	 	 ../../yaml-cpp/lib)

aux_source_directory(. SRC_DIR)
add_library(${PROJECT_NAME}  SHARED 
				${SRC_DIR})

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME} _comm _buffer yaml-cpp)

