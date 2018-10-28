//
//  form.cpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "form.hpp"

/**
 *
 */
Form::Form() {
    origine = Point3D();
    elements = NULL;
    color = new int[3];
}

Form::Form(Cube*** elements) {
    origine = Point3D();
    this->elements = createArray(3, 3, 3);
    memcpy(this->elements, elements, 3*3*3*sizeof(Cube));
    /*for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                this->elements[i][j][k] = elements[i][j][k];
            }
        }
    }*/
    color = new int[3];
    color[0] = 100;
    color[1] = 100;
    color[2] = 100;
}

Point3D Form::getOrigine() {
    return origine;
}

void Form::addElement(Cube e, int x, int y, int z) {
    if (elements != NULL)
        elements[x][y][z] = e;
    else {
        this->elements = createArray(3, 3, 3);
        elements[x][y][z] = e;
    }
}

Cube*** Form::getElements() {
    return elements;
}

void Form::move(int x, int y, int z) {
    origine = Point3D(origine.getX() + x, origine.getY() + y, origine.getZ() + z);
};
