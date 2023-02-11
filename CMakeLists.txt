cmake_minimum_required(VERSION 3.10)

project(Arcade)

include(FetchContent)

set(NAME_EXE Arcade)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

# ------------ FETCH SDL2 ------------ 
FetchContent_Declare(SDL2 
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.26.2
)
FetchContent_MakeAvailable(SDL2)

# ------------ CONFIGURE ARCADE -------------------
file(GLOB SRCFILES
    src/graphics/*.cpp
    src/graphics/render/*.cpp
    src/shapes/*.cpp
    src/util/*.cpp
    src/app/*.cpp
    src/scene/*.cpp
    src/input/*.cpp
    src/games/*.cpp
    src/games/breakout/*.cpp
    src/games/tetris/*.cpp
    src/*.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(${NAME_EXE} ${SRCFILES})
target_include_directories(${NAME_EXE}
    PRIVATE src/
)
target_link_libraries(${NAME_EXE} SDL2-static -static)


