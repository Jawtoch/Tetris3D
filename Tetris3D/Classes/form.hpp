//
//  form.hpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#ifndef form_hpp
#define form_hpp

#include <stdio.h>

#include "point3D.hpp"
#include "cube.hpp"

class Form {
    
private:
    Point3D origine;
    Cube*** elements;
    int* color;
    
public:
    Form();
    Form(Cube*** elements);
    Point3D getOrigine();
    void addElement(Cube e, int x, int y, int z);
    Cube*** getElements();
    void move(int x, int y, int z);
};

#endif /* form_hpp */
