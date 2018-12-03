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

void Container::addForm(Form addedForm) {
    for(int i = 0; i < FORM_MAX_SIZE; i++) {
        for(int j = 0; j < FORM_MAX_SIZE; j++) {
            for(int k = 0; k < FORM_MAX_SIZE; k++) {
                
                if (addedForm.getElements()[i][j][k].doesExist()) {
                    elements[i + (int)addedForm.getOrigin().getX()][j + (int)addedForm.getOrigin().getY()][k + (int)addedForm.getOrigin().getZ()] = addedForm.getElements()[i][j][k];
                }
            }
        }
    }
};

Form* Container::getForm(int index) {
    return currentForm;
};

int Container::getSize() {
    return 0;
};

void Container::update() {
    Cube c;
    bool del;
    
    for(int z = 0; z < CONTAINER_MAX_SIZE; z++) {
        del = true;
        
        for(int x = 0; x < CONTAINER_MAX_SIZE; x++) {
            for(int y = 0; y < CONTAINER_MAX_SIZE; y++) {
                if (!elements[x][y][z].doesExist()) {
                    del = false;
                }
            }
        }
        
        if (del) {
            for(int x = 0; x < CONTAINER_MAX_SIZE; x++) {
                for(int y = 0; y < CONTAINER_MAX_SIZE; y++) {
                    elements[x][y][z].setExist(false);
                }
            }
        }
        
    }
        /*
         
         FormGenerator fG = FormGenerator();
        form1.txt
        form2.txt
        
         String sD = "form";
         String sF = ".txt";
         
         for(int i = 1; i < NB_DE_FORMES; i++) {
         String myForm = sD + i + sF;
         int*** out = file_to_form(myForm);
         Cube*** mesCubes = UneFonction(out);
         
         fg.add(mesCubes)
         
         }
         
         
         */
}

void Container::RenderDrawContainer(SDL_Renderer* renderer, int shiftX, int shiftY) {
    update();

    Cube c;
    
    Uint8 SavedR = 0;
    Uint8 SavedG = 0;
    Uint8 SavedB = 0;
    Uint8 SavedA = 0;
    int test = SDL_GetRenderDrawColor(renderer, &SavedR, &SavedG, &SavedB, &SavedA);
    if (test != 0)
        SDL_GetError();
    
    for(int i = 0; i < CONTAINER_MAX_SIZE; i++) {
        for(int j = 0; j < CONTAINER_MAX_SIZE; j++) {
            for(int k = 0; k < CONTAINER_MAX_SIZE; k++) {
                c = elements[i][j][k];
                if (c.doesExist()) {
                    
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
    SDL_SetRenderDrawColor(renderer, SavedR, SavedG, SavedB, SavedA);
};
