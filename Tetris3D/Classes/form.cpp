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

void Form::RenderDrawForm(SDL_Renderer* renderer, int shiftX, int shiftY) {
    SDL_SetRenderDrawColor(renderer, this->color[0], this->color[1], this->color[2], 255);
    
    Cube *c = new Cube(sizeof(Cube));
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++) {
                *c = getElements()[i][j][k];
                if (c->doesExist())
                    c->RenderDrawCube(renderer,
                                      i + (int)(getOrigine().getX()),
                                      j + (int)(getOrigine().getY()),
                                      k + (int)(getOrigine().getZ()),
                                      shiftX, shiftY);
            }
        }
    }
    delete c;
};
