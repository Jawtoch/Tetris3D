//
//  cube.cpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "cube.hpp"

// Cube Methods

Cube::Cube() {
    taille = 0.;
    exist = false;
}

Cube::Cube(double taille) {
    this->taille = taille;
    if (taille == 0) {
        exist = false;
    } else {
        exist = true;
    }
}

void Cube::RenderDrawCube(SDL_Renderer *renderer, int x, int y, int z, int shiftX, int shiftY) {
    double angle = ANGLE;
    int a = x * taille;
    int b = y * taille;
    int c = z * taille;
    
    
    Point2D A = Point2D(a - b + shiftX, (a + b) * cos(angle) + 2 * c * cos(angle) + shiftY);
    Point2D B = Point2D(a - b + taille + shiftX, (a + b + taille) * cos(angle) + 2 * (c) * cos(angle) + shiftY);
    Point2D C = Point2D(a - b + shiftX, (a + b + 2 * taille) * cos(angle) + 2 * c * cos(angle) + shiftY);
    Point2D D = Point2D(a - b - taille + shiftX, (a + b + taille) * cos(angle) + 2 * c * cos(angle) + shiftY);
    //Point2D E = Point2D(a - b + shiftX, (a + b) * cos(angle) + 2 * (c + taille) * cos(angle) + shiftY);
    Point2D F = Point2D(a - b + taille + shiftX, (a + b + taille) * cos(angle) + 2 * (c + taille) * cos(angle) + shiftY);
    Point2D G = Point2D(a - b + shiftX, (a + b + 2 * taille) * cos(angle) + 2 * (c + taille) * cos(angle) + shiftY);
    Point2D H = Point2D(a - b - taille + shiftX, (a + b + taille) * cos(angle) + 2 * (c + taille) * cos(angle) + shiftY);
    
    Square s1 = Square(A, B, C, D);
    Square s2 = Square(B, C, G, F);
    Square s3 = Square(C, D, H, G);
    
    s1.remplir(renderer);
    s1.RenderDrawSquare(renderer);
    s2.remplir(renderer);
    s2.RenderDrawSquare(renderer);
    s3.remplir(renderer);
    s3.RenderDrawSquare(renderer);
    
}

bool Cube::doesExist() {
    return exist;
}
// End Cube Methods

Cube*** createArray(int taille1, int taille2, int taille3) {
    /*Cube*** T = new Cube**[taille1];
    if (T == NULL)
        exit(EXIT_FAILURE);
    for(int i = 0; i < taille1; i++) {
        T[i] = new Cube*[taille2];
        for(int j = 0; j < taille2; j++) {
            T[i][j] = new Cube[taille3];
        }
    }
    return T;*/
    Cube*** array;
    array = new Cube**[taille1];
    for(int x = 0; x < taille1; ++x) {
        array[x] = new Cube*[taille2];
        for(int y = 0; y < taille2; ++y) {
            array[x][y] = new Cube[taille3];
            for(int z = 0; z < taille3; ++z) {
                array[x][y][z] = Cube();
            }
        }
    }
    return array;
}

void freeArray(Cube*** cTab) {
    for(int i = 0; i < (sizeof(Cube**)/sizeof(Cube***)); i++) {
        for(int j = 0; j < (sizeof(Cube*)/sizeof(Cube**)); j++) {
            delete[] cTab[i][j];
        }
        delete[] cTab[i];
    }
    delete[] cTab;
}

