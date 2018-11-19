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
    
    /**
     The x coordinate of the 3D point
     */
    double x;
    
    /**
     The y coordinate of the 3D point
     */
    double y;
    
    /**
     The z coordinate of the 3D point
     */
    double z;
    
public:
    
    /**
     Constructor of an empty 3D point, on (0,0,0)
     */
    Point3D();
    
    /**
     Constructor of a 3D point, of given x,y and z coordinates
     */
    Point3D(double a, double b, double c);
        
    /**
     Return the x coodinate of the 3D point
     
     @return x
     */
    double getX();
    
    /**
     Return the y coodinate of the 3D point
     
     @return y
     */
    double getY();
    
    /**
     Return the z coodinate of the 3D point
     
     @return z
     */
    double getZ();
    
    /**
     Project the 3D point on the 2D plane
     
     @return A 2D point who correspond to the projected 3D point
     */
    Point2D toPoint2D();
};

#endif /* point3D_hpp */
