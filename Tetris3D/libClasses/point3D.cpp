//
//  point3D.cpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "point3D.hpp"

// Point3D Methods

Point3D::Point3D() {
    x = 0;
    y = 0;
    z = 0;
}

Point3D::Point3D(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
}


double Point3D::getX() {
    return x;
}

double Point3D::getY() {
    return y;
}

double Point3D::getZ() {
    return z;
}

Point2D Point3D::toPoint2D() {
    double a = (getX() + getY());
    double b = (getX() + getY()) * cos(ANGLE) + 2 * getZ() * cos(ANGLE);
    return Point2D(a,b);
}
// End Point3D Methods
