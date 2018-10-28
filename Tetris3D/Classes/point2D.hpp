//
//  point2D.hpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#ifndef point2D_hpp
#define point2D_hpp

#include <stdio.h>

class Point2D {
    
private:
    double x;
    double y;
    
public:
    Point2D();
    Point2D(double abscisse, double ordonnee);
    double getX();
    double getY();
};


#endif /* point2D_hpp */
