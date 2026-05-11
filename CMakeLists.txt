cmake_minimum_required(VERSION 3.16)
project(tictactoe LANGUAGES C CXX)

set(CMAKE_CXX STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSION OFF)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 6.0
)

FetchContent_MakeAvailable(raylib)

add_executable(tictactoe src/main.cpp)

target_link_libraries(tictactoe PRIVATE raylib)
