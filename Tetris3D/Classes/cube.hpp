//
//  cube.hpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#ifndef cube_hpp
#define cube_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "point2D.hpp"
#include "square.hpp"

#include "point3D.hpp" //Get ANGLE constant

class Cube {
    
private:
    double taille;
    bool exist;
    
public:
    Cube();
    Cube(double taille);
    void RenderDrawCube(SDL_Renderer* renderer, int a, int b, int c, int shiftX, int shiftY);
    bool doesExist();
};

Cube*** createArray(int taille1, int taille2, int taille3);

void freeArray(Cube*** cTab);
#endif /* cube_hpp */

