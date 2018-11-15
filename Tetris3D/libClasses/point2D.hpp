//
//  point2D.hpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#ifndef point2D_hpp
#define point2D_hpp

#define FORM_MAX_SIZE 3
#define CONTAINER_MAX_SIZE 10

#include <stdio.h>

class Point2D {
    
private:
    
    /**
     The abscissa of the point
     */
    double x;
    
    /**
     The ordinate of the point
     */
    double y;
    
public:
    
    /**
     Constructor of a 2D point in (0,0)
     */
    Point2D();
    
    /**
     Constructor of a 2D point of given abscissa and ordinate
     
     @param abscissa A abscissa
     @param ordinate A ordinate
     */
    Point2D(double abscissa, double ordinate);
    
    /**
     Return the abscissa of the 2D point
     
     @return x
     */
    double getX();
    
    /**
     Return the ordinate of the 2D point
     
     @return y
     */
    double getY();
};


#endif /* point2D_hpp */
