cmake_minimum_required(VERSION 3.19)

project(tool-learn)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(lib-example)
add_subdirectory(data-structure)
add_subdirectory(unix)
add_subdirectory(GOF)