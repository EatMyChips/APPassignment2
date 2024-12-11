cmake_minimum_required(VERSION 3.29)
project(APPassignment2)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

