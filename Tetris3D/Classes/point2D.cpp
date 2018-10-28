//
//  point2D.cpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "point2D.hpp"

// Point2D Methods
Point2D::Point2D() {
    x = 0;
    y = 0;
}

Point2D::Point2D(double abscisse, double ordonnee) {
    x = abscisse;
    y = ordonnee;
}

double Point2D::getX() {
    return x;
}

double Point2D::getY() {
    return y;
}
// End Point2D Methods
