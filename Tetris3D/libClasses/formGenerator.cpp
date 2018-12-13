//
//  formGenerator.cpp
//  Tetris3D
//
//  Created by ugo cottin on 29/11/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "formGenerator.hpp"

FormGenerator::FormGenerator() {
    
}

void FormGenerator::addForm(Form &addedForm) {
    forms.insert(std::make_pair(forms.size(), &addedForm));
}

Form* FormGenerator::getForm() {
    //return forms.at((rand() % forms.size()));
    Cube*** el = forms.at((rand() % forms.size()))->getElements();
    Form *f = new Form(el);
    f->setOrigin(Point3D((int)CONTAINER_MAX_SIZE/2, (int)CONTAINER_MAX_SIZE/2, 0));
    return f;
}
