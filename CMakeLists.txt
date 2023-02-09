# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

cmake_minimum_required(VERSION 3.5)
project(Hermes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

# find  OpenSSL
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)


include_directories(
    include
)

set (INCLUDE
    include/hermes.h
    include/cryptography.hpp
    include/socket.hpp
    include/socket.cpp
    include/ipaddress.hpp
    include/ipaddress.cpp
    include/tcpserver.hpp
    include/tcpserver.cpp
    include/tcpclient.hpp
    include/tcpclient.cpp
)




add_executable(server src/main.cpp ${INCLUDE})
target_link_libraries(server OpenSSL::Crypto)

add_executable(sha1 src/main2.cpp ${INCLUDE})
target_link_libraries(sha1 OpenSSL::Crypto)


