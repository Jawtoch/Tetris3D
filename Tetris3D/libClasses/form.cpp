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
    delete color;
    if (elements != NULL)
        freeArray(elements, FORM_MAX_SIZE, FORM_MAX_SIZE, FORM_MAX_SIZE);
}

Form::Form(Cube*** elements) {
    
    color = new int[3];
    color[0] = rand()%256;
    color[1] = rand()%256;
    color[2] = rand()%256;
    exist = true;
    
    origin = Point3D();
    this->elements = createArray(FORM_MAX_SIZE, FORM_MAX_SIZE, FORM_MAX_SIZE);
    for (int i = 0; i < FORM_MAX_SIZE; i++) {
        for (int j = 0; j < FORM_MAX_SIZE; j++) {
            for (int k = 0; k < FORM_MAX_SIZE; k++) {
                elements[i][j][k].setColors(color[0], color[1], color[2]);
                this->elements[i][j][k] = elements[i][j][k];
            }
        }
    }
}

Point3D Form::getOrigin() {
    return origin;
}

void Form::addElement(Cube e, unsigned int x, unsigned int y, unsigned int z) {
    if (x >= FORM_MAX_SIZE || y >= FORM_MAX_SIZE || z >= FORM_MAX_SIZE) {
        std::cout << "------\nWARNING -- Invalid parameter in fuction “addElement“ -- Index out of array bound. The element was not added to the form.\n" << std::endl;
    } else {
        if (elements == NULL)
            this->elements = createArray(FORM_MAX_SIZE, FORM_MAX_SIZE, FORM_MAX_SIZE);
        e.setColors(color[0], color[1], color[2]);
        elements[x][y][z] = e;
        
        color[0] = rand()%256;
        color[1] = rand()%256;
        color[2] = rand()%256;
        exist = true;
    }
}

Cube*** Form::getElements() {
    return elements;
}

void Form::setOrigin(Point3D org) {
    this->origin = org;
}

bool Form::move(int x, int y, int z, Cube*** elements) {
    bool out = true;
    for(int i = 0; i < FORM_MAX_SIZE; i++) {
        for(int j = 0; j < FORM_MAX_SIZE; j++) {
            for(int k = 0; k < FORM_MAX_SIZE; k++) {
                if (getElements()[i][j][k].doesExist()) {
                    Point3D org = getOrigin();
                    if (
                    ((org.getX() + i + x >= CONTAINER_MAX_SIZE) || (org.getX() + i + x < 0))
                    || ((org.getY() + j + y >= CONTAINER_MAX_SIZE) || (org.getY() + j + y < 0))
                    /*|| ((org.getZ() + k + z >= CONTAINER_MAX_SIZE) || (org.getZ() + k + z < 0))*/
                    ) /* le déplacement est hors des limites du conteneur*/ {
                        out = false;
                    } else {
                        if (elements[(int)org.getX() + i + x][(int)org.getY() + j + y][(int)org.getZ() + k + z].doesExist()) {
                            out = false;
                        }
                    }
                }
            }
        }
    }
    if (out) {
        origin = Point3D(getOrigin().getX() + x, getOrigin().getY() + y, getOrigin().getZ() + z);
        return true;
    }
    return false;
};

bool Form::doesExist() {
    return exist;
};

void Form::RenderDrawForm(SDL_Renderer* renderer, int shiftX, int shiftY) {
    
    Uint8 SavedR = 0;
    Uint8 SavedG = 0;
    Uint8 SavedB = 0;
    Uint8 SavedA = 0;
    int test = SDL_GetRenderDrawColor(renderer, &SavedR, &SavedG, &SavedB, &SavedA);
    if (test != 0)
        SDL_GetError();
    
    SDL_SetRenderDrawColor(renderer, this->color[0], this->color[1], this->color[2], 255);
    
    Cube *c = new Cube(sizeof(Cube));
    for(int i = 0; i < FORM_MAX_SIZE; i++) {
        for(int j = 0; j < FORM_MAX_SIZE; j++) {
            for(int k = 0; k < FORM_MAX_SIZE; k++) {
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
    
    SDL_SetRenderDrawColor(renderer, SavedR, SavedG, SavedB, SavedA);
};

