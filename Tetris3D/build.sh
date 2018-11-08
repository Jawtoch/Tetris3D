#!/bin/sh

#  conf.sh
#  Tetris3D
#
#  Created by ugo cottin on 08/11/2018.
#  Copyright © 2018 ugocottin. All rights reserved.

cd libClasses/
make

cd ..
make

mv main Tetris3D
./Tetris3D
