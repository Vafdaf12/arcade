cmake_minimum_required(VERSION 3.10)

project(Arcade)

include(FetchContent)

set(NAME_EXE Arcade)

# ------------ FETCH SDL2 ------------ 
FetchContent_Declare(SDL2 
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.26.2
)
FetchContent_MakeAvailable(SDL2)

# ------------ CONFIGURE ARCADE -------------------
file(GLOB SRCFILES
    src/graphics/*.cpp
    src/shapes/*.cpp
    src/util/*.cpp
    src/*.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(${NAME_EXE} ${SRCFILES})
target_link_libraries(${NAME_EXE} SDL2)


