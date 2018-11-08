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
    size = 0.;
    exist = false;
};

Cube::Cube(double size) {
    this->size = size;
    if (size == 0) {
        exist = false;
    } else {
        exist = true;
    }
};

double Cube::getSize() {
    return this->size;
};

bool Cube::doesExist() {
    return exist;
};

void Cube::RenderDrawCube(SDL_Renderer *renderer, int x, int y, int z, int shiftX, int shiftY) {
    int a = x * getSize();
    int b = y * getSize();
    int c = z * getSize();
    
    
    Point2D A = Point2D(a - b + shiftX, (a + b) * cos(ANGLE) + 2 * c * cos(ANGLE) + shiftY);
    Point2D B = Point2D(a - b + getSize() + shiftX, (a + b + getSize()) * cos(ANGLE) + 2 * (c) * cos(ANGLE) + shiftY);
    Point2D C = Point2D(a - b + shiftX, (a + b + 2 * getSize()) * cos(ANGLE) + 2 * c * cos(ANGLE) + shiftY);
    Point2D D = Point2D(a - b - getSize() + shiftX, (a + b + getSize()) * cos(ANGLE) + 2 * c * cos(ANGLE) + shiftY);
    //Point2D E = Point2D(a - b + shiftX, (a + b) * cos(ANGLE) + 2 * (c + getSize()) * cos(ANGLE) + shiftY);
    Point2D F = Point2D(a - b + getSize() + shiftX, (a + b + getSize()) * cos(ANGLE) + 2 * (c + getSize()) * cos(ANGLE) + shiftY);
    Point2D G = Point2D(a - b + shiftX, (a + b + 2 * getSize()) * cos(ANGLE) + 2 * (c + getSize()) * cos(ANGLE) + shiftY);
    Point2D H = Point2D(a - b - getSize() + shiftX, (a + b + getSize()) * cos(ANGLE) + 2 * (c + getSize()) * cos(ANGLE) + shiftY);
    
    Square s1 = Square(A, B, C, D);
    Square s2 = Square(B, C, G, F);
    Square s3 = Square(C, D, H, G);
    
    s1.fill(renderer);
    s1.RenderDrawSquare(renderer);
    s2.fill(renderer);
    s2.RenderDrawSquare(renderer);
    s3.fill(renderer);
    s3.RenderDrawSquare(renderer);
    
};

Cube*** createArray(int xSize, int ySize, int zSize) {
    Cube*** array;
    array = new Cube**[xSize];
    for(int x = 0; x < xSize; ++x) {
        array[x] = new Cube*[ySize];
        for(int y = 0; y < ySize; ++y) {
            array[x][y] = new Cube[zSize];
            for(int z = 0; z < zSize; ++z) {
                array[x][y][z] = Cube();
            }
        }
    }
    return array;
};

void freeArray(Cube*** cTab, int xSize, int ySize, int zSize) {
    for(int i = 0; i < xSize; i++) {
        for(int j = 0; j < ySize; j++) {
            delete[] cTab[i][j];
        }
        delete[] cTab[i];
    }
    delete[] cTab;
};
