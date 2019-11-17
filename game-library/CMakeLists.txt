cmake_minimum_required(VERSION 2.8.10)

set(GAME_LIBRARY GhotiRPGLibrary)
project(${GAME_LIBRARY})

file(GLOB_RECURSE CPP_FILES "src/*.cpp")
include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
