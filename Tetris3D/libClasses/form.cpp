//
//  form.cpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "form.hpp"

Form::Form() {
    origin = Point3D();
    elements = NULL;
    color = new int[3];
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    exist = false;
    
}

Form ::~Form() {
}

Form::Form(Cube*** elements) {
    origin = Point3D();
    this->elements = createArray(3, 3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                this->elements[i][j][k] = elements[i][j][k];
            }
        }
    }
    color = new int[3];
    color[0] = rand()%256;
    color[1] = rand()%256;
    color[2] = rand()%256;
    exist = true;
}

Point3D Form::getOrigin() {
    return origin;
}

void Form::addElement(Cube e, unsigned int x, unsigned int y, unsigned int z) {
    if (x > 3 || y > 3 || z > 3) {
        std::cout << "------\nWARNING -- Invalid parameter in fuction “addElement“ -- Index out of array bound. The element was not added to the form.\n" << std::endl;
    } else {
        if (elements != NULL)
            elements[x][y][z] = e;
        else {
            this->elements = createArray(3, 3, 3);
            elements[x][y][z] = e;
        }
    }
}

Cube*** Form::getElements() {
    return elements;
}

void Form::move(int x, int y, int z) {
    origin = Point3D(getOrigin().getX() + x, getOrigin().getY() + y, getOrigin().getZ() + z);
};

bool Form::doesExist() {
    return exist;
};

void Form::RenderDrawForm(SDL_Renderer* renderer, int shiftX, int shiftY) {
    SDL_SetRenderDrawColor(renderer, this->color[0], this->color[1], this->color[2], 255);
    
    Cube *c = new Cube(sizeof(Cube));
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 2; k >= 0; k--) {
                *c = getElements()[i][j][k];
                if (c->doesExist())
                    c->RenderDrawCube(renderer,
                                      i + (int)(getOrigin().getX()),
                                      j + (int)(getOrigin().getY()),
                                      k + (int)(getOrigin().getZ()),
                                      shiftX, shiftY);
            }
        }
    }
    delete c;
};
