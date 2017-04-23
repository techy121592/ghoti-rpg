#!/bin/bash

#cd ghoti-rpg
rm ./cmake_install.cmake
rm ./CMakeCache.txt
rm ./GhotiRPG.*
rm ./Makefile
rm -Rf ./CMakeFiles
rm -Rf ./output

cd game-library
rm ./cmake_install.cmake
rm ./Makefile
rm -Rf ./CMakeFiles

cd ../desktop-client
rm cmake_install.cmake
rm GhotiRPGDesktop.cbp
rm Makefile
rm -Rf ./CMakeFiles

cd ..
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
cmake -G "CodeBlocks - Unix Makefiles"

echo "Copying resources to build path."
cp -R game-library/res ./output
