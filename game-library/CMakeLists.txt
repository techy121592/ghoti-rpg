cmake_minimum_required(VERSION 2.8.10)

set(GAME_LIBRARY GhotiRPGLibrary)
project(${GAME_LIBRARY})

file(GLOB CPP_FILES src/*.cpp)

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${CPP_FILES})
