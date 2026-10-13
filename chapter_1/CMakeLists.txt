cmake_minimum_required(VERSION 3.24)   # oldest CMake allowed to build this project

project(pong LANGUAGES CXX)            # project name, and it's a C++ project

set(CMAKE_CXX_STANDARD 20)             # use C++20...
set(CMAKE_CXX_STANDARD_REQUIRED ON)    # ...and fail if the compiler can't do it
set(CMAKE_CXX_EXTENSIONS OFF)          # standard C++ only, no compiler-specific dialect

#for sdl
include(FetchContent)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
    GIT_TAG         release-2.32.10
    GIT_SHALLOW     TRUE
)

FetchContent_MakeAvailable(SDL2)


add_executable(pong src/main.cpp
    src/game.h
    src/game.cpp)
target_link_libraries(
    pong
        PRIVATE
            SDL2::SDL2main
            SDL2::SDL2-static
            
)           
