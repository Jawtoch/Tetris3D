//
//  formGenerator.hpp
//  Tetris3D
//
//  Created by ugo cottin on 29/11/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#ifndef formGenerator_hpp
#define formGenerator_hpp

#include <stdio.h>
#include <map>
#include <cassert>
#include <cstdlib>
#include "form.hpp"

class FormGenerator {
    
private:
    std::map<int, Form*> forms;

public:
    FormGenerator();
    void addForm(Form &addedForm);
    Form* getForm();
};

#endif /* formGenerator_hpp */
