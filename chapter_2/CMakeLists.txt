cmake_minimum_required(VERSION 3.24)   # oldest CMake allowed to build this project

project(starship LANGUAGES CXX)            # project name, and it's a C++ project

set(CMAKE_CXX_STANDARD 20)             # use C++20...
set(CMAKE_CXX_STANDARD_REQUIRED ON)    # ...and fail if the compiler can't do it
set(CMAKE_CXX_EXTENSIONS OFF)          # standard C++ only, no compiler-specific dialect
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_CLANG_TIDY "Run clang-tidy during build" OFF)
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


add_executable(starship src/main.cpp
    src/game.cpp
    src/game.h
    src/actors/actor.cpp
    src/actors/actor.h
    src/object/vectors.h
    src/components/component.h
    src/components/component.cpp
    )
target_include_directories(starship PRIVATE src)
target_link_libraries(
    starship
        PRIVATE
            SDL2::SDL2main
            SDL2::SDL2-static
            
)           


if (MSVC)
    target_compile_options(starship PRIVATE /W4)
else()
    target_compile_options(starship PRIVATE -Wall -Wextra -Wpedantic)
endif()


if (ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
    set_target_properties(starship PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()


find_program(CLANG_FORMAT_EXE NAMES clang-format)
if (CLANG_FORMAT_EXE)
    file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)
    add_custom_target(format COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_SOURCES})
endif()
