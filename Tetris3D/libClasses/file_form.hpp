//
//  file_form.hpp
//  Tetris3D
//
//  Created by ugo cottin on 15/12/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#ifndef file_form_h
#define file_form_h

#include <iostream>

#include "cube.hpp"
#include "form.hpp"

void freeArrayInteger(int*** cTab, int xSize, int ySize, int zSize);

int*** file_to_array(char* name_file, int formMaxSize);

Form array_to_form(int*** arr, int formMaxSize);

int*** choose_form(int nbForm, int formMaxSize);

int*** generateTab();

#endif /* file_form_h */
