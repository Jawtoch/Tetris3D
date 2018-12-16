//
//  formGenerator.cpp
//  Tetris3D
//
//  Created by ugo cottin on 29/11/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "formGenerator.hpp"

FormGenerator::FormGenerator(int containerMaxSize, int formMaxSize) {
    this->containerMaxSize = containerMaxSize;
    this->formMaxSize = formMaxSize;
}

FormGenerator::~FormGenerator() {
    for(int i = 0; i < forms.size(); i++) {
        Form *f = forms.at(i);
        delete f;
    }
}

void FormGenerator::addForm(Form &addedForm) {
    forms.insert(std::make_pair(forms.size(), &addedForm));
}

Form* FormGenerator::getForm() {
    int rnd = rand() % forms.size();
    Cube*** el = forms.at(rnd)->getElements();
    Form *f = new Form(el, containerMaxSize, formMaxSize);
    f->setOrigin(Point3D((int)containerMaxSize/2, (int)containerMaxSize/2, 0));
    return f;
}
