//
//  segment.cpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "segment.hpp"

// Segment Methods
Segment::Segment() {
    p1 = Point2D();
    p2 = Point2D();
}

Segment::Segment(Point2D a, Point2D b) {
    p1 = a;
    p2 = b;
}

Point2D Segment::getP1() {
    return p1;
}

Point2D Segment::getP2() {
    return p2;
}

void Segment::RenderDrawSegment(SDL_Renderer* renderer) {
    SDL_RenderDrawLine(renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    
}

// End Segment Methods
