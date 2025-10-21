cmake_minimum_required(VERSION 4.1)
project(ccs)

set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(ccs src/ccs.cc src/lib.cc)
