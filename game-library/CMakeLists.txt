cmake_minimum_required(VERSION 2.8.10)

set(GAME_LIBRARY GhotiRPGLibrary)
project(${GAME_LIBRARY})

file(GLOB_RECURSE CPP_FILES "src/*.cpp")

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_check(REQUIRED)
conan_add_remote(NAME bincrafters URL https://api.bintray.com/conan/bincrafters/public-conan)

conan_cmake_run(REQUIRES sdl2/2.0.10@bincrafters/stable
        sdl2_image/2.0.5@bincrafters/stable
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

include_directories(include ${CONAN_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} CONAN_PKG::sdl2 CONAN_PKG::sdl2_image)
