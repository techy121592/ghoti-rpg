cmake_minimum_required(VERSION 2.8.10)

project(GhotiRPGDesktop)

file(GLOB_RECURSE CPP_FILES "src/*.cpp")

include_directories(include ../game-library/include)

add_executable(${PROJECT_NAME} ${CPP_FILES})
target_link_libraries(${PROJECT_NAME} GhotiRPGLibrary)

file(COPY ../game-library/res DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${BIN_DIR})
