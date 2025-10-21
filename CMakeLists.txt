cmake_minimum_required(VERSION 4.1)
project(ccs)

set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ccs src/ccs.cc src/pool.cc src/socket.cc)
add_executable(client src/client.cc src/socket.cc)
