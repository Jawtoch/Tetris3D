//
//  point3D.hpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#ifndef point3D_hpp
#define point3D_hpp

#include <stdio.h>
#include <math.h>
#include "point2D.hpp"

#define ANGLE 0.9546951008

class Point3D {
    
private:
    double x;
    double y;
    double z;
    
public:
    Point3D();
    Point3D(double a, double b, double c);
    double getX();
    double getY();
    double getZ();
    Point2D toPoint2D();
};

#endif /* point3D_hpp */
