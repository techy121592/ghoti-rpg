#!/bin/bash

#cd ghoti-rpg
rm ./cmake_install.cmake
rm ./CMakeCache.txt
rm ./GhotiRPG.cbp
rm ./GhotiRPG.layout
rm ./Makefile
rm -Rf ./CMakeFiles

cd game-library
rm ./cmake_install.cmake
rm ./libGhotiRPGLibrary.a
rm ./Makefile
rm -Rf ./CMakeFiles

cd ../desktop-client
rm cmake_install.cmake
rm GhotiRPGDesktop.cbp
rm Makefile
rm ./GhotiRPGDesktop
rm -Rf ./CMakeFiles

cd ..
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
cmake -G "CodeBlocks - Unix Makefiles"
