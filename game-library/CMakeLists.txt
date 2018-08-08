cmake_minimum_required(VERSION 2.8.10)

set(GAME_LIBRARY GhotiRPGLibrary)
project(${GAME_LIBRARY})

file(GLOB CPP_FILES src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp src/*/*/*/*/*.cpp)
file(GLOB HEADER_FILES include/*.h include/*/*.h)

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${HEADER_FILES})
