#!/bin/sh

#  conf.sh
#  Tetris3D
#
#  Created by ugo cottin on 08/11/2018.
#  Copyright © 2018 ugocottin. All rights reserved.

mkdir .trash

cd libClasses/
cmake ./CMakeLists.txt
make

mv cmake_install.cmake ../.trash/cmake_installLib.cmake
mv CMakeCache.txt ../.trash/CMakeCacheLib.txt
mv CMakeFiles ../.trash/CMakeFilesLib
mv Makefile ../.trash/MakefileLib

cd ..
cmake ./CMakeLists.txt
make

mv cmake_install.cmake .trash/cmake_installBase.cmake
mv CMakeCache.txt .trash/CMakeCacheBase.txt
mv CMakeFiles .trash/CMakeFilesBase
mv Makefile .trash/MakefileBase

mv main Tetris3D
./Tetris3D
