cmake_minimum_required(VERSION 3.14)

project(MCC VERSION 0.0.1 LANGUAGES CXX)

message("Building ${CMAKE_PROJECT_NAME} Version = ${CMAKE_PROJECT_VERSION}...")
string(TOUPPER ${CMAKE_PROJECT_NAME} PROJECT_NAME_UPPER)
add_definitions( -D${PROJECT_NAME_UPPER}_VERSION="${CMAKE_PROJECT_VERSION}" )

set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MCC_COMPILE_CORE "ON")
set(MCC_RTMIDI_STATUS "ON")

add_subdirectory(src)

if( BUILD_EXAMPLES  STREQUAL "ON")
	add_subdirectory(examples)
endif()