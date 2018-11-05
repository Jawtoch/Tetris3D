//
//  container.cpp
//  Tetris3D
//
//  Created by ugo cottin on 28/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "container.hpp"

Container::Container() {
    size = 3;
    for(int i = 0; i < size; i++) {
        forms[i] = Form();
    }
}

Container::~Container() {
}

void Container::extendFrom(unsigned int delta) {
    Form newContainer[3];
    for(int i = 0; i < size + delta; i++) {
        newContainer[i] = forms[i];
    }
    *forms = *newContainer;
};

void Container::shrinkFrom(unsigned int delta) {
    Form newContainer[3];
    for(int i = 0; i < size - delta; i++) {
        newContainer[i] = forms[i];
    }
    *forms = *newContainer;
};

void Container::addForm(Form addedForm) {
    //extendFrom(1);
    forms[size] = addedForm;
};

int Container::getSize() {
    return size;
};

void Container::RenderDrawContainer(SDL_Renderer* renderer, int shiftX, int shiftY) {
    for(int i = 0; i < size; i++) {
        if (forms[i].doesExist())
            forms[i].RenderDrawForm(renderer, shiftX, shiftY);
    }
};
