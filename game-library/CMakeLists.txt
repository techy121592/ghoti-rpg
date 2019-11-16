cmake_minimum_required(VERSION 2.8.10)

set(GAME_LIBRARY GhotiRPGLibrary)
project(${GAME_LIBRARY})

file(GLOB CPP_FILES src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp src/*/*/*/*/*.cpp)
file(GLOB HEADER_FILES include/*.h include/*/*.h include/*/*/*.h include/*/*/*/*.h)

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${HEADER_FILES})

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})

find_file(SDL2_IMAGE_INCLUDE_DIR NAME SDL_image.h HINTS SDL2_image)
find_library(SDL2_IMAGE_LIBRARY NAME SDL2_image)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARY})
