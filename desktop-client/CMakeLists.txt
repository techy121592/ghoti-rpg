cmake_minimum_required(VERSION 2.8.10)

project(GhotiRPGDesktop)

file(GLOB CPP_FILES src/*.cpp)

include_directories(include)
include_directories(../game-library/include)

add_executable(${PROJECT_NAME} ${CPP_FILES})
target_link_libraries(${PROJECT_NAME} GhotiRPGLibrary ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${BIN_DIR})
