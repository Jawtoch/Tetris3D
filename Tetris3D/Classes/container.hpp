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
#include "form.hpp"

/**
 This structure represent the board of the game. All forms shoud be contained in and deleted when needed.
 */
class Container {
private:
    
    /**
     An array of forms which contains all the forms which need to be manipulated during the game
     */
    Form* forms;
public:
    
    /**
     Constructor of a container, with no forms inside.
     */
    Container();
    
    /**
     Destructor of a container, with no forms inside.
     */
    ~Container();
    
    /**
     Extend the size of the forms array
     
     @param delta The number of cells which need to be added
     */
    void extendFrom(unsigned int delta);
    
    /**
     Shrink the size of the forms array
     
     @param delta The number of cells which need to be deleted
     */
    void shrinkFrom(unsigned int delta);
};

#endif /* container_hpp */
