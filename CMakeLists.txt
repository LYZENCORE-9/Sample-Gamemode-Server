cmake_minimum_required(VERSION 3.24)
project(SampleGDK)

SET(GCC_COVERAGE_COMPILE_FLAGS "-m32 -g -O0 -static-libgcc -static-libstdc++")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_library(Account_Database	OBJECT 		"${CMAKE_SOURCE_DIR}/src/Account/Database.cpp")
add_library(${PROJECT_NAME} 	SHARED 		"${CMAKE_SOURCE_DIR}/src/sample.cpp")

target_link_libraries(${PROJECT_NAME} Account_Database)
target_link_libraries(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/lib/libsampgdk.a")
target_link_libraries(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/lib/liblfileini32.a")
#target_link_libraries(${PROJECT_NAME} libgcc stdc++)
