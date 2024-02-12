cmake_minimum_required(VERSION 3.15)
project(stockfish_api CXX)

set(restinio_DIR build)
set(llhttp_DIR build)
set(expected-lite_DIR build)
set(asio_DIR build)

find_package(restinio REQUIRED)

message("Building with CMake version: ${CMAKE_VERSION}")

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} restinio::restinio)
