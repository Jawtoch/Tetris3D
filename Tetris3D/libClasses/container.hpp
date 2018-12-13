//
//  container.hpp
//  Tetris3D
//
//  Created by ugo cottin on 28/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//
#ifndef container_hpp
#define container_hpp

#include <stdio.h>
#include <map>
#include <cassert>

#include "form.hpp"

/**
 This structure represent the board of the game. All forms shoud be contained in and deleted when needed.
 */
class Container {
    
private:
    /**
     An array of forms which contains all the forms which need to be manipulated during the game
     */
    Cube*** elements;
    
public:
    
    /**
     Constructor of a container, with no forms inside.
     */
    Container();
    
    ~Container();
    /**
     Add form to the container
     
     @param addedForm The form which shoud be added
     */
    void addForm(Form addedForm);
    
    void update();
    
    /**
     Return the elements of the container
     
     @return the elements
     */
    Cube*** getElements();
    
    /**
     Add the container to the renderer
     
     @param renderer A structure representing rendering state
     */
    void RenderDrawContainer(SDL_Renderer* renderer, int shiftX, int shiftY, Form &currentForm);
};

#endif /* container_hpp */




