cmake_minimum_required(VERSION 3.5)
project(ccs)


set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(ccs src/ccs.cc src/socket.cc src/server.cc src/crypto.cc)
add_executable(client src/client_main.cc src/client.cc src/socket.cc src/crypto.cc)
add_executable(test test/test.cc src/crypto.cc src/server.cc src/socket.cc src/client.cc)
