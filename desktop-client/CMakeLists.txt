cmake_minimum_required(VERSION 2.8.10)

project(GhotiRPGDesktop)

file(GLOB CPP_FILES src/*.cpp)

# Look up SDL2 and add the include directory to our include path
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

include_directories(include)
include_directories(../game-library/include)

add_executable(${PROJECT_NAME} ${CPP_FILES})
target_link_libraries(${PROJECT_NAME} GhotiRPGLibrary ${SDL2_LIBRARY})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${BIN_DIR})
