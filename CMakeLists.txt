cmake_minimum_required(VERSION 3.15)
project(stockfish_api CXX)

message("Building with CMake version: ${CMAKE_VERSION}")

add_executable(stockfish_api src/main.cpp)

project(input CXX)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 871ed52d350214a034f6ef8a3b8f51c5ce1bd400) # The commit hash for 1.9.0. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)


add_executable(input src/input/main.cpp)
target_link_libraries(input PRIVATE cpr::cpr)

