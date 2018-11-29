//
//  container.cpp
//  Tetris3D
//
//  Created by ugo cottin on 28/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "container.hpp"

Container::Container() {
    elements = createArray(CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE);
}

Container::~Container() {
    freeArray(elements, CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE);
}

void Container::addForm(Form &addedForm) {
    forms.insert(std::make_pair(getSize(), &addedForm));
};

Form* Container::getForm(int index) {
    std::map<int, Form*>::iterator it = forms.begin();
    for(int i = 0; i < getSize(); i++) {
        if (i == index) {
            return (it->second);
        }
        it++;
    }
    return NULL;
};

int Container::getSize() {
    return (int)forms.size();
};

void Container::update() {
    std::map<int, Form*>::const_iterator it = forms.begin();
    
    Cube*** plateau = createArray(CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE);
    
    Point3D *org = new Point3D;
    while (it != forms.end()) {
        
        *org = it->second->getOrigin();
        Cube*** el = it->second->getElements();
        for(int i = 0; i < FORM_MAX_SIZE; i++) {
            for(int j = 0; j < FORM_MAX_SIZE; j++) {
                for(int k = 0; k < FORM_MAX_SIZE; k++) {
                    if (el[i][j][k].doesExist()) {
                        plateau[(int)org->getX() + i][(int)org->getY() + j][(int)org->getZ() + k] = el[i][j][k];
                        
                    }
                    
                }
            }
        }
        it++;
    }
    delete org;
    
    Cube c;
    bool del = true;
    
    for(int i = 0; i < CONTAINER_MAX_SIZE; i++) {
        del = true;
        for(int j = 0; j < CONTAINER_MAX_SIZE; j++) {
            for(int k = 0; k < CONTAINER_MAX_SIZE; k++) {
                c = plateau[i][j][k];
                if (!c.doesExist()) {
                    del = false;
                    
                }
            }
        }
        
        if (del) {
            for(int j = 0; j < CONTAINER_MAX_SIZE; j++) {
                for(int k = 0; k < CONTAINER_MAX_SIZE; k++) {
                    c = plateau[i][j][k];
                    c.setExist(false);
                }
            }
        }
        
        
    }
    freeArray(plateau, CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE);
    
}

void Container::RenderDrawContainer(SDL_Renderer* renderer, int shiftX, int shiftY) {
    update();
    std::map<int, Form*>::const_iterator it = forms.begin();
    
    Cube*** plateau = createArray(CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE);
    
    Point3D *org = new Point3D;
    while (it != forms.end()) {
        
        *org = it->second->getOrigin();
        Cube*** el = it->second->getElements();
        for(int i = 0; i < FORM_MAX_SIZE; i++) {
            for(int j = 0; j < FORM_MAX_SIZE; j++) {
                for(int k = 0; k < FORM_MAX_SIZE; k++) {
                    if (el[i][j][k].doesExist()) {
                        plateau[(int)org->getX() + i][(int)org->getY() + j][(int)org->getZ() + k] = el[i][j][k];
                        
                    }
                    
                }
            }
        }
        it++;
    }
    delete org;
    
    Cube c;
    
    for(int i = 0; i < CONTAINER_MAX_SIZE; i++) {
        for(int j = 0; j < CONTAINER_MAX_SIZE; j++) {
            for(int k = 0; k < CONTAINER_MAX_SIZE; k++) {
                c = plateau[i][j][k];
                if (c.doesExist()) {
                    Uint8 SavedR = 0;
                    Uint8 SavedG = 0;
                    Uint8 SavedB = 0;
                    Uint8 SavedA = 0;
                    int test = SDL_GetRenderDrawColor(renderer, &SavedR, &SavedG, &SavedB, &SavedA);
                    if (test != 0)
                        SDL_GetError();
                    
                    Uint8 r = 0;
                    Uint8 g = 0;
                    Uint8 b = 0;
                    Uint8 a = 255;
                    c.getColors(&r, &g, &b);
                    test = SDL_SetRenderDrawColor(renderer, r, g, b, a);
                    if (test != 0)
                        SDL_GetError();
                    c.RenderDrawCube(renderer, i, j, k, shiftX, shiftY);
                }
            }
        }
    }
    freeArray(plateau, CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE, CONTAINER_MAX_SIZE);
};
