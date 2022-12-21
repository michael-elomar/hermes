cmake_minimum_required(VERSION 3.10)


project(Hermes VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")


set(CMAKE_CXX_STANDARD 14)
set(INDLUDE_DIR "../include")

set(
    SOURCES "./src/main.cpp" 
    ${INDLUDE_DIR}/Node.hpp 
    ${INDLUDE_DIR}/Node.cpp
)

add_executable(hermes ${SOURCES})
target_include_directories(hermes PRIVATE ${INDLUDE_DIR})
