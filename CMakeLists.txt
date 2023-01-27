# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

cmake_minimum_required(VERSION 3.5)
project(Hermes)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    include
)

set (SRCS
    include/hermes.h
    include/socket.hpp
    include/socket.cpp
    include/ipaddress.hpp
    include/ipaddress.cpp
    src/main.cpp
)


add_executable(${CMAKE_PROJECT_NAME} ${SRCS})

