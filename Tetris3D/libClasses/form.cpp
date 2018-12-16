//
//  form.cpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "form.hpp"

Form::Form(int containerMaxSize,int formMaxSize) {
    origin = Point3D();
    elements = NULL;
    color = new int[3];
    color[0] = rand()%256;
    color[1] = rand()%256;
    color[2] = rand()%256;
    color[3] = rand()%256;
    exist = false;
    this->containerMaxSize = containerMaxSize;
    this->formMaxSize = formMaxSize;
    
}

Form ::~Form() {
    if (elements != NULL)
        freeArray(elements, formMaxSize, formMaxSize, formMaxSize);
}

Form::Form(Cube*** elements, int containerMaxSize,int formMaxSize) {
    
    this->containerMaxSize = containerMaxSize;
    this->formMaxSize = formMaxSize;
    
    color = new int[3];
    color[0] = rand()%256;
    color[1] = rand()%256;
    color[2] = rand()%256;
    color[3] = rand()%256;
    exist = true;
    
    origin = Point3D();
    this->elements = createArray(formMaxSize, formMaxSize, formMaxSize);
    for (int i = 0; i < formMaxSize; i++) {
        for (int j = 0; j < formMaxSize; j++) {
            for (int k = 0; k < formMaxSize; k++) {
                elements[i][j][k].setColors(color[0], color[1], color[2], color[3]);
                this->elements[i][j][k] = elements[i][j][k];
            }
        }
    }
}

Form::Form(int*** elements, int containerMaxSize,int formMaxSize) {
    
    this->containerMaxSize = containerMaxSize;
    this->formMaxSize = formMaxSize;
    
    color = new int[3];
    color[0] = rand()%256;
    color[1] = rand()%256;
    color[2] = rand()%256;
    color[3] = rand()%256;
    exist = true;
    
    origin = Point3D();
    this->elements = createArray(formMaxSize, formMaxSize, formMaxSize);
    for (int i = 0; i < formMaxSize; i++) {
        for (int j = 0; j < formMaxSize; j++) {
            for (int k = 0; k < formMaxSize; k++) {
                if (elements[i][j][k] == 1) {
                    this->elements[i][j][k] = Cube(20);
                    this->elements[i][j][k].setColors(color[0], color[1], color[2], color[3]);
                }
            }
        }
    }
}


Point3D Form::getOrigin() {
    return origin;
}

void Form::addElement(Cube e, unsigned int x, unsigned int y, unsigned int z) {
    if (x >= formMaxSize || y >= formMaxSize || z >= formMaxSize) {
        std::cout << "------\nWARNING -- Invalid parameter in fuction “addElement“ -- Index out of array bound. The element was not added to the form.\n" << std::endl;
    } else {
        if (elements == NULL)
            this->elements = createArray(formMaxSize, formMaxSize, formMaxSize);
        
        e.setColors(color[0], color[1], color[2], color[3]);
        elements[x][y][z] = e;
        
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
    for(int i = 0; i < formMaxSize; i++) {
        for(int j = 0; j < formMaxSize; j++) {
            for(int k = 0; k < formMaxSize; k++) {
                if (getElements()[i][j][k].doesExist()) {
                    Point3D org = getOrigin();
                    if (
                    ((org.getX() + i + x >= this->containerMaxSize) || (org.getX() + i + x < 0))
                    || ((org.getY() + j + y >= this->containerMaxSize) || (org.getY() + j + y < 0))
                    || ((org.getZ() + k + z >= this->containerMaxSize) || (org.getZ() + k + z < 0))
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

int Form::getScore() {
    
    int score = 0;
    
    for(int i = 0; i < this->formMaxSize; i++) {
        for(int j = 0; j < this->formMaxSize; j++) {
            for(int k = 0; k < this->formMaxSize; k++) {
                if (getElements()[i][j][k].doesExist())
                    score++;
            }
        }
    }
    
    return score;
}

bool Form::doesExist() {
    return exist;
};

void Form::RenderDrawForm(SDL_Renderer* renderer, int shiftX, int shiftY) {
    
    Cube *c = new Cube(sizeof(Cube));
    for(int i = 0; i < this->formMaxSize; i++) {
        for(int j = 0; j < this->formMaxSize; j++) {
            for(int k = 0; k < this->formMaxSize; k++) {
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

