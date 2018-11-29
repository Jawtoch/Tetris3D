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
#include <iterator>

#include "point3D.hpp"
#include "cube.hpp"

/**
 This structure is intended to represent a form, composed of cubes. The form dimension is 3x3x3
 */
class Form {
    
private:
    
    /**
     The origin of the form, from where she shoud be represented
     */
    Point3D origin;
    
    /**
     An array of 3 integers (red, green, blue)
     */
    int* color;
    
    /**
     Tell if the form exist or not. If true, the form exist, and if false, not
     */
    bool exist;
    
    /**
     An array of cubes, elements the form, of dimension 3x3x3
     */
    Cube*** elements;
    
public:
    
    /**
     Constructor of an empty form, of origin in (0,0,0), zero elements and black color
     */
    Form();
    
    ~Form();
    /**
     Constructor of a form, of origin in (0,0,0), random color, and given elements
     
     @param elements The elements who compose the form
     */
    Form(Cube*** elements);
    
    /**
     Return the origin of the form
     
     @return The origin of the form
     */
    Point3D getOrigin();
    
    /**
     Return the elements of the form
     
     @return An array of cubes, representing the elements of the form
     */
    Cube*** getElements();
    
    /**
     Add a given element to the form, on given coordinates (each coordinate in [0;3[)
     
     @param e The element who shoud be added
     @param x The x coordiante of the added element
     @param y The y coordiante of the added element
     @param z The z coordiante of the added element
     
     @warning If the x,y or z coordiante is incorrect, print an error message and do nothing. Please check that x,y and z are in [0;3[
     */
    void addElement(Cube e, unsigned int x, unsigned int y, unsigned int z);
    
    /**
     Move the form
     
     @param x The shift on the x axis
     @param y The shift on the y axis
     @param z The shift on the z axis
     */
    void move(int x, int y, int z);
    
    /**
     Return the state of the form, if it exist or not
     
     @return the state of form
     */
    bool doesExist();
    
    /**
     Add the form to the renderer
     
     @param renderer A structure representing rendering state
     */
    void RenderDrawForm(SDL_Renderer* renderer, int shiftX, int shiftY);
    
};
#endif /* form_hpp */
