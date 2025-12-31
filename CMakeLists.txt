cmake_minimum_required(VERSION 3.5)
project(ccs)


set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang)
#set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(ccs src/ccs.c src/server.c src/crypto.c)
add_executable(client src/client_main.c src/client.c src/crypto.c)
add_executable(test test/test.c src/crypto.c src/server.c src/client.c)
