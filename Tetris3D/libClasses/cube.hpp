//
//  cube.hpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#ifndef cube_hpp
#define cube_hpp

#include <iostream>

#include "point2D.hpp"
#include "square.hpp"
#include "point3D.hpp" //Get ANGLE constant

class Cube {
    
private:

    /**
     The size of the cube on one dimension. All sides are the same size
     */
    double size;
    
    /**
     Tell if the cube exist or not. If true, the cube exist, and if false, not
     */
    bool exist;
    
    int colors[4];
    
public:
    
    /**
     Constructor of an empty cube. His size is 0
     */
    Cube();
    
    /**
     Constructor of a cube of given size
     
     @param size The size of the cube
     */
    Cube(double size);
    
    /**
     Return the size of the cube
     
     @return the size of the cube
     */
    double getSize();
    
    /**
     Set the rgb colors value of the cube
     
     @param r the red componment
     @param g the green componment
     @param b the blue componment
     */
    void setColors(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    
    /**
     Put the rgb colors value of the cube into the pointers
     
     @param r the red componment
     @param g the green componment
     @param b the blue componment
     */
    void getColors(Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a);
    
    /**
     Set the state of the cube, if it exist or not
     
     @param b the state of cube
     */
    void setExist(bool b);
    
    /**
     Return the state of the cube, if it exist or not
     
     @return the state of cube
     */
    bool doesExist();
    
    /**
     Add the cube to the renderer
     
     @param renderer A structure representing rendering state
     */
    void RenderDrawCube(SDL_Renderer* renderer, int a, int b, int c, int shiftX, int shiftY);
};

/**
 Create an 3D array of cubes of given size (x,y,z)
 
 @param xSize The x size of the array
 @param ySize The y size of the array
 @param zSize The z size of the array
 @warning After use, de-allocate the array with the "freeArray" function
 @return A 3D array of cubes
 */
Cube*** createArray(int xSize, int ySize, int zSize);


/**
 De-allocate the given array of given size
 
 @param cTab The array who need to be freed
 @param xSize The x size of the array
 @param ySize The y size of the array
 @param zSize The z size of the array
 @warning Be sure of the dimension of the array
 */
void freeArray(Cube*** cTab, int xSize, int ySize, int zSize);

#endif /* cube_hpp */
