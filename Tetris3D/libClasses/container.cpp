//
//  container.cpp
//  Tetris3D
//
//  Created by ugo cottin on 28/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "container.hpp"

Container::Container(int containerMaxSize, int formMaxSize) {
    this->containerMaxSize = containerMaxSize;
    this->formMaxSize = formMaxSize;
    elements = createArray(this->containerMaxSize, this->containerMaxSize, this->containerMaxSize);
}

Container::~Container() {
    freeArray(elements, containerMaxSize, containerMaxSize, containerMaxSize);
}

void Container::addForm(Form addedForm) {
    for(int i = 0; i < this->formMaxSize; i++) {
        for(int j = 0; j < this->formMaxSize; j++) {
            for(int k = 0; k < this->formMaxSize; k++) {
                
                if (addedForm.getElements()[i][j][k].doesExist()) {
                    elements[i + (int)addedForm.getOrigin().getX()][j + (int)addedForm.getOrigin().getY()][k + (int)addedForm.getOrigin().getZ()] = addedForm.getElements()[i][j][k];
                }
            }
        }
    }
};

Cube*** Container::getElements() {
    return elements;
}

void Container::update() {
    Cube c;
    bool del;
    
    for(int z = 0; z < this->containerMaxSize; z++) {
        del = true;
        
        for(int x = 0; x < this->containerMaxSize; x++) {
            for(int y = 0; y < this->containerMaxSize; y++) {
                if (!elements[x][y][z].doesExist()) {
                    del = false;
                }
            }
        }
        
        if (del) {
            for(int x = 0; x < this->containerMaxSize; x++) {
                for(int y = 0; y < this->containerMaxSize; y++) {
                    elements[x][y][z].setExist(false);
                }
            }
            
            for(int k = z; k > 0; k--) {
                for(int i = 0; i < this->containerMaxSize; i++) {
                    for (int j = 0; j < this->containerMaxSize; j++) {
                        elements[i][j][k] = elements[i][j][k - 1];
                        elements[i][j][k - 1].setExist(false);
                    }
                }
            }
        }
        
    }
}

void Container::RenderDrawContainer(SDL_Renderer* renderer, int shiftX, int shiftY, Form &currentForm) {
    update();

    Cube c;
    bool found;
    Uint8 SavedR = 0;
    Uint8 SavedG = 0;
    Uint8 SavedB = 0;
    Uint8 SavedA = 0;
    int test = SDL_GetRenderDrawColor(renderer, &SavedR, &SavedG, &SavedB, &SavedA);
    if (test != 0)
        SDL_GetError();
    
    for(int i = 0; i < this->containerMaxSize; i++) {
        for(int j = 0; j < this->containerMaxSize; j++) {
            for(int k = this->containerMaxSize - 1; k > -1; k--) {
                found = false;
                if(
                   (i >= currentForm.getOrigin().getX() && i < currentForm.getOrigin().getX() + this->formMaxSize) &&
                   (j >= currentForm.getOrigin().getY() && j < currentForm.getOrigin().getY() + this->formMaxSize) &&
                   (k >= currentForm.getOrigin().getZ() && k < currentForm.getOrigin().getZ() + this->formMaxSize)
                   ) {
                    int indexI = i - (int)currentForm.getOrigin().getX();
                    int indexJ = j -  (int)currentForm.getOrigin().getY();
                    int indexK = k - (int)currentForm.getOrigin().getZ();
                    
                    if (currentForm.getElements()[indexI][indexJ][indexK].doesExist()) {
                        found = true;
                        c = currentForm.getElements()[indexI][indexJ][indexK];
                    }
                }
                
                if (!found) {
                    c = elements[i][j][k];
                }
                if (c.doesExist()) {
                    c.RenderDrawCube(renderer, i, j, k, shiftX, shiftY);
                }
            }
        }
    }
};
